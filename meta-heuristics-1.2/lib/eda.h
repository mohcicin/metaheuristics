#ifndef __eda_h__
#define __eda_h__

#include "edaDefine.h"
#include "edaCommDefine.h"

#include "edaSerialize.h"

#include "edaHC.h"
#include "edaSA.h"
#include "edaTS.h"
#include "edaGA.h"
#include "edaMA.h"
#include "edaNS.h"

#include "edaProblem.h"
#include "edaSolution.h"
#include "edaMove.h"

#include "edaExpCoolingSchedule.h"
#include "edaLinearCoolingSchedule.h"

#include "edaBestImprSelect.h"
#include "edaFirstImprSelect.h"

#include "edaGenContinue.h"
#include "edaFitContinue.h"
#include "edaTimeContinue.h"
#include "edaVarFitContinue.h"

#include "edaSimpleMoveTabuList.h"
#include "edaSimpleSolutionTabuList.h"

#include "edaImprBestFitAspirCrit.h"
#include "edaNoAspirCrit.h"

#include "edaGenne.h"
#include "edaChromosome.h"
#include "edaPopulation.h"
#include "edaNaturalSelection.h"
#include "edaRankSelection.h"
#include "edaRouletteWheelSelection.h"
#include "edaCrossover.h"
#include "edaOnePointCrossover.h"
#include "edaLambdaPointCrossover.h"
#include "edaPartiallyMatchedCrossover.h"
#include "edaRandSwapMutation.h"
#include "edaRandomMutation.h"
#include "edaAdaption.h"
#include "edaMoveGen.h"


#ifdef COMM_MPI
#include "edaMpiWrapperControl.h"
#include "edaMpiWorker.h"
#else
#include "edaSeqWrapperControl.h"
#include "edaSequentialControl.h"
#endif

#include "edaRNG.h"
#include "ini.h"
#include "edaTimer.h"
#include "edaCluster.h"
#include "edaINIReader.h"
#include "edaFullSelectWrapper.h"
#include "edaBestSelectWrapper.h"
#include "edaIDSelectWrapper.h"
#include "edaNoSelectWapper.h"

#endif
