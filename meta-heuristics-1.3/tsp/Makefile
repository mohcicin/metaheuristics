CXX = mpic++
OBJSPATH = ../objs/
RUNPATH = ../run
CXXFLAGS = -Wall -D_DEBUG=0 -O -g
MPIFLAGS = -Wall -D_DEBUG=0 -O -g -DCOMM_MPI
LDFLAGS = -O -g -L${OBJSPATH} -ltsp -lmetasearch

SOURCES = 	tsp2Opt.cpp\
			tspInsertion.cpp\
			tspSolution.cpp\
			tspGenne.cpp\
			tspSolution.cpp\
			tspProblem.cpp
	
OBJS=$(patsubst %.cpp,${OBJSPATH}%.o,${SOURCES})

tspHCSearchSource = tspHCSearch.cpp
tspSASearchSource = tspSASearch.cpp
tspTSSearchSource = tspTSSearch.cpp
tspVNSSearchSource = tspVNSSearch.cpp
tspGASearchSource = tspGASearch.cpp
tspMASearchSource = tspMASearch.cpp
tspWF01SearchSource = tspWF01Search.cpp
tspWF02SearchSource = tspWF02Search.cpp
tspWF03SearchSource = tspWF03Search.cpp
tspWF04SearchSource = tspWF04Search.cpp

all: sequential parallel

parallel: CXXFLAGS = ${MPIFLAGS}

sequential: tspHCSearch tspSASearch tspTSSearch tspVNSSearch tspGASearch tspMASearch tspSEQ01Search tspSEQ02Search tspSEQ03Search tspSEQ04Search

parallel: tspMPI01Search tspMPI02Search tspMPI03Search tspMPI04Search tspMPIMASearch

${OBJSPATH}libtsp.a: ${OBJS}
	ar rcs $@ ${OBJS} 

${OBJSPATH}%.o: %.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $<	

${OBJSPATH}%.obj: %.cpp
	${CXX} ${MPIFLAGS} -c -o $@ $<	

	
tspHCSearch:${OBJSPATH}$(tspHCSearchSource:.cpp=.o) ${OBJSPATH}libtsp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f tspHCSearch ${RUNPATH}

tspSASearch:${OBJSPATH}$(tspSASearchSource:.cpp=.o) ${OBJSPATH}libtsp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f tspSASearch ${RUNPATH}

tspTSSearch:${OBJSPATH}$(tspTSSearchSource:.cpp=.o) ${OBJSPATH}libtsp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f tspTSSearch ${RUNPATH}

tspVNSSearch:${OBJSPATH}$(tspVNSSearchSource:.cpp=.o) ${OBJSPATH}libtsp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f tspVNSSearch ${RUNPATH}

tspGASearch:${OBJSPATH}$(tspGASearchSource:.cpp=.o) ${OBJSPATH}libtsp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f tspGASearch ${RUNPATH}

tspMASearch:${OBJSPATH}$(tspMASearchSource:.cpp=.o) ${OBJSPATH}libtsp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f tspMASearch ${RUNPATH}	
	
tspSEQ01Search:${OBJSPATH}$(tspWF01SearchSource:.cpp=.o) ${OBJSPATH}libtsp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f tspSEQ01Search ${RUNPATH}	

tspSEQ02Search:${OBJSPATH}$(tspWF02SearchSource:.cpp=.o) ${OBJSPATH}libtsp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f tspSEQ02Search ${RUNPATH}	
	
tspSEQ03Search:${OBJSPATH}$(tspWF03SearchSource:.cpp=.o) ${OBJSPATH}libtsp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f tspSEQ03Search ${RUNPATH}		

tspSEQ04Search:${OBJSPATH}$(tspWF04SearchSource:.cpp=.o) ${OBJSPATH}libtsp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f tspSEQ04Search ${RUNPATH}	
	
tspMPIMASearch:${OBJSPATH}$(tspMASearchSource:.cpp=.obj) ${OBJSPATH}libtsp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f tspMPIMASearch ${RUNPATH}	
	
tspMPI01Search:${OBJSPATH}$(tspWF01SearchSource:.cpp=.obj) ${OBJSPATH}libtsp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f tspMPI01Search ${RUNPATH}	

tspMPI02Search:${OBJSPATH}$(tspWF02SearchSource:.cpp=.obj) ${OBJSPATH}libtsp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f tspMPI02Search ${RUNPATH}	
	
tspMPI03Search:${OBJSPATH}$(tspWF03SearchSource:.cpp=.obj) ${OBJSPATH}libtsp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f tspMPI03Search ${RUNPATH}		

tspMPI04Search:${OBJSPATH}$(tspWF04SearchSource:.cpp=.obj) ${OBJSPATH}libtsp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f tspMPI04Search ${RUNPATH}
	
clean:
	@rm -rf ${OBJS} *~ libtsp.a
	@rm -rf ${OBJSPATH}tsp*.o ${OBJSPATH}tsp*.obj ${OBJSPATH}*~ ${OBJSPATH}libtsp.a 
	@rm -f ../run/tsp*Search*
