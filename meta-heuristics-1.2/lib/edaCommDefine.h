#ifndef __edaCommDefine_h__
#define __edaCommDefine_h__

#include "edaDefine.h"


#ifdef COMM_MPI
#include <mpi.h>
#endif

#ifdef COMM_MPI
#define EDAMetasearchStart(argc, argv)                          \
  EDALogProcessStart()                                          \
  MPI_Init( &argc, &argv );                                     \
  MPI_Comm_rank( MPI_COMM_WORLD, &__rank__ );                   \
  MPI_Comm_size( MPI_COMM_WORLD, &__size__ );                   \
  if ( __size__ < 2 ){                                          \
    std::cerr << "Number of processors must > 1" << std::endl;  \
    MPI_Finalize();                                             \
    return 0;                                                   \
  }                                                             \
  if ( __rank__ == 0 ){
#else
#define EDAMetasearchStart(argc, argv)                          \
  EDALogProcessStart()                                          \
  ;
#endif

#ifdef COMM_MPI
#define EDAMetasearchStop()                                     \
    int __c__ = EDA_MPI_QUIT;                                   \
    for( int __p__ = 1; __p__<__size__; __p__++ ){              \
      MPI_Send( &__c__, 1, MPI_INT, __p__, 0, MPI_COMM_WORLD ); \
    }                                                           \
  } else {                                                      \
    /* stuff listening to master requests here */               \
    rnd.init(__rank__);                                         \
    edaMpiWorker w(0);                                          \
    w.serve();                                                  \
  }                                                             \
  MPI_Finalize();
#else

#define EDAMetasearchStop()                                     \
  ; /* do nothing */
#endif

#endif
