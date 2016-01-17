#include <unistd.h>
#include "edaWrapperControl.h"
#include "edaSearchWrapper.h"
#include "edaBestSelectWrapper.h"
#include "edaFullSelectWrapper.h"

edaWrapperControl::edaWrapperControl() :
  edgeNum (0), vertexNum (0), loopNum (0)
{
}

int edaWrapperControl::insertVertex(edaSearch *sa)
{
  edaSelectionWrapper *slect = new edaFullSelectWrapper();
  int result = insertVertex(sa, *slect);
  delete slect;
  return result;
}

int edaWrapperControl::insertVertex(edaSearch *sa, const edaSelectionWrapper &slect)
{
  int id = vertexNum;
  vertexNum++;
  edaSearch* search = sa->clone(); 
  search->TaskID = id; 
  taskDAG.insertVertex(id, search);
  taskSlect[id] = slect.clone();
  taskStatus[id] = STATUS_PENDING;  
  return id;
}

int edaWrapperControl::insertEdge(const int from, const int to)
{
  int id = edgeNum;
  edgeNum++;

  taskDAG.insertEdge(id, from, to);

//  printDebug(4, "parent of [" << to << "] is [" << from <<"]");

  return id;
}

vector<int> edaWrapperControl::findReadyTask() const
{
  vector<int> taskList;
  vector<int> readyTasks;
  vector<int>::iterator intIter;

  taskList = taskDAG.traverse();
  for (intIter = taskList.begin(); intIter != taskList.end(); intIter++)
  {
    map<int, int>::const_iterator mci = taskStatus.find(*intIter);
    if (mci->second == STATUS_READY || mci->second == STATUS_LOOP_READY)
    {
      // If it is ready, then add to ready list
      readyTasks.push_back(*intIter);
    }
  }

  return readyTasks;
}

int edaWrapperControl::insertLoop(const int _from, const int _to, const edaContinue &con)
{
  int id = loopNum;
  int from = _from, to = _to;
  if( taskDAG.insertLoop(id, from, to) ) {  
    loopCond[id] = con.clone();
    loopCond[id]->init();
    loopStatus[id] = STATUS_PENDING;
    loopNum++;  
  } else {
    cerr << "The process not include loop from task " << from
            << " to task " << to << ". Make sure you had a connector between 2 tasks !" << endl; 
    exit(1);
  }
  return id;
}

bool edaWrapperControl::allDone() 
{  
  vector<int> taskList;
  vector<int>::iterator intIter;
  taskList = taskDAG.traverse();
  bool allDone;
  bool haveError;

  // Scan until no new error found
  do
  {
    allDone = true;
    haveError = false;

    for (intIter = taskList.begin(); intIter != taskList.end(); intIter++)
    {
      int taskID = *intIter;
      // Update all nodes status
      int oldStatus = taskStatus[taskID];
      int newStatus = checkTaskStatus( taskID );

      if ((newStatus != oldStatus) && (newStatus == STATUS_ERROR))
      {
        haveError = true;
      }
      taskStatus[taskID] = newStatus;

      if ((taskStatus[taskID] != STATUS_FINISHED)
          && (taskStatus[taskID] != STATUS_ERROR))
      {
        allDone = false;
      }
    }
  } while (haveError && !allDone);

    
  map<int, int>::const_iterator loopIter;
  for (loopIter = loopStatus.begin(); loopIter != loopStatus.end(); loopIter++) {
    if(loopIter->second != STATUS_FINISHED) 
    {
//      printDebug(5, "not done loop: " << loopIter->first);
    
      return false;
    }
  }
  
  return allDone;
}

