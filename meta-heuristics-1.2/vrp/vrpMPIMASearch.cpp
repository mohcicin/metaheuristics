/* 
 * File:   VRPMain.cpp
 * Author: Tieu Minh
 *
 * Created on November 21, 2012, 3:18 PM
 */


#include <cstdlib>
#include "../vrp/vrpLibrary.h"

using namespace std;

int main(int argc, char** argv) {
  EDAMetasearchStart (argc, argv);
  
  if (argc != 2)
  {
    std::cerr << "Usage : ./" <<  __progname
              << " [instance]" << std::endl;
  }
  else
  { 
    unsigned int n = 40;
    vrpProblem *vrpPro = new vrpProblem();
    vrpPro->load(argv[1]);
    vrpConst *vrpCon = new vrpConst();
    edaSolutionList list;
    for(unsigned int i = 0; i < n; i++) {
      vrpSolution *vrpSol = new vrpSolution (vrpPro); 
      vrpSol->init();
      list.push_back(vrpSol);
    }	

    vrpInterchangeMove* optMove = new vrpInterchangeMove();
    vrpInterchangeNext* optNext = new vrpInterchangeNext(vrpPro);
    edaFirstImprSelect moveSelect;
    edaGenContinue cont_criteria(1500); 
    edaHC hcSearch(optMove, optNext, &moveSelect, &cont_criteria);  
    
    vrpRepresentation repre(*vrpPro, *vrpCon);
    edaRouletteWheelSelection slect(0.5);    
    edaPartiallyMatchedCrossover cross;
    edaRandSwapMutation mute(0.05);   
    edaGenContinue con(1); 
    edaGA gaSearch(&con, &repre, &slect, &cross, &mute);

    // Use the declaration below to run on parallel machine:
    edaMpiWrapperControl mfControl; 
    edaNS nullSearch;
    int nullid, hcid[n], gaid;
    nullid = mfControl.insertVertex (&nullSearch);
    for(unsigned int i = 0; i < n; i++) {
      edaIDSelectWrapper wslect(i);
      hcid[i] = mfControl.insertVertex (&hcSearch, wslect);                         
    }
    gaid = mfControl.insertVertex (&gaSearch);   
    for(unsigned int i = 0; i < n; i++) {
      mfControl.insertEdge(nullid, hcid[i]);
      mfControl.insertEdge(hcid[i], gaid);
    }    
    
    edaGenContinue loop(80);
    mfControl.insertLoop(gaid, nullid, loop);
    
    if (!mfControl.search (list))
    {
      std::cerr << "Error: Cannot execute search" << std::endl;
    }
    else
    {
        vrpSolution* vrpSol = (vrpSolution*) list.getBest();
        cout << "[To Fitness] " << vrpSol->evaluate () << endl;
        cout << "[To Total Dist] " << vrpSol->getTotalDist () << endl;
        cout << "[To Total Wait] " << vrpSol->getTotalWaitTime () << endl;
        cout << "[Vehicles] " << vrpSol->size() << endl;
        cout << "[Route] " << *vrpSol << endl;
    }
  }
  EDAMetasearchStop ();
  return 0;
}

edaSerialize *
userClassGenerate (int clsid)
{
  switch (clsid)
  {
    case _USERCLASSID_ + _CLSID_VRP_PROBLEM_:
      return new vrpProblem;

    case _USERCLASSID_ + _CLSID_VRP_STOP_:
      return new vrpStop;

    case _USERCLASSID_ + _CLSID_VRP_GROUP_CONFLICT_:
      return new vrpGroupConflict;

    case _USERCLASSID_ + _CLSID_VRP_SOLUTION_:
      return new vrpSolution;

    case _USERCLASSID_ + _CLSID_VRP_ROUTE_:
      return new vrpRoute;

    case _USERCLASSID_ + _CLSID_VRP_SUBROUTE_:
      return new vrpSubRoute;
    
    case _USERCLASSID_ + _CLSID_VRP_CONST_:
      return new vrpConst; 

    case _USERCLASSID_ + _CLSID_VRP_SUBROUTE_MOVE_:
      return new vrpSubRouteMove;
      
    case _USERCLASSID_ + _CLSID_VRP_SUBROUTE_NEXT_:
      return new vrpSubRouteNext;
      
    case _USERCLASSID_ + _CLSID_VRP_ROUTE_MOVE_:
      return new vrpRouteMove;
      
    case _USERCLASSID_ + _CLSID_VRP_ROUTE_NEXT_:
      return new vrpRouteNext;
      
    case _USERCLASSID_ + _CLSID_VRP_INTERCHANGE_MOVE_:
      return new vrpInterchangeMove;
      
    case _USERCLASSID_ + _CLSID_VRP_INTERCHANGE_NEXT_:
      return new vrpInterchangeNext;
      
    case _USERCLASSID_ + _CLSID_VRP_INTERCHANGE_RAND_:
      return new vrpInterchangeRand;      
    case _USERCLASSID_ + _CLSID_VRP_REPRESENTATION_:
      return new vrpRepresentation;
      
    default:
      cerr << "Unknown classId " << clsid 
              << " for object generation!!!" << endl;
      exit (-1);
  }
}
