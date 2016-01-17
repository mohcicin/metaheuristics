CXX = g++
OBJSPATH = ../objs/
LIBPATH = ./lib/
RUNPATH = ../run
CXXFLAGS = -Wall -D_DEBUG=0 -O -g
LDFLAGS = -O -g -L${OBJSPATH} -lmtsp -lmetasearch

SOURCES = 	mtsp2Opt.cpp\
			mtspSolution.cpp\
			mtspGenne.cpp\
			mtspSolution.cpp\
			mtspProblem.cpp
	
OBJS=$(patsubst %.cpp,${OBJSPATH}%.o,${SOURCES})

mtspMainSource = mtspMain.cpp

all: mtspMain

mtspMain:${OBJSPATH}$(mtspMainSource:.cpp=.o) ${OBJSPATH}libmtsp.a
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}	
	@mv -f mtspMain ${RUNPATH}

${OBJSPATH}$(mtspMainSource:.cpp=.o): ${mtspMainSource}
	${CXX} ${CXXFLAGS} -c -o $@ $<

${OBJSPATH}libmtsp.a: ${OBJS}
	ar rcs $@ ${OBJS} 
	
${OBJSPATH}%.o: ${LIBPATH}%.cpp
	${CXX} ${CXXFLAGS} -c -o $@ $<
	
	
clean:
	@rm -rf ${OBJS} *~ libmtsp.a
	@rm -rf ${OBJSPATH}mtsp*.o ${OBJSPATH}mtsp*.obj ${OBJSPATH}*~ ${OBJSPATH}libmtsp.a 
	@rm -f ../run/mtspMain
	
