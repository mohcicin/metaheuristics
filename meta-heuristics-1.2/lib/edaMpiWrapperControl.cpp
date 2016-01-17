#include <unistd.h>
#include <mpi.h>

#include "edaMpiWrapperControl.h"

edaMpiWrapperControl::edaMpiWrapperControl() {
  edgeNum = 0;
  vertexNum = 0;
  MPI_Comm_size( MPI_COMM_WORLD, &nprocs_ );
  workers_ = new edaMpiProcStatus[nprocs_];
}

edaMpiWrapperControl::~edaMpiWrapperControl()
{
  delete [] workers_;
}


bool edaMpiWrapperControl::search( edaSolutionList &list )
{ 
  // variables
  int i, j, p, l;
  int command;
  int nidles;
  int idles[nprocs_];
  MPI_Status mpiStat;

  // initialize status variables
  runningJobCount = 0;
  for( i=1; i<nprocs_; i++ ){
    workers_[i].stat_ = EDA_MPI_PROCESSOR_IDLE;
    workers_[i].taskID_ = -1;
  }

  // start the search
  while (!allDone()) {
    vector<int> readyTasks = findReadyTask();
    vector<int>::iterator readyIter;

    // find idle processors
    nidles = 0;
    for( i=1; i<nprocs_; i++ )
      if ( workers_[i].stat_ == EDA_MPI_PROCESSOR_IDLE )
        idles[nidles++] = i;

    // Create the search objects for all ready nodes
    p = 0;
    for (readyIter = readyTasks.begin(); readyIter != readyTasks.end(); readyIter++)
    {
      // task ID on DAG
      int taskID = *readyIter;

      // send computing request to first idle processor
      if ( p < nidles ){
        // send command
        command = EDA_MPI_START_SEARCH;
        MPI_Send( &command, 1, MPI_INT, idles[p], 0, MPI_COMM_WORLD );
       
        // pack search and its parameters
        edaBuffer sa_buf;
        edaSearch *sa = taskDAG[taskID];
        sa->ProcID = idles[p];
        sa->doSerialize( sa_buf, true );

        
        // send buffer for search method
        l = sa_buf.getActualSize();
        MPI_Send( &l, 1, MPI_INT, idles[p],
                  0, MPI_COMM_WORLD );
        MPI_Send( sa_buf.getBuffer(), sa_buf.getActualSize(), 
                  MPI_CHAR, idles[p], 0, MPI_COMM_WORLD );

        // pack solution
        edaBuffer sol_buf;
        edaSolutionList *mysol = NULL;
        mysol = chooseSolution( taskID, list );
        mysol->doSerialize( sol_buf, true );
        
        // send buffer for solution to worker
        l = sol_buf.getActualSize();
        MPI_Send( &l, 1, MPI_INT, idles[p],
                  0, MPI_COMM_WORLD );
        MPI_Send( sol_buf.getBuffer(), l, MPI_CHAR, idles[p],
                  0, MPI_COMM_WORLD );

        // set status of worker to computing
        workers_[idles[p]].stat_ = EDA_MPI_PROCESSOR_COMPUTING;
        workers_[idles[p]].taskID_ = taskID;
        taskStatus[taskID] = STATUS_RUNNING;
        runningJobCount ++;
        p ++;
      } else {
        // no processor idle, then break the loop
        break;
      }
    }
    
    int pollingResult = POLLING_NOCHANGE;
    int nodeFinished;

    // Polling for job finished
    while (true)
    {
      if ( runningJobCount == 0 ){
        // Nothing to poll
        pollingResult = POLLING_NOCHANGE;
        break;
      }

      // poll for any return
      pollingResult = polling( nodeFinished );
      if ( pollingResult == POLLING_FINISHED ){
        break;
      } else if ( pollingResult == POLLING_ERROR ){
        break;
      } else { // NOCHANGE
      }

    }

    // Job finished
    if ( pollingResult == POLLING_FINISHED )
    {
//      printDebug(3, "Job finished: " << workers_[nodeFinished].taskID_);
      taskStatus[workers_[nodeFinished].taskID_] = STATUS_FINISHED;
      runningJobCount--;

      // Get the solution
      edaBuffer result_buf;

      // receive the result status
      MPI_Recv( &l, 1, MPI_INT, nodeFinished, 0, MPI_COMM_WORLD, &mpiStat );
      if ( l == EDA_MPI_SEARCH_FINISHED ) {

        // receive the result into a buffer of characters
        MPI_Recv( &j, 1, MPI_INT, nodeFinished, 0, MPI_COMM_WORLD, &mpiStat );
        char *buf = new char[j];
        MPI_Recv( buf, j, MPI_CHAR, nodeFinished, 0, MPI_COMM_WORLD, &mpiStat );
        result_buf.setBuffer( j, buf );

        edaSolutionList *result = (edaSolutionList*)classGenerateFromBuffer(result_buf);
        taskSolutionList[workers_[nodeFinished].taskID_] = result;
        searchOrder.push_back( workers_[nodeFinished].taskID_ );

        workers_[nodeFinished].stat_ = EDA_MPI_PROCESSOR_IDLE;
      }
      
      checkLoopStatus(workers_[nodeFinished].taskID_);
    }

    // Job error
    if ( pollingResult == POLLING_ERROR )
    {
//      printDebug(3, "Job error while running: " << workers_[nodeFinished].taskID_);
      taskStatus[workers_[nodeFinished].taskID_] = STATUS_ERROR;
      runningJobCount--;
      searchOrder.remove( workers_[nodeFinished].taskID_ );
    }
  }

  if (searchOrder.empty())
  {
    return false;
  }
  
  // TODO: Should return the best result among results
//  printDebug(4, "Last search block is: " << searchOrder.back());
  list = *(taskSolutionList[searchOrder.back()]);

  return true;
}

int edaMpiWrapperControl::polling( int &nodeID )
{
  MPI_Status mpiStat;
  MPI_Probe( MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &mpiStat );
  nodeID = mpiStat.MPI_SOURCE;
  return POLLING_FINISHED;
}

