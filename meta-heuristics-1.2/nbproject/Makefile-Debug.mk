#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=mpic++
CXX=mpic++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=Cygwin-Windows
CND_DLIB_EXT=dll
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/air/Define.o \
	${OBJECTDIR}/air/airControl.o \
	${OBJECTDIR}/air/airCrossover.o \
	${OBJECTDIR}/air/airFoil.o \
	${OBJECTDIR}/air/airGenne.o \
	${OBJECTDIR}/air/airMesh.o \
	${OBJECTDIR}/air/airNeighbourMove.o \
	${OBJECTDIR}/air/airNeighbourNext.o \
	${OBJECTDIR}/air/airNeighbourRand.o \
	${OBJECTDIR}/air/airProblem.o \
	${OBJECTDIR}/air/airRepresentation.o \
	${OBJECTDIR}/air/airSolution.o \
	${OBJECTDIR}/air/airSolver.o \
	${OBJECTDIR}/lib/edaAdaption.o \
	${OBJECTDIR}/lib/edaBestImprSelect.o \
	${OBJECTDIR}/lib/edaBestSelectWrapper.o \
	${OBJECTDIR}/lib/edaBuffer.o \
	${OBJECTDIR}/lib/edaChromosome.o \
	${OBJECTDIR}/lib/edaCluster.o \
	${OBJECTDIR}/lib/edaContinue.o \
	${OBJECTDIR}/lib/edaCoolingSchedule.o \
	${OBJECTDIR}/lib/edaCrossover.o \
	${OBJECTDIR}/lib/edaDAGEdge.o \
	${OBJECTDIR}/lib/edaDAGVertex.o \
	${OBJECTDIR}/lib/edaDefine.o \
	${OBJECTDIR}/lib/edaExpCoolingSchedule.o \
	${OBJECTDIR}/lib/edaFirstImprSelect.o \
	${OBJECTDIR}/lib/edaFitContinue.o \
	${OBJECTDIR}/lib/edaFullSelectWrapper.o \
	${OBJECTDIR}/lib/edaGA.o \
	${OBJECTDIR}/lib/edaGenContinue.o \
	${OBJECTDIR}/lib/edaGenne.o \
	${OBJECTDIR}/lib/edaHC.o \
	${OBJECTDIR}/lib/edaHCMoveExpl.o \
	${OBJECTDIR}/lib/edaIDSelectWrapper.o \
	${OBJECTDIR}/lib/edaINIReader.o \
	${OBJECTDIR}/lib/edaImprBestFitAspirCrit.o \
	${OBJECTDIR}/lib/edaLambdaPointCrossover.o \
	${OBJECTDIR}/lib/edaLinearCoolingSchedule.o \
	${OBJECTDIR}/lib/edaMA.o \
	${OBJECTDIR}/lib/edaMove.o \
	${OBJECTDIR}/lib/edaMpiWorker.o \
	${OBJECTDIR}/lib/edaMpiWrapperControl.o \
	${OBJECTDIR}/lib/edaMutation.o \
	${OBJECTDIR}/lib/edaNS.o \
	${OBJECTDIR}/lib/edaNaturalSelection.o \
	${OBJECTDIR}/lib/edaNoAspirCrit.o \
	${OBJECTDIR}/lib/edaNoSelectWapper.o \
	${OBJECTDIR}/lib/edaOnePointCrossover.o \
	${OBJECTDIR}/lib/edaPartiallyMatchedCrossover.o \
	${OBJECTDIR}/lib/edaPopulation.o \
	${OBJECTDIR}/lib/edaProblem.o \
	${OBJECTDIR}/lib/edaRNG.o \
	${OBJECTDIR}/lib/edaRandSwapMutation.o \
	${OBJECTDIR}/lib/edaRandomMutation.o \
	${OBJECTDIR}/lib/edaRankSelection.o \
	${OBJECTDIR}/lib/edaRepresentation.o \
	${OBJECTDIR}/lib/edaRouletteWheelSelection.o \
	${OBJECTDIR}/lib/edaSA.o \
	${OBJECTDIR}/lib/edaSearch.o \
	${OBJECTDIR}/lib/edaSearchWrapper.o \
	${OBJECTDIR}/lib/edaSeqSearchWrapper.o \
	${OBJECTDIR}/lib/edaSeqWrapperControl.o \
	${OBJECTDIR}/lib/edaSequentialControl.o \
	${OBJECTDIR}/lib/edaSerialize.o \
	${OBJECTDIR}/lib/edaSimpleMoveTabuList.o \
	${OBJECTDIR}/lib/edaSimpleSolutionTabuList.o \
	${OBJECTDIR}/lib/edaSolution.o \
	${OBJECTDIR}/lib/edaSolutionList.o \
	${OBJECTDIR}/lib/edaString.o \
	${OBJECTDIR}/lib/edaTS.o \
	${OBJECTDIR}/lib/edaTSMoveExpl.o \
	${OBJECTDIR}/lib/edaTimeContinue.o \
	${OBJECTDIR}/lib/edaTimer.o \
	${OBJECTDIR}/lib/edaVarFitContinue.o \
	${OBJECTDIR}/lib/edaWrapperControl.o \
	${OBJECTDIR}/lib/edaWriter.o \
	${OBJECTDIR}/lib/ini.o \
	${OBJECTDIR}/tsp/graph.o \
	${OBJECTDIR}/tsp/tspGenne.o \
	${OBJECTDIR}/tsp/tspKOpt.o \
	${OBJECTDIR}/tsp/tspKOptNext.o \
	${OBJECTDIR}/tsp/tspKOptRand.o \
	${OBJECTDIR}/tsp/tspMPISearch02.o \
	${OBJECTDIR}/tsp/tspOrOpt.o \
	${OBJECTDIR}/tsp/tspOrOptNext.o \
	${OBJECTDIR}/tsp/tspOrOptRand.o \
	${OBJECTDIR}/tsp/tspRepresentation.o \
	${OBJECTDIR}/tsp/tspSolution.o \
	${OBJECTDIR}/tsp/tspTwoOpt.o \
	${OBJECTDIR}/tsp/tspTwoOptMoveRandom.o \
	${OBJECTDIR}/tsp/tspTwoOptNext.o \
	${OBJECTDIR}/vrp/vrpConst.o \
	${OBJECTDIR}/vrp/vrpContinue.o \
	${OBJECTDIR}/vrp/vrpCyclicMove.o \
	${OBJECTDIR}/vrp/vrpCyclicNext.o \
	${OBJECTDIR}/vrp/vrpCyclicRand.o \
	${OBJECTDIR}/vrp/vrpGenne.o \
	${OBJECTDIR}/vrp/vrpGroupConflict.o \
	${OBJECTDIR}/vrp/vrpInterchangeMove.o \
	${OBJECTDIR}/vrp/vrpInterchangeNext.o \
	${OBJECTDIR}/vrp/vrpInterchangeRand.o \
	${OBJECTDIR}/vrp/vrpProblem.o \
	${OBJECTDIR}/vrp/vrpRepresentation.o \
	${OBJECTDIR}/vrp/vrpRoute.o \
	${OBJECTDIR}/vrp/vrpRouteMove.o \
	${OBJECTDIR}/vrp/vrpRouteNext.o \
	${OBJECTDIR}/vrp/vrpSolution.o \
	${OBJECTDIR}/vrp/vrpStop.o \
	${OBJECTDIR}/vrp/vrpSubRoute.o \
	${OBJECTDIR}/vrp/vrpSubRouteMove.o \
	${OBJECTDIR}/vrp/vrpSubRouteNext.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-DCOMM_MPI
