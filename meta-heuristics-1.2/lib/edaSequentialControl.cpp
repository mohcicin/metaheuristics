#include "edaSequentialControl.h"

edaSequentialControl::edaSequentialControl() :
  edgeNum (0), vertexNum (0)
{
}

int edaSequentialControl::insertVertex(edaSearch *sa)
{
  int id = vertexNum;
  vertexNum++;

  taskDAG.insertVertex(id, sa);
  taskStatus[id] = STATUS_PENDING;

  return id;
}

int edaSequentialControl::insertEdge(const int from, const int to)
{
  int id = edgeNum;
  edgeNum++;

  taskDAG.insertEdge(id, from, to);

//  printDebug(3, "parent of [" << to << "] is [" << from <<"]");

  return id;
}

bool edaSequentialControl::search(edaSolutionList &list)
{
  map<int, edaSolutionList*> taskSolList;
  int lastSearch;

  // If all job is done, quit
  while (!allDone())
  {
    // Find nodes that ready to run
    vector<int> readyNodes = findReadyNodes();
    vector<int>::iterator intIter;

    for (intIter = readyNodes.begin(); intIter != readyNodes.end(); intIter++)
    {
      vector<int> parentNodes;
      vector<int>::iterator parentIter;
      parentNodes = taskDAG.getParentNodes(*intIter);

      edaSearch *&sa = taskDAG[*intIter];
      lastSearch = *intIter;
      edaSolutionList *myList = NULL;

      if (parentNodes.empty()){
        // No parent
        myList = list.clone();
      } else {
        // Have parents
        double bestFitness = -1e100;
        int bestSolution;
        for (parentIter = parentNodes.begin(); parentIter != parentNodes.end(); parentIter++)
        {
          double f = (taskSolList[*parentIter])->evaluate();
          if (bestFitness < f)
          {
            bestFitness = f;
            bestSolution = *parentIter;
          }
        }

        myList = taskSolList[bestSolution]->clone();
      }

//      printDebug(4, "The solution (before): "  << myList->evaluate() << ", " << *myList->getBest());

      sa->search(*myList);
      taskSolList[*intIter] = myList;
      taskStatus[*intIter] = STATUS_FINISHED;

//      printDebug(4, "task " << *intIter <<  " -  mysol(after): " 
//              << taskSolList[*intIter]->evaluate() << ", " << * taskSolList[*intIter]->getBest() );
    }
  }

  // Return the solution
  list = *(taskSolList[lastSearch]);

  // Delete solutions map
  map<int, edaSolutionList*>::iterator mapIter;
  for (mapIter = taskSolList.begin(); mapIter != taskSolList.end(); mapIter++)
  {
    delete mapIter->second;
  }

  return true;
}

vector<int> edaSequentialControl::findReadyNodes() const
{
  vector<int> nodeList;
  vector<int> readyNodes;
  vector<int>::iterator intIter;

  nodeList = taskDAG.traverse();
  for (intIter = nodeList.begin(); intIter != nodeList.end(); intIter++)
  {
    // Check if the node is not in PENDING state
    map<int, int>::const_iterator mci = taskStatus.find(*intIter);
    if (mci->second != STATUS_PENDING)
    {
      // Then bypass
      continue;
    }

    // Find parents node
    vector<int> parentNodes;
    parentNodes = taskDAG.getParentNodes(*intIter);

    // Check parent nodes that all nodes is FINISHED
    vector<int>::iterator parentIter;
    bool allFinished = true;
    for (parentIter = parentNodes.begin(); parentIter != parentNodes.end(); parentIter++)
    {
      mci = taskStatus.find(*parentIter);
      if (mci->second != STATUS_FINISHED)
      {
        allFinished = false;
        break;
      }
    }

    if (allFinished)
    {
      readyNodes.push_back(*intIter);
    }
  }

  return readyNodes;
}

bool edaSequentialControl::allDone() const
{
  vector<int> nodeList;
  vector<int>::iterator intIter;
  nodeList = taskDAG.traverse();

  for (intIter = nodeList.begin(); intIter != nodeList.end(); intIter++)
  {
    map<int, int>::const_iterator mci = taskStatus.find(*intIter);

    if (mci->second != STATUS_FINISHED)
    {
//      printDebug(5, "not done: " << mci->first << endl);

      return false;
    }
  }

  return true;
}
