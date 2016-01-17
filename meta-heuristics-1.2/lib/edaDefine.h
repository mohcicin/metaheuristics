#ifndef __edaDefine_h__
#define __edaDefine_h__

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <fstream>
#include <math.h>
#include "edaRNG.h"
#include "edaTimer.h"

// Define some default value
#define POLLING_INTERVAL            2        // 2 seconds
#define RETRY_INTERVAL              10       // 10 seconds
#define MAX_RETRY                   25       // 25 times

// Define the status code
#define STATUS_PENDING              0
#define STATUS_READY                1
#define STATUS_STARTING             2
#define STATUS_RUNNING              3
#define STATUS_FINISHED             4
#define STATUS_ERROR                5
#define STATUS_LOOPING              6
#define STATUS_LOOP_READY           7

// Define the polling results
#define POLLING_NOCHANGE            0
#define POLLING_FINISHED            1
#define POLLING_ERROR               2

/* for Class Serialize */
#define _SYSCLASSID_                          50000
#define _USERCLASSID_                         0
#define _CLSID_INVALID_                       99999

/* for General Class */
#define _CLSID_EDASOLUTIONLIST_               001

/* for edaHC */
#define _CLSID_EDAMOVEGEN_                    101
#define _CLSID_EDAHCMOVEEXPL_                 102
#define _CLSID_EDAMOVESELECT_                 103
#define _CLSID_EDABESTIMPRSELECT_             104
#define _CLSID_EDAFIRSTIMPRSELECT_            105

/* for edaSA */
#define _CLSID_EXP_COOLING_SCHEDULE_          200
#define _CLSID_LINEAR_COOLING_SCHEDULE_       201

#define _CLSID_GEN_CONTINUE_                  300
#define _CLSID_FIT_CONTINUE_                  301
#define _CLSID_TIME_CONTINUE_                 302
#define _CLSID_VAR_FIT_CONTINUE_              303

/* for edaTS */
#define _CLSID_EDATABULIST_                   400
#define _CLSID_EDATSMOVEEXPL_                 401
#define _CLSID_EDAASPIRCRIT_                  402
#define _CLSID_EDANOASPIRCRIT_                403
#define _CLSID_EDAIMPRBESTFITASPIRCRIT_       404
#define _CLSID_EDASIMPLEMOVETABULIST_         405
#define _CLSID_EDASIMPLESOLUTIONTABULIST_     406

/* for edaGA and edaMA */
#define _CLSID_EDACHROMOSOME_                 501
#define _CLSID_EDAPOPULATION_                 502
#define _CLSID_EDARANKSELECTION_              503
#define _CLSID_EDAROULETTEWHEELSELECTION_     504
#define _CLSID_EDAONEPOINTCROSSOVER_          505
#define _CLSID_EDALAMBDAPOINTCROSSOVER_       506
#define _CLSID_EDARANDOMMUTATION_             507
#define _CLSID_EDAADAPTION_                   508
#define _CLSID_EDAHISTORY_                    509
#define _CLSID_EDAPARTIALLYMATCHEDCROSSOVER_  510
#define _CLSID_EDARANDSWAPMUTATION_           511


/* meta-heuristics */
#define _CLSID_EDAHC_                         600
#define _CLSID_EDASA_                         601
#define _CLSID_EDATS_                         602
#define _CLSID_EDAGA_                         603
#define _CLSID_EDAMA_                         604
#define _CLSID_EDANS_                         605

extern std::ofstream __ofstr;
extern char __logName[256];
extern edaTimer __timer; 
extern char *__progname;
extern int __csvFlag;
extern int __rank__;
extern int __size__;
extern edaRNG rnd;

#ifdef _DEBUG_
#define printDebug(dbglevel, dbg)                           \
   if (dbglevel <= _DEBUG_) {                               \
    cout << dbg << endl;                                    \
  }
#else
#define printDebug(dbglevel, dbg)                           
#endif

#define EDALogProcessStart()                                \
  __timer.start();                                          \
  __csvFlag = -1;                                           \
  sprintf(__logName,"%s.csv", __progname);                  \
  remove (__logName);                                       \
;

#define printCSVLog(heur, task, proc, status, id, gen, list)\
  if(__csvFlag == -1) {                                     \
    if (__rank__ == 1 || __rank__ == 0) {                   \
      __ofstr.open(__logName, ofstream::app);               \
      __ofstr << "Heuristic, Task, Proc, Status, ID, Time," \
      " Fitness, Loop/Gen, Count, Best,"                    \
      " Worst, Mean, Std, Sol/Chro" << endl;                \
      __ofstr.close();                                      \
      __csvFlag = 1;                                        \
    }                                                       \
  }                                                         \
  if(__csvFlag == 1) {                                      \
    __ofstr.open(__logName, ofstream::app);                 \
    __ofstr << heur << ", "                                 \
            << task << ", "                                 \
            << proc << ", "                                 \
            << status << ", "                               \
            << id << ", "                                   \
            << TIME << ", "                                 \
            << list[id]->evaluate() << ", "                 \
            << gen << ", "                                  \
            << list.size() << ", "                          \
            << list.max() << ", "                           \
            << list.min() << ", "                           \
            << list.mean() << ", "                          \
            << list.std() << ", "                           \
            << *list[id] << endl;                           \
    __ofstr.close();                                        \
  }                    
 
#define TIME __timer.stop()                

#define MIN(a,b) (((a)<(b))?(a):(b))

#define MAX(a,b) (((a)>(b))?(a):(b))

#define setClassID( id )                                    \
  virtual int getClassID() const {                          \
    return id;                                              \
  }
#endif /* __edaDefine_h__ */