CXXFLAGS=-DCOMM_MPI

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/meta-heuristics-1.2.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/meta-heuristics-1.2.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/meta-heuristics-1.2 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/air/Define.o: air/Define.cpp 
	${MKDIR} -p ${OBJECTDIR}/air
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/air/Define.o air/Define.cpp

${OBJECTDIR}/air/airControl.o: air/airControl.cpp 
	${MKDIR} -p ${OBJECTDIR}/air
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/air/airControl.o air/airControl.cpp

${OBJECTDIR}/air/airCrossover.o: air/airCrossover.cpp 
	${MKDIR} -p ${OBJECTDIR}/air
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/air/airCrossover.o air/airCrossover.cpp

${OBJECTDIR}/air/airFoil.o: air/airFoil.cpp 
	${MKDIR} -p ${OBJECTDIR}/air
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/air/airFoil.o air/airFoil.cpp

${OBJECTDIR}/air/airGenne.o: air/airGenne.cpp 
	${MKDIR} -p ${OBJECTDIR}/air
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/air/airGenne.o air/airGenne.cpp

${OBJECTDIR}/air/airMesh.o: air/airMesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/air
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/air/airMesh.o air/airMesh.cpp

${OBJECTDIR}/air/airNeighbourMove.o: air/airNeighbourMove.cpp 
	${MKDIR} -p ${OBJECTDIR}/air
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/air/airNeighbourMove.o air/airNeighbourMove.cpp

