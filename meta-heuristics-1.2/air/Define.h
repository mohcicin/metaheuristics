/* 
 * File:   define.h
 * Author: Tieu Minh
 *
 * Created on March 6, 2013, 7:32 PM
 */

#ifndef DEFINE_H
#define	DEFINE_H

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
#include "../lib/eda.h"

using namespace std;

#define _CLSID_AIR_PROBLEM_                      0
#define _CLSID_AIR_SOLUTION_                     1
#define _CLSID_AIR_CONTROL_                      2
#define _CLSID_AIR_GENNE_                        3
#define _CLSID_AIR_NEIGHBOURMOVE_                4
#define _CLSID_AIR_NEIGHBOURNEXT_                5
#define _CLSID_AIR_NEIGHBOURRAND_                6
#define _CLSID_AIR_REPRESENTATION_               7
#define _CLSID_AIR_RANPOPGENERATION_             8
#define _CLSID_AIR_SAMPLEPOPGENERATION_          9
#define _CLSID_AIR_MESH_                         10
#define _CLSID_AIR_SOLVER_                       11
#define _CLSID_AIR_FOIL_                         12
#define _CLSID_AIR_CROSSOVER_                    13

#define MIN_VALUE                                -9999

int createFolder(const char* foldername);
int moveData(const char* from, const char* to);
int changeFolder(const char* foldername);
int removeData(const char* folder);
int runCase(const char* command);
int catchCase(const char* data);
int testCase(const char* command);
int runCase(const char* command, unsigned int nodes);
void fprints(FILE *file, const char* object, const char* _class = "dictionary");
void fprinte(FILE *file);
bool findValue(const char* filename, const char* value);
void writeLog(const char* logFile, string content);
unsigned int a2i(char character);
#endif	/* NACADEFINE_H */

