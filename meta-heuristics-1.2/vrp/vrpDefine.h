/* 
 * File:   vrpConst.h
 * Author: Administrator
 *
 * Created on June 7, 2012, 4:34 PM
 */
#include "../lib/eda.h"

#ifndef VRPDEFINE_H
#define	VRPDEFINE_H

//Define for stop's type
#define DEPOT                                   0
#define LANDFILL                                2
#define REGULAR_STOP                            1

//Define for stop's status
#define ROUTED                                  0
#define UN_ROUTED                               1
#define NON_GROUP                               9999

//Define constant value
#define FEET_TO_MILES                           0.000189393939
#define MAX_NUMBER                              +9999999
#define MIN_NUMBER                              -9999999


//Define userClassGenerate
#define _CLSID_VRP_STOP_                        01
#define _CLSID_VRP_GROUP_CONFLICT_              02
#define _CLSID_VRP_PROBLEM_                     03
#define _CLSID_VRP_SOLUTION_                    04
#define _CLSID_VRP_ROUTE_                       05
#define _CLSID_VRP_SUBROUTE_                    06
#define _CLSID_VRP_CONST_                       07

#define _CLSID_VRP_SUBROUTE_MOVE_               11
#define _CLSID_VRP_SUBROUTE_NEXT_               12
#define _CLSID_VRP_ROUTE_MOVE_                  13
#define _CLSID_VRP_ROUTE_NEXT_                  14
#define _CLSID_VRP_INTERCHANGE_MOVE_            15
#define _CLSID_VRP_INTERCHANGE_NEXT_            16
#define _CLSID_VRP_INTERCHANGE_RAND_            17
#define _CLSID_VRP_CYCLIC_MOVE_                 18
#define _CLSID_VRP_CYCLIC_NEXT_                 19
#define _CLSID_VRP_CYCLIC_RAND_                 20

#define _CLSID_VRP_GENNE_                       21
#define _CLSID_VRP_CHROMOSOME_                  22
#define _CLSID_VRP_REPRESENTATION_              23
#define _CLSID_VRP_CONTINUE_                    31



#endif	/* VRPCONST_H */

