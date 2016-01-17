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
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=Cygwin-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/EDA/edaSource.o \
	${OBJECTDIR}/TSP/tsp2Opt.o \
	${OBJECTDIR}/TSP/tspGASearch.o \
	${OBJECTDIR}/TSP/tspGenne.o \
	${OBJECTDIR}/TSP/tspHCSearch.o \
	${OBJECTDIR}/TSP/tspInsertion.o \
	${OBJECTDIR}/TSP/tspMASearch.o \
	${OBJECTDIR}/TSP/tspProblem.o \
	${OBJECTDIR}/TSP/tspSASearch.o \
	${OBJECTDIR}/TSP/tspSolution.o \
	${OBJECTDIR}/TSP/tspTSSearch.o \
	${OBJECTDIR}/TSP/tspVNSSearch.o \
	${OBJECTDIR}/TSP/tspWF01Search.o \
	${OBJECTDIR}/TSP/tspWF02Search.o \
	${OBJECTDIR}/TSP/tspWF03Search.o \
	${OBJECTDIR}/TSP/tspWF04Search.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/meta-heuristics-1.3.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/meta-heuristics-1.3.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/meta-heuristics-1.3 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/EDA/edaSource.o: EDA/edaSource.cpp 
	${MKDIR} -p ${OBJECTDIR}/EDA
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/EDA/edaSource.o EDA/edaSource.cpp

${OBJECTDIR}/TSP/tsp2Opt.o: TSP/tsp2Opt.cpp 
	${MKDIR} -p ${OBJECTDIR}/TSP
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TSP/tsp2Opt.o TSP/tsp2Opt.cpp

${OBJECTDIR}/TSP/tspGASearch.o: TSP/tspGASearch.cpp 
	${MKDIR} -p ${OBJECTDIR}/TSP
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TSP/tspGASearch.o TSP/tspGASearch.cpp

${OBJECTDIR}/TSP/tspGenne.o: TSP/tspGenne.cpp 
	${MKDIR} -p ${OBJECTDIR}/TSP
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TSP/tspGenne.o TSP/tspGenne.cpp

${OBJECTDIR}/TSP/tspHCSearch.o: TSP/tspHCSearch.cpp 
	${MKDIR} -p ${OBJECTDIR}/TSP
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TSP/tspHCSearch.o TSP/tspHCSearch.cpp

${OBJECTDIR}/TSP/tspInsertion.o: TSP/tspInsertion.cpp 
	${MKDIR} -p ${OBJECTDIR}/TSP
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TSP/tspInsertion.o TSP/tspInsertion.cpp

${OBJECTDIR}/TSP/tspMASearch.o: TSP/tspMASearch.cpp 
	${MKDIR} -p ${OBJECTDIR}/TSP
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TSP/tspMASearch.o TSP/tspMASearch.cpp

${OBJECTDIR}/TSP/tspProblem.o: TSP/tspProblem.cpp 
	${MKDIR} -p ${OBJECTDIR}/TSP
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TSP/tspProblem.o TSP/tspProblem.cpp

${OBJECTDIR}/TSP/tspSASearch.o: TSP/tspSASearch.cpp 
	${MKDIR} -p ${OBJECTDIR}/TSP
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TSP/tspSASearch.o TSP/tspSASearch.cpp

${OBJECTDIR}/TSP/tspSolution.o: TSP/tspSolution.cpp 
	${MKDIR} -p ${OBJECTDIR}/TSP
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TSP/tspSolution.o TSP/tspSolution.cpp

${OBJECTDIR}/TSP/tspTSSearch.o: TSP/tspTSSearch.cpp 
	${MKDIR} -p ${OBJECTDIR}/TSP
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TSP/tspTSSearch.o TSP/tspTSSearch.cpp

${OBJECTDIR}/TSP/tspVNSSearch.o: TSP/tspVNSSearch.cpp 
	${MKDIR} -p ${OBJECTDIR}/TSP
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TSP/tspVNSSearch.o TSP/tspVNSSearch.cpp

${OBJECTDIR}/TSP/tspWF01Search.o: TSP/tspWF01Search.cpp 
	${MKDIR} -p ${OBJECTDIR}/TSP
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TSP/tspWF01Search.o TSP/tspWF01Search.cpp

${OBJECTDIR}/TSP/tspWF02Search.o: TSP/tspWF02Search.cpp 
	${MKDIR} -p ${OBJECTDIR}/TSP
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TSP/tspWF02Search.o TSP/tspWF02Search.cpp

${OBJECTDIR}/TSP/tspWF03Search.o: TSP/tspWF03Search.cpp 
	${MKDIR} -p ${OBJECTDIR}/TSP
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TSP/tspWF03Search.o TSP/tspWF03Search.cpp

${OBJECTDIR}/TSP/tspWF04Search.o: TSP/tspWF04Search.cpp 
	${MKDIR} -p ${OBJECTDIR}/TSP
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/TSP/tspWF04Search.o TSP/tspWF04Search.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/meta-heuristics-1.3.exe

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
