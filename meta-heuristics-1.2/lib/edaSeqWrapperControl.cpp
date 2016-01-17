#include "edaSeqWrapperControl.h"
#include "edaSeqSearchWrapper.h"

edaSeqWrapperControl::edaSeqWrapperControl() :
  edaWrapperControl()
{
}

bool edaSeqWrapperControl::search(edaSolutionList &list)
{     
  int lastSearch = -1; 

  // If all job is done, quit
  while (!allDone())
  {
    // Find nodes that ready to run
    vector<int> readyNodes = findReadyTask();
    vector<int>::iterator intIter;

    for (intIter = readyNodes.begin(); intIter != readyNodes.end(); intIter++)
    {
      edaSearch *&sa = taskDAG[*intIter];

      sa->ProcID = 0;
      lastSearch = *intIter;
      edaSolutionList *myList = chooseSolution( *intIter, list );
  
      // Pack the search algorithm
      edaBuffer sa_buf;
      sa->doSerialize( sa_buf, true ); 

      // Create wrapper object
      edaSearchWrapper *sw;
      sw = new edaSeqSearchWrapper( sa_buf );

      // Pack the solution
      edaBuffer sol_buf_in, sol_buf_out;
      myList->doSerialize( sol_buf_in, true );

      // Invoke wrapper's search method
      sw->search( sol_buf_in, sol_buf_out );

      // Unpack and save the solution
      if ( taskSolutionList[*intIter] != NULL ) 
          delete taskSolutionList[*intIter];
      
      taskSolutionList[*intIter] = 
              (edaSolutionList*)classGenerateFromBuffer( sol_buf_out );
      taskStatus[*intIter] = STATUS_FINISHED;
      
      checkLoopStatus(*intIter);
      
      // Destroy objects
      delete myList;
      delete sw;

    }
  }

  // Return the solution
  if(lastSearch != -1)
    list = *(taskSolutionList[lastSearch]);

//  // Delete solutions map
//  map<int, edaSolutionList*>::iterator mapIter;
//  for (mapIter = taskSolutionList.begin(); mapIter != taskSolutionList.end(); mapIter++)
//  {
//    delete mapIter->second;
//  }

  return true;
}
