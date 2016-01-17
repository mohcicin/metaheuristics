/* 
 * File:   HCRAE2822.cpp
 * Author: Tieu Minh
 *
 * Created on June 11, 2013, 6:10 PM
 */

#include <cstdlib>
#include "Define.h"
#include "airProblem.h"
#include "airSolution.h"
#include "airNeighbourMove.h"
#include "airNeighbourNext.h"


using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    double rae2822i[12];
    rae2822i[0] = 0.009;
    rae2822i[1] = 0.009;
    rae2822i[2] = 0.43;
    rae2822i[3] = 0.063;
    rae2822i[4] = -0.4;
    rae2822i[5] = 0.35;
    rae2822i[6] = -0.059;
    rae2822i[7] = 0.73;
    rae2822i[8] = 0;
    rae2822i[9] = 0;
    rae2822i[10] = -7.55;
    rae2822i[11] = 9.11;
    airFoil *rea= new airFoil(rae2822i);  
    cout << rea->detail() << endl; 
//    airProblem pro("config.ini");
//    airSolution sol(pro, rea);
//    cout << "Fitness value: " << sol.evaluate() << endl; 
   
    return 0;
}