${OBJECTDIR}/air/airNeighbourNext.o: air/airNeighbourNext.cpp 
	${MKDIR} -p ${OBJECTDIR}/air
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/air/airNeighbourNext.o air/airNeighbourNext.cpp

${OBJECTDIR}/air/airNeighbourRand.o: air/airNeighbourRand.cpp 
	${MKDIR} -p ${OBJECTDIR}/air
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/air/airNeighbourRand.o air/airNeighbourRand.cpp

${OBJECTDIR}/air/airProblem.o: air/airProblem.cpp 
	${MKDIR} -p ${OBJECTDIR}/air
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/air/airProblem.o air/airProblem.cpp

${OBJECTDIR}/air/airRepresentation.o: air/airRepresentation.cpp 
	${MKDIR} -p ${OBJECTDIR}/air
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/air/airRepresentation.o air/airRepresentation.cpp

${OBJECTDIR}/air/airSolution.o: air/airSolution.cpp 
	${MKDIR} -p ${OBJECTDIR}/air
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/air/airSolution.o air/airSolution.cpp

${OBJECTDIR}/air/airSolver.o: air/airSolver.cpp 
	${MKDIR} -p ${OBJECTDIR}/air
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/air/airSolver.o air/airSolver.cpp

${OBJECTDIR}/lib/edaAdaption.o: lib/edaAdaption.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaAdaption.o lib/edaAdaption.cpp

${OBJECTDIR}/lib/edaBestImprSelect.o: lib/edaBestImprSelect.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaBestImprSelect.o lib/edaBestImprSelect.cpp

${OBJECTDIR}/lib/edaBestSelectWrapper.o: lib/edaBestSelectWrapper.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaBestSelectWrapper.o lib/edaBestSelectWrapper.cpp

${OBJECTDIR}/lib/edaBuffer.o: lib/edaBuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaBuffer.o lib/edaBuffer.cpp

${OBJECTDIR}/lib/edaChromosome.o: lib/edaChromosome.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaChromosome.o lib/edaChromosome.cpp

${OBJECTDIR}/lib/edaCluster.o: lib/edaCluster.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaCluster.o lib/edaCluster.cpp

${OBJECTDIR}/lib/edaContinue.o: lib/edaContinue.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaContinue.o lib/edaContinue.cpp

${OBJECTDIR}/lib/edaCoolingSchedule.o: lib/edaCoolingSchedule.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaCoolingSchedule.o lib/edaCoolingSchedule.cpp

${OBJECTDIR}/lib/edaCrossover.o: lib/edaCrossover.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaCrossover.o lib/edaCrossover.cpp

${OBJECTDIR}/lib/edaDAGEdge.o: lib/edaDAGEdge.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaDAGEdge.o lib/edaDAGEdge.cpp

${OBJECTDIR}/lib/edaDAGVertex.o: lib/edaDAGVertex.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaDAGVertex.o lib/edaDAGVertex.cpp

${OBJECTDIR}/lib/edaDefine.o: lib/edaDefine.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaDefine.o lib/edaDefine.cpp

${OBJECTDIR}/lib/edaExpCoolingSchedule.o: lib/edaExpCoolingSchedule.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaExpCoolingSchedule.o lib/edaExpCoolingSchedule.cpp

${OBJECTDIR}/lib/edaFirstImprSelect.o: lib/edaFirstImprSelect.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaFirstImprSelect.o lib/edaFirstImprSelect.cpp

