#include <cstdlib>
#include "../vrp/vrpLibrary.h"

int main (int argc, char **argv)
{
  EDAMetasearchStart (argc, argv);
  if (argc != 2)
  {
    std::cerr << "Usage : ./" <<  __progname
              << " [instance]" << std::endl;
  }
  else
  {
    //The number neighbourhood
    unsigned int K = 5;
    
    vrpProblem *vrpPro = new vrpProblem(argv[1]);
    edaSolutionList list;
    for(unsigned int i = 0; i < 40; i++) {
      vrpSolution *vrpSol = new vrpSolution (vrpPro); 
      vrpSol->init();
      list.push_back(vrpSol);
    }	   

    edaVarFitContinue nloop;  
    edaSeqWrapperControl sfControl;   
    unsigned int *hcid = new unsigned int [K];
    for(unsigned int  i = 0; i < K; i++) 
    {
        vrpInterchangeMove optMove;
        vrpInterchangeNext optNext(vrpPro, i + 2);
        edaFirstImprSelect moveSelect;
        edaGenContinue cont; 
        edaHC hcSearch(&optMove, &optNext, &moveSelect, &cont);     
        
        hcid[i] = sfControl.insertVertex (&hcSearch); 
        if(i > 0) sfControl.insertEdge(hcid[i - 1], hcid[i]);   
    }
    sfControl.insertLoop(hcid[K-1], hcid[0], nloop);
    
    // Use the declaration below to run on single machine:
    if (!sfControl.search (list))
    {
      cerr << "Error: Cannot execute search" << endl;
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
    delete[] hcid;
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
