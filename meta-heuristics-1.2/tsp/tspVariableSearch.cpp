#include "../lib/eda.h"
#include "graph.h"
#include "tspSolution.h"
#include "tspOrOpt.h"
#include "tspOrOptNext.h"
#include "tspTwoOpt.h"
#include "tspTwoOptNext.h"
#include "tspTwoOptMoveRandom.h"
#include "tspRepresentation.h"
#include "tspGenne.h"
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
    //The number neighbor
    unsigned int K = 5;
    
    Graph graph(argv[1]);
    edaSolutionList list;
    for(unsigned int i = 0; i < 40; i++) {
      tspSolution *route = new tspSolution (graph); 
      route->init();
      list.push_back(route);
    }	     

    edaVarFitContinue nloop;  
    edaSeqWrapperControl sfControl;   
    unsigned int *hcid = new unsigned int [K];
    for(unsigned int  i = 0; i < K; i++) 
    {
        tspOrOpt or_opt (graph, i + 2);
        tspOrOptNext or_opt_next (graph);      
        edaBestImprSelect moveSelect;
        edaGenContinue cont(1500);      
        edaHC hcSearch (&or_opt, &or_opt_next, &moveSelect, &cont); 
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
      tspSolution route = *( (tspSolution*) list.getBest() );
      cout << "[Route] " << route << endl;
      cout << "[Fitness] " << route.evaluate () << endl;
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
    case _USERCLASSID_ + _CLSID_TWO_OPT_:
      return new tspTwoOpt;

    case _USERCLASSID_ + _CLSID_TWO_OPT_NEXT_:
      return new tspTwoOptNext;

    case _USERCLASSID_ + _CLSID_OR_OPT_:
      return new tspOrOpt;

    case _USERCLASSID_ + _CLSID_OR_OPT_NEXT_:
      return new tspOrOptNext;  
      
    case _USERCLASSID_ + _CLSID_TSP_SOLUTION_:
      return new tspSolution;

    case _USERCLASSID_ + _CLSID_TWO_OPT_MOVE_RANDOM_:
      return new tspTwoOptMoveRandom;

    case _USERCLASSID_ + _CLSID_GRAPH_:
      return new Graph;

    case _USERCLASSID_ + _CLSID_TSP_REPRESENTATION_:
      return new tspRepresentation;
    
    case _USERCLASSID_ + _CLSID_TSP_GENNE_:
      return new tspGenne; 
      
    default:
      std::
        cerr << "Unknown classId " << clsid << " for object generation!!!" <<
        std::endl;
      exit (-1);
    }
}
