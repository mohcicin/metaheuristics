CXX = mpic++
OBJSPATH = ../objs/
CXXFLAGS = -Wall -D_DEBUG_=3 -O -g
MPIFLAGS = -Wall -D_DEBUG_=3 -O -g -DCOMM_MPI
LDFLAGS = -O -g -L${OBJSPATH} -lvrp -lmetasearch

SOURCES=\
	vrpConst.cpp\
	vrpContinue.cpp\
	vrpGenne.cpp\
	vrpGroupConflict.cpp\
	vrpRouteMove.cpp\
	vrpRouteNext.cpp\
	vrpSubRouteMove.cpp\
	vrpSubRouteNext.cpp\
	vrpInterchangeMove.cpp\
	vrpInterchangeNext.cpp\
	vrpInterchangeRand.cpp\
	vrpCyclicNext.cpp\
	vrpCyclicMove.cpp\
	vrpCyclicRand.cpp\
	vrpProblem.cpp\
	vrpRepresentation.cpp\
	vrpRoute.cpp\
	vrpSolution.cpp\
	vrpStop.cpp\
	vrpSubRoute.cpp
	
OBJS=$(patsubst %.cpp,${OBJSPATH}%.o,${SOURCES})

vrpGASearchSource = vrpGASearch.cpp
vrpMASearchSource = vrpMASearch.cpp
vrpTSSearchSource = vrpTSSearch.cpp
vrpSASearchSource = vrpSASearch.cpp
vrpHCInterchangeSearchSource = vrpHCInterchangeSearch.cpp
vrpHCCyclicSearchSource = vrpHCCyclicSearch.cpp
vrpMPISearchSource = vrpMPISearch.cpp
vrpMPIMASearchSource = vrpMPIMASearch.cpp
vrpSEQSearchSource = vrpSEQSearch.cpp
vrpVariableSearchSource = vrpVariableSearch.cpp


all: sequential parallel

sequential: vrpGASearch vrpMASearch vrpTSSearch vrpSASearch vrpHCCyclicSearch vrpHCInterchangeSearch vrpSEQSearch vrpVariableSearch

parallel: CXXFLAGS = ${MPIFLAGS}

parallel: vrpMPISearch vrpMPIMASearch

${OBJSPATH}libvrp.a: ${OBJS}
	ar rcs $@ ${OBJS} 
	
${OBJSPATH}%.o: %.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $<	
	
vrpGASearch:${OBJSPATH}$(vrpGASearchSource:.cpp=.o)	${OBJSPATH}libvrp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f vrpGASearch ../run	

vrpMASearch:${OBJSPATH}$(vrpMASearchSource:.cpp=.o)	${OBJSPATH}libvrp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f vrpMASearch ../run	

vrpTSSearch:${OBJSPATH}$(vrpTSSearchSource:.cpp=.o)	${OBJSPATH}libvrp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f vrpTSSearch ../run

vrpSASearch:${OBJSPATH}$(vrpSASearchSource:.cpp=.o)	${OBJSPATH}libvrp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f vrpSASearch ../run	
	
vrpHCInterchangeSearch:${OBJSPATH}$(vrpHCInterchangeSearchSource:.cpp=.o)	${OBJSPATH}libvrp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f vrpHCInterchangeSearch ../run	
	
vrpHCCyclicSearch:${OBJSPATH}$(vrpHCCyclicSearchSource:.cpp=.o)	${OBJSPATH}libvrp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f vrpHCCyclicSearch ../run	

vrpSEQSearch:${OBJSPATH}$(vrpSEQSearchSource:.cpp=.o) ${OBJSPATH}libvrp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f vrpSEQSearch ../run
	
vrpMPISearch:${OBJSPATH}$(vrpMPISearchSource:.cpp=.o) ${OBJSPATH}libvrp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f vrpMPISearch ../run

vrpMPIMASearch:${OBJSPATH}$(vrpMPIMASearchSource:.cpp=.o) ${OBJSPATH}libvrp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f vrpMPIMASearch ../run

vrpVariableSearch:${OBJSPATH}$(vrpVariableSearchSource:.cpp=.o) ${OBJSPATH}libvrp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f vrpVariableSearch ../run
		
clean:
	@rm -rf ${OBJS} *~ libvrp.a
	@rm -rf ${OBJSPATH}vrp*.o ${OBJSPATH}*~ ${OBJSPATH}libvrp.a
	@rm -f ../run/vrp*Search*