int edaWrapperControl::checkTaskStatus(int taskID) {
  // Check only Pending jobs
  if (taskStatus[taskID] != STATUS_PENDING && taskStatus[taskID]!= STATUS_LOOPING)
  {
    return taskStatus[taskID];
  }

  vector<int> parentTasks;
  vector<int>::iterator parentIter;

  parentTasks = taskDAG.getParentNodes( taskID );
  if ( parentTasks.empty() )
  {
    // If node has no parent, then it is ready
    if(taskStatus[taskID] == STATUS_PENDING)
      return STATUS_READY;
    if (taskStatus[taskID] == STATUS_LOOPING) 
      return STATUS_LOOP_READY;
  }
  // If loop mode 
  else if (taskStatus[taskID] == STATUS_LOOPING) 
      return STATUS_LOOP_READY;
  
  bool allFail = true;

  // Check for its parents
  for (parentIter = parentTasks.begin(); parentIter != parentTasks.end(); parentIter++)
  {
    int jobStatus = taskStatus[*parentIter];

    if ((jobStatus != STATUS_FINISHED) && (jobStatus != STATUS_ERROR))
    {
      // If node's parent is not finished yet, then it is pending
      return STATUS_PENDING;
    }

    if (jobStatus != STATUS_ERROR)
    {
      allFail = false;
    }
  }

  if ( allFail )
  {
      cout << taskStatus[taskID] << endl;
    // If all its parents is fail, then it is fail too
    return STATUS_ERROR;
  }
  
  // Otherwise, it is ready to run
  return STATUS_READY;
}

int edaWrapperControl::checkLoopStatus( int taskID ) {
  int count = 0;   
  for(edaDAGEdge* loop = taskDAG.findLoop(taskID, loopStatus);
      loop != NULL; loop = taskDAG.findLoop(taskID, loopStatus) ) {
    count ++;
    
    edaContinue* con = loopCond[loop->getKey()];
    edaSolutionList* list = taskSolutionList[taskID];
    if(!con->check(*list)) 
    {     
      loopStatus[loop->getKey()] = STATUS_FINISHED;     
    }
    else {
      edaCluster* cluster = taskDAG.getCluster(loop);
      for(unsigned int i = 0; i < cluster->size(); i++) {
        taskStatus[cluster->at(i)->getKey()] = STATUS_PENDING;
      }
      vector<edaDAGEdge*>* subLoop = taskDAG.detectSubLoop(*loop);
      for(unsigned int i = 0; i < subLoop->size(); i++) {
        int loopID = subLoop->at(i)->getKey();
        loopStatus[loopID] = STATUS_PENDING;
        loopCond[loopID]->init();
      }
      delete subLoop;
      delete cluster;
      edaDAGVertex *toVertex = loop->getDestVertex();
      taskStatus[toVertex->getKey()] = STATUS_LOOPING; 
      return count;
    }
  }
  return count;  
}


edaSolutionList* edaWrapperControl::chooseSolution( int taskID, edaSolutionList &list ) 
{
  vector<int> parentTasks;
  parentTasks = taskDAG.getParentNodes(taskID);
  edaSolutionList *myList = NULL;   
  if ( taskStatus[taskID] == STATUS_LOOP_READY) {
    edaDAGEdge* loop = taskDAG.detectLoop(taskID, loopStatus); 
    int loopKey = loop->getSourceVertex()->getKey();
    myList = taskSolutionList[loopKey]->clone();
    taskSlect[taskID]->select(*myList);        
  }
  else if (parentTasks.empty())
  {
    // If no parent, use input solution
    myList = list.clone();
    taskSlect[taskID]->select(*myList);
  }
  else
  {
    // Have parents
    myList = new edaSolutionList();
    vector<int>::iterator parentIter;
    for (parentIter = parentTasks.begin(); parentIter != parentTasks.end(); parentIter++) {
      if (taskSolutionList[*parentIter] != NULL) {
          edaSolutionList *pList = taskSolutionList[*parentIter];
          for(unsigned int i = 0; i < pList->size(); i++) {    
            edaSolution * pSol = pList->at(i);
            myList->push_back(pSol->clone());
          }
          taskSlect[taskID]->select(*myList);
      }
    }
  }
  return myList;
}
edaWrapperControl::~edaWrapperControl() {
  /*Delete anything*/
    
  map<int, edaSolutionList *>::iterator solIt;
  map<int, edaSelectionWrapper *>::iterator slectIt;
  map<int, edaContinue *>::iterator conIt;
  
  for( solIt=taskSolutionList.begin(); solIt!=taskSolutionList.end(); solIt++ )
    delete solIt->second;
  for( slectIt=taskSlect.begin(); slectIt!=taskSlect.end(); slectIt++ )
    delete slectIt->second;
  for( conIt=loopCond.begin(); conIt!=loopCond.end(); conIt++) 
    delete conIt->second;

}