${OBJECTDIR}/lib/edaFitContinue.o: lib/edaFitContinue.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaFitContinue.o lib/edaFitContinue.cpp

${OBJECTDIR}/lib/edaFullSelectWrapper.o: lib/edaFullSelectWrapper.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaFullSelectWrapper.o lib/edaFullSelectWrapper.cpp

${OBJECTDIR}/lib/edaGA.o: lib/edaGA.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaGA.o lib/edaGA.cpp

${OBJECTDIR}/lib/edaGenContinue.o: lib/edaGenContinue.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaGenContinue.o lib/edaGenContinue.cpp

${OBJECTDIR}/lib/edaGenne.o: lib/edaGenne.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaGenne.o lib/edaGenne.cpp

${OBJECTDIR}/lib/edaHC.o: lib/edaHC.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaHC.o lib/edaHC.cpp

${OBJECTDIR}/lib/edaHCMoveExpl.o: lib/edaHCMoveExpl.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaHCMoveExpl.o lib/edaHCMoveExpl.cpp

${OBJECTDIR}/lib/edaIDSelectWrapper.o: lib/edaIDSelectWrapper.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaIDSelectWrapper.o lib/edaIDSelectWrapper.cpp

${OBJECTDIR}/lib/edaINIReader.o: lib/edaINIReader.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaINIReader.o lib/edaINIReader.cpp

${OBJECTDIR}/lib/edaImprBestFitAspirCrit.o: lib/edaImprBestFitAspirCrit.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaImprBestFitAspirCrit.o lib/edaImprBestFitAspirCrit.cpp

${OBJECTDIR}/lib/edaLambdaPointCrossover.o: lib/edaLambdaPointCrossover.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaLambdaPointCrossover.o lib/edaLambdaPointCrossover.cpp

${OBJECTDIR}/lib/edaLinearCoolingSchedule.o: lib/edaLinearCoolingSchedule.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaLinearCoolingSchedule.o lib/edaLinearCoolingSchedule.cpp

${OBJECTDIR}/lib/edaMA.o: lib/edaMA.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaMA.o lib/edaMA.cpp

${OBJECTDIR}/lib/edaMove.o: lib/edaMove.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaMove.o lib/edaMove.cpp

${OBJECTDIR}/lib/edaMpiWorker.o: lib/edaMpiWorker.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaMpiWorker.o lib/edaMpiWorker.cpp

${OBJECTDIR}/lib/edaMpiWrapperControl.o: lib/edaMpiWrapperControl.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaMpiWrapperControl.o lib/edaMpiWrapperControl.cpp

${OBJECTDIR}/lib/edaMutation.o: lib/edaMutation.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaMutation.o lib/edaMutation.cpp

${OBJECTDIR}/lib/edaNS.o: lib/edaNS.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaNS.o lib/edaNS.cpp

${OBJECTDIR}/lib/edaNaturalSelection.o: lib/edaNaturalSelection.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaNaturalSelection.o lib/edaNaturalSelection.cpp

${OBJECTDIR}/lib/edaNoAspirCrit.o: lib/edaNoAspirCrit.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaNoAspirCrit.o lib/edaNoAspirCrit.cpp

${OBJECTDIR}/lib/edaNoSelectWapper.o: lib/edaNoSelectWapper.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaNoSelectWapper.o lib/edaNoSelectWapper.cpp

${OBJECTDIR}/lib/edaOnePointCrossover.o: lib/edaOnePointCrossover.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaOnePointCrossover.o lib/edaOnePointCrossover.cpp

${OBJECTDIR}/lib/edaPartiallyMatchedCrossover.o: lib/edaPartiallyMatchedCrossover.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaPartiallyMatchedCrossover.o lib/edaPartiallyMatchedCrossover.cpp

${OBJECTDIR}/lib/edaPopulation.o: lib/edaPopulation.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaPopulation.o lib/edaPopulation.cpp

${OBJECTDIR}/lib/edaProblem.o: lib/edaProblem.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaProblem.o lib/edaProblem.cpp

${OBJECTDIR}/lib/edaRNG.o: lib/edaRNG.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaRNG.o lib/edaRNG.cpp

