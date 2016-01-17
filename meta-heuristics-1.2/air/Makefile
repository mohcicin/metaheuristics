CXX = mpic++
OBJSPATH = ../objs/
CXXFLAGS = -Wall -D_DEBUG_=3 -O -g
MPIFLAGS = -Wall -D_DEBUG_=3 -O -g -DCOMM_MPI
LDFLAGS = -O -g -L${OBJSPATH} -lair -lmetasearch

SOURCES=\
	airControl.cpp\
	airFoil.cpp\
	airGenne.cpp\
	airMesh.cpp\
	airNeighbourMove.cpp\
	airNeighbourNext.cpp\
	airNeighbourRand.cpp\
	airProblem.cpp\
	airRepresentation.cpp\
	airSolution.cpp\
	airSolver.cpp\
	Define.cpp\
	airCrossover.cpp

	
OBJS=$(patsubst %.cpp,${OBJSPATH}%.o,${SOURCES})

airSEQMASearchSource = airSEQMASearch.cpp
airMPIMASearchSource = airMPIMASearch.cpp
airRAE2822Source = airRAE2822.cpp
	
all: sequential parallel rae2822

parallel: CXXFLAGS = ${MPIFLAGS}

sequential: airSEQMASearch

parallel: airMPIMASearch

rae2822: airRAE2822

${OBJSPATH}libair.a: ${OBJS}
	ar rcs $@ ${OBJS} 

${OBJSPATH}%.o: %.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $<

airSEQMASearch:${OBJSPATH}$(airSEQMASearchSource:.cpp=.o) ${OBJSPATH}libair.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f airSEQMASearch ../run
	
airMPIMASearch:${OBJSPATH}$(airMPIMASearchSource:.cpp=.o) ${OBJSPATH}libair.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f airMPIMASearch ../run
	
airRAE2822:${OBJSPATH}$(airRAE2822Source:.cpp=.o) ${OBJSPATH}libair.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f airRAE2822 ../run

clean:
	@rm -rf ${OBJS} *~ libair.a
	@rm -rf ${OBJSPATH}air*.o ${OBJSPATH}*~ ${OBJSPATH}libair.a 
	@rm -f ../run/air*Search* ../run/airRAE2822
