CXX = mpic++
OBJSPATH = ../objs/
CXXFLAGS = -Wall -D_DEBUG_=3 -O -g
MPIFLAGS = -Wall -D_DEBUG_=3 -O -g -DCOMM_MPI
LDFLAGS = -O -g -L${OBJSPATH} -ltsp -lmetasearch

SOURCES = \
			tspTwoOptNext.cpp\
			tspTwoOptMoveRandom.cpp\
			tspTwoOpt.cpp\
			tspOrOpt.cpp\
			tspOrOptNext.cpp\
			tspOrOptRand.cpp\
			tspSolution.cpp\
			tspRepresentation.cpp\
			tspGenne.cpp\
			graph.cpp
	
OBJS=$(patsubst %.cpp,${OBJSPATH}%.o,${SOURCES})

tspHCTwoOptSearchSource = tspHCTwoOptSearch.cpp
tspHCOrOptSearchSource = tspHCOrOptSearch.cpp
tspSASearchSource = tspSASearch.cpp
tspTSSearchSource = tspTSSearch.cpp
tspGASearchSource = tspGASearch.cpp
tspMASearchSource = tspMASearch.cpp
tspVariableSearchSource = tspVariableSearch.cpp
tspSEQSearch01Source = tspSEQSearch01.cpp	
tspSEQSearch02Source = tspSEQSearch02.cpp	
tspSEQSearch03Source = tspSEQSearch03.cpp	
tspSEQSearch04Source = tspSEQSearch04.cpp	
tspMPISearch01Source = tspMPISearch01.cpp
tspMPISearch02Source = tspMPISearch02.cpp
tspMPISearch03Source = tspMPISearch03.cpp
tspMPISearch04Source = tspMPISearch04.cpp
tspMPIMASearchSource = tspMPIMASearch.cpp

all: sequential parallel

parallel: CXXFLAGS = ${MPIFLAGS}

sequential: tspHCTwoOptSearch tspHCOrOptSearch tspSASearch tspTSSearch tspGASearch tspMASearch \
	tspSEQSearch01 tspSEQSearch02 tspSEQSearch03 tspSEQSearch04 tspVariableSearch

parallel: tspMPISearch01 tspMPISearch02 tspMPISearch03 tspMPISearch04 tspMPIMASearch

${OBJSPATH}libtsp.a: ${OBJS}
	ar rcs $@ ${OBJS} 

${OBJSPATH}%.o: %.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $<	

tspHCTwoOptSearch:${OBJSPATH}$(tspHCTwoOptSearchSource:.cpp=.o) ${OBJSPATH}libtsp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f tspHCTwoOptSearch ../run

tspHCOrOptSearch:${OBJSPATH}$(tspHCOrOptSearchSource:.cpp=.o) ${OBJSPATH}libtsp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f tspHCOrOptSearch ../run
	
tspSASearch:${OBJSPATH}$(tspSASearchSource:.cpp=.o) ${OBJSPATH}libtsp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f tspSASearch ../run
	
tspTSSearch:${OBJSPATH}$(tspTSSearchSource:.cpp=.o) ${OBJSPATH}libtsp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f tspTSSearch ../run
	
tspGASearch:${OBJSPATH}$(tspGASearchSource:.cpp=.o) ${OBJSPATH}libtsp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f tspGASearch ../run
	
tspMASearch:${OBJSPATH}$(tspMASearchSource:.cpp=.o) ${OBJSPATH}libtsp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f tspMASearch ../run

tspVariableSearch:${OBJSPATH}$(tspVariableSearchSource:.cpp=.o) ${OBJSPATH}libtsp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f tspVariableSearch ../run

tspSEQSearch01:${OBJSPATH}$(tspSEQSearch01Source:.cpp=.o) ${OBJSPATH}libtsp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f tspSEQSearch01 ../run

tspSEQSearch02:${OBJSPATH}$(tspSEQSearch02Source:.cpp=.o) ${OBJSPATH}libtsp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f tspSEQSearch02 ../run

tspSEQSearch03:${OBJSPATH}$(tspSEQSearch03Source:.cpp=.o) ${OBJSPATH}libtsp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f tspSEQSearch03 ../run

tspSEQSearch04:${OBJSPATH}$(tspSEQSearch04Source:.cpp=.o) ${OBJSPATH}libtsp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f tspSEQSearch04 ../run
	
tspMPISearch01:${OBJSPATH}$(tspMPISearch01Source:.cpp=.o) ${OBJSPATH}libtsp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f tspMPISearch01 ../run	
	
tspMPISearch02:${OBJSPATH}$(tspMPISearch02Source:.cpp=.o) ${OBJSPATH}libtsp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f tspMPISearch02 ../run	

tspMPISearch03:${OBJSPATH}$(tspMPISearch03Source:.cpp=.o) ${OBJSPATH}libtsp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f tspMPISearch03 ../run	

tspMPISearch04:${OBJSPATH}$(tspMPISearch04Source:.cpp=.o) ${OBJSPATH}libtsp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f tspMPISearch04 ../run	
	
tspMPIMASearch:${OBJSPATH}$(tspMPIMASearchSource:.cpp=.o) ${OBJSPATH}libtsp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f tspMPIMASearch ../run	
	
clean:
	@rm -rf ${OBJS} *~ libtsp.a
	@rm -rf ${OBJSPATH}tsp*.o ${OBJSPATH}*~ ${OBJSPATH}libtsp.a 
	@rm -f ../run/tsp*Search*