${OBJECTDIR}/lib/edaRandSwapMutation.o: lib/edaRandSwapMutation.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaRandSwapMutation.o lib/edaRandSwapMutation.cpp

${OBJECTDIR}/lib/edaRandomMutation.o: lib/edaRandomMutation.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaRandomMutation.o lib/edaRandomMutation.cpp

${OBJECTDIR}/lib/edaRankSelection.o: lib/edaRankSelection.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaRankSelection.o lib/edaRankSelection.cpp

${OBJECTDIR}/lib/edaRepresentation.o: lib/edaRepresentation.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaRepresentation.o lib/edaRepresentation.cpp

${OBJECTDIR}/lib/edaRouletteWheelSelection.o: lib/edaRouletteWheelSelection.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaRouletteWheelSelection.o lib/edaRouletteWheelSelection.cpp

${OBJECTDIR}/lib/edaSA.o: lib/edaSA.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaSA.o lib/edaSA.cpp

${OBJECTDIR}/lib/edaSearch.o: lib/edaSearch.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaSearch.o lib/edaSearch.cpp

${OBJECTDIR}/lib/edaSearchWrapper.o: lib/edaSearchWrapper.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaSearchWrapper.o lib/edaSearchWrapper.cpp

${OBJECTDIR}/lib/edaSeqSearchWrapper.o: lib/edaSeqSearchWrapper.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaSeqSearchWrapper.o lib/edaSeqSearchWrapper.cpp

${OBJECTDIR}/lib/edaSeqWrapperControl.o: lib/edaSeqWrapperControl.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaSeqWrapperControl.o lib/edaSeqWrapperControl.cpp

${OBJECTDIR}/lib/edaSequentialControl.o: lib/edaSequentialControl.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaSequentialControl.o lib/edaSequentialControl.cpp

${OBJECTDIR}/lib/edaSerialize.o: lib/edaSerialize.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaSerialize.o lib/edaSerialize.cpp

${OBJECTDIR}/lib/edaSimpleMoveTabuList.o: lib/edaSimpleMoveTabuList.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaSimpleMoveTabuList.o lib/edaSimpleMoveTabuList.cpp

${OBJECTDIR}/lib/edaSimpleSolutionTabuList.o: lib/edaSimpleSolutionTabuList.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaSimpleSolutionTabuList.o lib/edaSimpleSolutionTabuList.cpp

${OBJECTDIR}/lib/edaSolution.o: lib/edaSolution.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaSolution.o lib/edaSolution.cpp

${OBJECTDIR}/lib/edaSolutionList.o: lib/edaSolutionList.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaSolutionList.o lib/edaSolutionList.cpp

${OBJECTDIR}/lib/edaString.o: lib/edaString.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaString.o lib/edaString.cpp

${OBJECTDIR}/lib/edaTS.o: lib/edaTS.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaTS.o lib/edaTS.cpp

${OBJECTDIR}/lib/edaTSMoveExpl.o: lib/edaTSMoveExpl.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaTSMoveExpl.o lib/edaTSMoveExpl.cpp

${OBJECTDIR}/lib/edaTimeContinue.o: lib/edaTimeContinue.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaTimeContinue.o lib/edaTimeContinue.cpp

${OBJECTDIR}/lib/edaTimer.o: lib/edaTimer.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaTimer.o lib/edaTimer.cpp

${OBJECTDIR}/lib/edaVarFitContinue.o: lib/edaVarFitContinue.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaVarFitContinue.o lib/edaVarFitContinue.cpp

${OBJECTDIR}/lib/edaWrapperControl.o: lib/edaWrapperControl.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaWrapperControl.o lib/edaWrapperControl.cpp

${OBJECTDIR}/lib/edaWriter.o: lib/edaWriter.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/edaWriter.o lib/edaWriter.cpp

${OBJECTDIR}/lib/ini.o: lib/ini.cpp 
	${MKDIR} -p ${OBJECTDIR}/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/ini.o lib/ini.cpp

${OBJECTDIR}/tsp/graph.o: tsp/graph.cpp 
	${MKDIR} -p ${OBJECTDIR}/tsp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tsp/graph.o tsp/graph.cpp

