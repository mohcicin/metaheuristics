CXX = mpic++
OBJSPATH = ../objs/
CXXFLAGS = -D_DEBUG_=3 -Wall -O -g
SOURCES=\
		edaAdaption.cpp\
		edaBestImprSelect.cpp\
		edaBestSelectWrapper.cpp\
		edaBuffer.cpp\
		edaChromosome.cpp\
		edaCluster.cpp\
		edaContinue.cpp\
		edaCoolingSchedule.cpp\
		edaCrossover.cpp\
		edaDAGEdge.cpp\
		edaDAGVertex.cpp\
		edaDefine.cpp\
		edaExpCoolingSchedule.cpp\
		edaFirstImprSelect.cpp\
		edaFitContinue.cpp\
		edaFullSelectWrapper.cpp\
		edaGA.cpp\
		edaGenContinue.cpp\
		edaGenne.cpp\
		edaHC.cpp\
		edaHCMoveExpl.cpp\
		edaIDSelectWrapper.cpp\
		edaImprBestFitAspirCrit.cpp\
		edaINIReader.cpp\
		edaLambdaPointCrossover.cpp\
		edaLinearCoolingSchedule.cpp\
		edaMA.cpp\
		edaMove.cpp\
		edaMpiWorker.cpp\
		edaMpiWrapperControl.cpp\
		edaMutation.cpp\
		edaNoAspirCrit.cpp\
		edaNoSelectWapper.cpp\
		edaOnePointCrossover.cpp\
		edaPartiallyMatchedCrossover.cpp\
		edaPopulation.cpp\
		edaProblem.cpp\
		edaRandomMutation.cpp\
		edaRandSwapMutation.cpp\
		edaRankSelection.cpp\
		edaRepresentation.cpp\
		edaRouletteWheelSelection.cpp\
		edaSA.cpp\
		edaSearch.cpp\
		edaNS.cpp\
		edaSearchWrapper.cpp\
		edaNaturalSelection.cpp\
		edaSeqSearchWrapper.cpp\
		edaSequentialControl.cpp\
		edaSeqWrapperControl.cpp\
		edaSerialize.cpp\
		edaSimpleMoveTabuList.cpp\
		edaSimpleSolutionTabuList.cpp\
		edaSolution.cpp\
		edaSolutionList.cpp\
		edaTimeContinue.cpp\
		edaTimer.cpp\
		edaTS.cpp\
		edaTSMoveExpl.cpp\
		edaVarFitContinue.cpp\
		edaWrapperControl.cpp\
		ini.cpp\
		edaRNG.cpp

OBJS=${SOURCES:.cpp=.o}
all: libmetasearch.a move

libmetasearch.a: ${OBJS}
	ar rcs $@ ${OBJS}

.cpp\.o:
	${CXX} ${CXXFLAGS} -c -o $@ $<
move:
	@mv -f ${OBJS} ${OBJSPATH}
	@mv -f libmetasearch.a ${OBJSPATH}
clean:
	@rm -rf ${OBJS} *~ libmetasearch.a
	@rm -rf ${OBJSPATH}eda*.o ${OBJSPATH}rng.o ${OBJSPATH}ini.o ${OBJSPATH}*~ ${OBJSPATH}libmetasearch.a


