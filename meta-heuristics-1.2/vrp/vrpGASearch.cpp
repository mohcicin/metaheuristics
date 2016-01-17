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
    std::cerr << "Usage : ./vrpMPISearch [instance]" << std::endl;
  }
  else
  { 

    vrpProblem *vrpPro = new vrpProblem();
    vrpPro->load(argv[1]);
    vrpConst *vrpCon = new vrpConst();
    edaSolutionList list;
    for(unsigned int i = 0; i < 40; i++) {
      vrpSolution *vrpSol = new vrpSolution (vrpPro); 
      vrpSol->init();
      list.push_back(vrpSol);
    }	


    vrpRepresentation repre(*vrpPro, *vrpCon);
    edaRouletteWheelSelection slect(0.5);  
    edaPartiallyMatchedCrossover cross;
    edaRandSwapMutation mute(0.05);   
    edaGenContinue con(1500); 
    edaGA gaSearch(&con, &repre, &slect, &cross, &mute);

    edaSeqWrapperControl sfControl; 
    sfControl.insertVertex (&gaSearch);  

    if (!sfControl.search (list))
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