${OBJECTDIR}/tsp/tspGenne.o: tsp/tspGenne.cpp 
	${MKDIR} -p ${OBJECTDIR}/tsp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tsp/tspGenne.o tsp/tspGenne.cpp

${OBJECTDIR}/tsp/tspKOpt.o: tsp/tspKOpt.cpp 
	${MKDIR} -p ${OBJECTDIR}/tsp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tsp/tspKOpt.o tsp/tspKOpt.cpp

${OBJECTDIR}/tsp/tspKOptNext.o: tsp/tspKOptNext.cpp 
	${MKDIR} -p ${OBJECTDIR}/tsp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tsp/tspKOptNext.o tsp/tspKOptNext.cpp

${OBJECTDIR}/tsp/tspKOptRand.o: tsp/tspKOptRand.cpp 
	${MKDIR} -p ${OBJECTDIR}/tsp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tsp/tspKOptRand.o tsp/tspKOptRand.cpp

${OBJECTDIR}/tsp/tspMPISearch02.o: tsp/tspMPISearch02.cpp 
	${MKDIR} -p ${OBJECTDIR}/tsp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tsp/tspMPISearch02.o tsp/tspMPISearch02.cpp

${OBJECTDIR}/tsp/tspOrOpt.o: tsp/tspOrOpt.cpp 
	${MKDIR} -p ${OBJECTDIR}/tsp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tsp/tspOrOpt.o tsp/tspOrOpt.cpp

${OBJECTDIR}/tsp/tspOrOptNext.o: tsp/tspOrOptNext.cpp 
	${MKDIR} -p ${OBJECTDIR}/tsp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tsp/tspOrOptNext.o tsp/tspOrOptNext.cpp

${OBJECTDIR}/tsp/tspOrOptRand.o: tsp/tspOrOptRand.cpp 
	${MKDIR} -p ${OBJECTDIR}/tsp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tsp/tspOrOptRand.o tsp/tspOrOptRand.cpp

${OBJECTDIR}/tsp/tspRepresentation.o: tsp/tspRepresentation.cpp 
	${MKDIR} -p ${OBJECTDIR}/tsp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tsp/tspRepresentation.o tsp/tspRepresentation.cpp

${OBJECTDIR}/tsp/tspSolution.o: tsp/tspSolution.cpp 
	${MKDIR} -p ${OBJECTDIR}/tsp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tsp/tspSolution.o tsp/tspSolution.cpp

${OBJECTDIR}/tsp/tspTwoOpt.o: tsp/tspTwoOpt.cpp 
	${MKDIR} -p ${OBJECTDIR}/tsp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tsp/tspTwoOpt.o tsp/tspTwoOpt.cpp

${OBJECTDIR}/tsp/tspTwoOptMoveRandom.o: tsp/tspTwoOptMoveRandom.cpp 
	${MKDIR} -p ${OBJECTDIR}/tsp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tsp/tspTwoOptMoveRandom.o tsp/tspTwoOptMoveRandom.cpp

${OBJECTDIR}/tsp/tspTwoOptNext.o: tsp/tspTwoOptNext.cpp 
	${MKDIR} -p ${OBJECTDIR}/tsp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tsp/tspTwoOptNext.o tsp/tspTwoOptNext.cpp

${OBJECTDIR}/vrp/vrpConst.o: vrp/vrpConst.cpp 
	${MKDIR} -p ${OBJECTDIR}/vrp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vrp/vrpConst.o vrp/vrpConst.cpp

${OBJECTDIR}/vrp/vrpContinue.o: vrp/vrpContinue.cpp 
	${MKDIR} -p ${OBJECTDIR}/vrp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vrp/vrpContinue.o vrp/vrpContinue.cpp

${OBJECTDIR}/vrp/vrpCyclicMove.o: vrp/vrpCyclicMove.cpp 
	${MKDIR} -p ${OBJECTDIR}/vrp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vrp/vrpCyclicMove.o vrp/vrpCyclicMove.cpp

${OBJECTDIR}/vrp/vrpCyclicNext.o: vrp/vrpCyclicNext.cpp 
	${MKDIR} -p ${OBJECTDIR}/vrp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vrp/vrpCyclicNext.o vrp/vrpCyclicNext.cpp

