#include <mpi.h>
#include "edaMpiWrapperControl.h"
#include "edaMpiWorker.h"

edaMpiWorker::edaMpiWorker( int master )
  : master_(master)
{
  MPI_Comm_rank( MPI_COMM_WORLD, &rank_ );
}

edaMpiWorker::~edaMpiWorker()
{
}

void edaMpiWorker::serve()
{
  // variables
  int command, l, stat = EDA_MPI_WAITING_COMMAND;
  edaSearch *sa = NULL;
  edaSolutionList *list = NULL;
  MPI_Status mpiStat;
  char *buf = NULL;

  while( stat == EDA_MPI_WAITING_COMMAND ){
    // wait command and print error if exists
    MPI_Recv( &command, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &mpiStat );
    if ( mpiStat.MPI_SOURCE != master_ ){
      std::cerr << rank_ << ": command not from master " << master_ << std::endl; 
      continue;
    }

    // serve the command
    switch( command ){
    case EDA_MPI_START_SEARCH: {
      // get the search algorithm
      MPI_Recv( &l, 1, MPI_INT, master_, 0, MPI_COMM_WORLD, &mpiStat );
      buf = new char[l];
      MPI_Recv( buf, l, MPI_CHAR, master_, 0, MPI_COMM_WORLD, &mpiStat );
      edaBuffer sa_buf;
      sa_buf.setBuffer( l, buf );
      sa = (edaSearch*)classGenerateFromBuffer( sa_buf );

      // get the solution
      MPI_Recv( &l, 1, MPI_INT, master_, 0, MPI_COMM_WORLD, &mpiStat );
      buf = new char[l];
      MPI_Recv( buf, l, MPI_CHAR, master_, 0, MPI_COMM_WORLD, &mpiStat );
      edaBuffer solList_buf;
      solList_buf.setBuffer( l, buf );
      list = (edaSolutionList*)classGenerateFromBuffer( solList_buf );

      // start the search
      sa->search( *list );

      // write the status
      stat = EDA_MPI_SEARCH_FINISHED;
      break;
    }
    case EDA_MPI_QUIT:
      stat = EDA_MPI_QUIT_DONE;
      break;
    default:
      std::cerr << rank_ << ": unknown command from master " << master_ << std::endl;
      stat = EDA_MPI_UNKNOWN_COMMAND;
      break;
    }
    
    // return the result if not quit
    if ( stat != EDA_MPI_QUIT_DONE )
      MPI_Send( &stat, 1, MPI_INT, master_, 0, MPI_COMM_WORLD );
    else
      break;

    // and return additional result
    switch( stat ){
    case EDA_MPI_SEARCH_FINISHED:{
      // return new solution to master
      edaBuffer sol_buf;
      list->doSerialize( sol_buf, true );
      l = sol_buf.getActualSize();
      MPI_Send( &l, 1, MPI_INT, master_, 0, MPI_COMM_WORLD );
      MPI_Send( sol_buf.getBuffer(), l, MPI_CHAR, master_, 0, MPI_COMM_WORLD );

      // delete search algorithm and solution
      delete sa;
      delete list;
      sa = NULL;
      list = NULL;
      
      break;
    }
    default:
      break;
    }

    // update local variables
    stat = EDA_MPI_WAITING_COMMAND;
  }
}
