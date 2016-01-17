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
CND_PLATFORM=GNU-MacOSX
CND_DLIB_EXT=dylib
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/eda/edaSource.o \
	${OBJECTDIR}/mtsp/lib/mtsp2Opt.o \
	${OBJECTDIR}/mtsp/lib/mtspGenne.o \
	${OBJECTDIR}/mtsp/lib/mtspProblem.o \
	${OBJECTDIR}/mtsp/lib/mtspSolution.o \
	${OBJECTDIR}/mtsp/mtspMain.o \
	${OBJECTDIR}/tsp/lib/tsp2Opt.o \
	${OBJECTDIR}/tsp/lib/tspGenne.o \
	${OBJECTDIR}/tsp/lib/tspInsertion.o \
	${OBJECTDIR}/tsp/lib/tspProblem.o \
	${OBJECTDIR}/tsp/lib/tspSolution.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-D_DEBUG=0 -DDCOMM_MPI
CXXFLAGS=-D_DEBUG=0 -DDCOMM_MPI

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/meta-heuristics-1.3

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/meta-heuristics-1.3: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/meta-heuristics-1.3 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/eda/edaSource.o: eda/edaSource.cpp 
	${MKDIR} -p ${OBJECTDIR}/eda
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/eda/edaSource.o eda/edaSource.cpp

${OBJECTDIR}/mtsp/lib/mtsp2Opt.o: mtsp/lib/mtsp2Opt.cpp 
	${MKDIR} -p ${OBJECTDIR}/mtsp/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mtsp/lib/mtsp2Opt.o mtsp/lib/mtsp2Opt.cpp

${OBJECTDIR}/mtsp/lib/mtspGenne.o: mtsp/lib/mtspGenne.cpp 
	${MKDIR} -p ${OBJECTDIR}/mtsp/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mtsp/lib/mtspGenne.o mtsp/lib/mtspGenne.cpp

${OBJECTDIR}/mtsp/lib/mtspProblem.o: mtsp/lib/mtspProblem.cpp 
	${MKDIR} -p ${OBJECTDIR}/mtsp/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mtsp/lib/mtspProblem.o mtsp/lib/mtspProblem.cpp

${OBJECTDIR}/mtsp/lib/mtspSolution.o: mtsp/lib/mtspSolution.cpp 
	${MKDIR} -p ${OBJECTDIR}/mtsp/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mtsp/lib/mtspSolution.o mtsp/lib/mtspSolution.cpp

${OBJECTDIR}/mtsp/mtspMain.o: mtsp/mtspMain.cpp 
	${MKDIR} -p ${OBJECTDIR}/mtsp
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/mtsp/mtspMain.o mtsp/mtspMain.cpp

${OBJECTDIR}/tsp/lib/tsp2Opt.o: tsp/lib/tsp2Opt.cpp 
	${MKDIR} -p ${OBJECTDIR}/tsp/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tsp/lib/tsp2Opt.o tsp/lib/tsp2Opt.cpp

${OBJECTDIR}/tsp/lib/tspGenne.o: tsp/lib/tspGenne.cpp 
	${MKDIR} -p ${OBJECTDIR}/tsp/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tsp/lib/tspGenne.o tsp/lib/tspGenne.cpp

${OBJECTDIR}/tsp/lib/tspInsertion.o: tsp/lib/tspInsertion.cpp 
	${MKDIR} -p ${OBJECTDIR}/tsp/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tsp/lib/tspInsertion.o tsp/lib/tspInsertion.cpp

${OBJECTDIR}/tsp/lib/tspProblem.o: tsp/lib/tspProblem.cpp 
	${MKDIR} -p ${OBJECTDIR}/tsp/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tsp/lib/tspProblem.o tsp/lib/tspProblem.cpp

${OBJECTDIR}/tsp/lib/tspSolution.o: tsp/lib/tspSolution.cpp 
	${MKDIR} -p ${OBJECTDIR}/tsp/lib
	${RM} "$@.d"
	$(COMPILE.cc) -g -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tsp/lib/tspSolution.o tsp/lib/tspSolution.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/meta-heuristics-1.3

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