${OBJECTDIR}/vrp/vrpCyclicRand.o: vrp/vrpCyclicRand.cpp 
	${MKDIR} -p ${OBJECTDIR}/vrp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vrp/vrpCyclicRand.o vrp/vrpCyclicRand.cpp

${OBJECTDIR}/vrp/vrpGenne.o: vrp/vrpGenne.cpp 
	${MKDIR} -p ${OBJECTDIR}/vrp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vrp/vrpGenne.o vrp/vrpGenne.cpp

${OBJECTDIR}/vrp/vrpGroupConflict.o: vrp/vrpGroupConflict.cpp 
	${MKDIR} -p ${OBJECTDIR}/vrp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vrp/vrpGroupConflict.o vrp/vrpGroupConflict.cpp

${OBJECTDIR}/vrp/vrpInterchangeMove.o: vrp/vrpInterchangeMove.cpp 
	${MKDIR} -p ${OBJECTDIR}/vrp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vrp/vrpInterchangeMove.o vrp/vrpInterchangeMove.cpp

${OBJECTDIR}/vrp/vrpInterchangeNext.o: vrp/vrpInterchangeNext.cpp 
	${MKDIR} -p ${OBJECTDIR}/vrp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vrp/vrpInterchangeNext.o vrp/vrpInterchangeNext.cpp

${OBJECTDIR}/vrp/vrpInterchangeRand.o: vrp/vrpInterchangeRand.cpp 
	${MKDIR} -p ${OBJECTDIR}/vrp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vrp/vrpInterchangeRand.o vrp/vrpInterchangeRand.cpp

${OBJECTDIR}/vrp/vrpProblem.o: vrp/vrpProblem.cpp 
	${MKDIR} -p ${OBJECTDIR}/vrp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vrp/vrpProblem.o vrp/vrpProblem.cpp

${OBJECTDIR}/vrp/vrpRepresentation.o: vrp/vrpRepresentation.cpp 
	${MKDIR} -p ${OBJECTDIR}/vrp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vrp/vrpRepresentation.o vrp/vrpRepresentation.cpp

${OBJECTDIR}/vrp/vrpRoute.o: vrp/vrpRoute.cpp 
	${MKDIR} -p ${OBJECTDIR}/vrp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vrp/vrpRoute.o vrp/vrpRoute.cpp

${OBJECTDIR}/vrp/vrpRouteMove.o: vrp/vrpRouteMove.cpp 
	${MKDIR} -p ${OBJECTDIR}/vrp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vrp/vrpRouteMove.o vrp/vrpRouteMove.cpp

${OBJECTDIR}/vrp/vrpRouteNext.o: vrp/vrpRouteNext.cpp 
	${MKDIR} -p ${OBJECTDIR}/vrp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vrp/vrpRouteNext.o vrp/vrpRouteNext.cpp

${OBJECTDIR}/vrp/vrpSolution.o: vrp/vrpSolution.cpp 
	${MKDIR} -p ${OBJECTDIR}/vrp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vrp/vrpSolution.o vrp/vrpSolution.cpp

${OBJECTDIR}/vrp/vrpStop.o: vrp/vrpStop.cpp 
	${MKDIR} -p ${OBJECTDIR}/vrp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vrp/vrpStop.o vrp/vrpStop.cpp

${OBJECTDIR}/vrp/vrpSubRoute.o: vrp/vrpSubRoute.cpp 
	${MKDIR} -p ${OBJECTDIR}/vrp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vrp/vrpSubRoute.o vrp/vrpSubRoute.cpp

${OBJECTDIR}/vrp/vrpSubRouteMove.o: vrp/vrpSubRouteMove.cpp 
	${MKDIR} -p ${OBJECTDIR}/vrp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vrp/vrpSubRouteMove.o vrp/vrpSubRouteMove.cpp

${OBJECTDIR}/vrp/vrpSubRouteNext.o: vrp/vrpSubRouteNext.cpp 
	${MKDIR} -p ${OBJECTDIR}/vrp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/vrp/vrpSubRouteNext.o vrp/vrpSubRouteNext.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/meta-heuristics-1.2.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
