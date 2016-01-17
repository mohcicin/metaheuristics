/* 
 * File:   HCRAE2822.cpp
 * Author: Tieu Minh
 *
 * Created on June 11, 2013, 6:10 PM
 */

#include <cstdlib>
#include "../lib/eda.h"
#include "Define.h"
#include "airProblem.h"
#include "airSolution.h"
#include "airNeighbourMove.h"
#include "airNeighbourNext.h"
#include "airNeighbourRand.h"
#include "airRepresentation.h"
#include "airCrossover.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
  EDAMetasearchStart (argc, argv);
  if (argc != 2)
  {
    std::cerr << "Usage : ./" <<  __progname
              << " [instance]" << std::endl;
  }
  else
  {
    airProblem pro(argv[1]);
    unsigned int n = 20;	
    airFoil* *foil = new airFoil* [n]; 
    foil[0] = new airFoil("090943073096035241107310010042454910");       //rae2822
    foil[1] = new airFoil("090943073096035241107310010042454911");       //rae2822i    
    foil[2] = new airFoil("220834089093617266106710010045225508");       //naca2411
    foil[3] = new airFoil("230836089093717266106710110045235508");       //naca2411i    
    foil[4] = new airFoil("201032090093717268106810010045225500");       //naca2411o
    foil[5] = new airFoil("201032090093815267106910010045225500");       //naca2411oi    
    foil[6] = new airFoil("161630070095530239104510110050004736");       //naca0012  
    foil[7] = new airFoil("161630071095529239104510110050004736");       //naca0012i    
    foil[8] = new airFoil("141525071095429241104610110050004730");       //naca0012o1 
    foil[9] = new airFoil("141525070095429241104610110050004730");       //naca0012o1i
    foil[10] = new airFoil("151629071095531241104610110050004725");      //naca0012o2    
    foil[11] = new airFoil("151629071095531241104610210050004725");      //naca0012o2i  
    foil[12] = new airFoil("233736080097452195124208810044835067");      //foil1
    foil[13] = new airFoil("624654115091127218118107810029856119");      //foil2
    foil[14] =  foil[15] =  foil[16] =  foil[17] = foil[18] =  foil[19] = NULL;
    
    edaSolutionList list;
    for(unsigned int i = 0; i < n; i++) {
      airSolution* sol = new airSolution(pro, foil[i]);
      list.push_back(sol);
    }	
    
    airNeighbourMove move;
    airNeighbourRand next;
    edaFirstImprSelect moveSelect;
    edaGenContinue cont(3);
    edaHC hcSearch (&move, &next, &moveSelect, &cont);      
    
    airRepresentation repre(pro);        
    edaRankSelection rank(0.8);    
    airCrossover cross;
    edaRandomMutation mute(0.1);   
    edaGenContinue gens(1);       
    edaGA gaSearch(&gens, &repre, &rank, &cross, &mute);      
    
     // Use the declaration below to run on single machine:
    edaMpiWrapperControl mfControl; 

    edaNS nullSearch;
    int nullid, hcid[n], gaid;
    nullid = mfControl.insertVertex (&nullSearch);
    for(unsigned int i = 0; i < n; i++) {
      edaIDSelectWrapper slect(i);
      hcid[i] = mfControl.insertVertex (&hcSearch, slect);                         
    }
    gaid = mfControl.insertVertex (&gaSearch);   
    for(unsigned int i = 0; i < n; i++) {
      mfControl.insertEdge(nullid, hcid[i]);
      mfControl.insertEdge(hcid[i], gaid);
    }

    edaGenContinue loop(20);
    mfControl.insertLoop(gaid, nullid, loop);
    
    if (!mfControl.search (list))
    {
      std::cerr << "Error: Cannot execute search" << std::endl;
    }
    else
    {
        airSolution* sol = (airSolution*)list.getBest();
        cout << "The best solution: " << sol->name() << endl;
        cout << "Fitness value: " << sol->getCost() << endl;
    }
    
    for(unsigned int i = 0; i < n; i++) 
        delete foil[i];
    delete[] foil;
  }
  EDAMetasearchStop ();
  return 0;
}

edaSerialize *
userClassGenerate (int clsid)
{
  switch (clsid)
  {
    case _USERCLASSID_ + _CLSID_AIR_PROBLEM_:
      return new airProblem;

    case _USERCLASSID_ + _CLSID_AIR_FOIL_ :
      return new airFoil;
    
      case _USERCLASSID_ + _CLSID_AIR_CROSSOVER_ :
      return new airCrossover;
      
    case _USERCLASSID_ + _CLSID_AIR_CONTROL_:
      return new airControl;

    case _USERCLASSID_ + _CLSID_AIR_SOLUTION_:
      return new airSolution;

    case _USERCLASSID_ + _CLSID_AIR_SOLVER_:
      return new airSolver;

    case _USERCLASSID_ + _CLSID_AIR_MESH_:
      return new airMesh;
    
    case _USERCLASSID_ + _CLSID_AIR_REPRESENTATION_:
      return new airRepresentation; 

    case _USERCLASSID_ + _CLSID_AIR_GENNE_:
      return new airGenne;
      
    case _USERCLASSID_ + _CLSID_AIR_NEIGHBOURMOVE_:
      return new airNeighbourMove;
      
    case _USERCLASSID_ + _CLSID_AIR_NEIGHBOURNEXT_:
      return new airNeighbourNext;
      
    case _USERCLASSID_ + _CLSID_AIR_NEIGHBOURRAND_:
      return new airNeighbourRand;
      
    default:
      cerr << "Unknown classId " << clsid 
              << " for object generation!!!" << endl;
      exit (-1);
  }
}
