#include <iostream>
#include "../lib/eda.h"
#include "graph.h"
#include "tspSolution.h"
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

    Graph graph(argv[1]);
  
    edaSolutionList list;
    for(unsigned int i = 0; i < 40; i++) {
      tspSolution *route = new tspSolution (graph); 
      route->init();
      list.push_back(route);
    }	     

    tspTwoOpt two_opt (graph);
    tspTwoOptNext two_opt_next (graph);      
    edaFirstImprSelect moveSelect;
    edaGenContinue cont(1500);      
    edaHC hcSearch (&two_opt, &two_opt_next, &moveSelect, &cont);   

    tspTwoOptMoveRandom two_ran_opt (graph);
    edaExpCoolingSchedule coolingSchedule (0.01, 0.98);
    edaSA saSearch (&two_opt, &two_ran_opt, &cont,
            50.0, &coolingSchedule);        

    edaSimpleMoveTabuList tabuList;
    edaImprBestFitAspirCrit aspirCrit;
    edaTS tsSearch (&two_opt, &two_opt_next, &tabuList, &aspirCrit, &cont);   

    
    // Use the declaration below to run on single machine:
    edaSeqWrapperControl sfControl; 
    edaBestSelectWrapper bslect;
    edaGenContinue nloop(2); 
 
    int tsid0 = sfControl.insertVertex (&tsSearch);
    int said1 = sfControl.insertVertex (&saSearch);   
    int said2 = sfControl.insertVertex (&saSearch);  
    int said3 = sfControl.insertVertex (&saSearch);  
    int hcid4 = sfControl.insertVertex (&hcSearch,bslect);
    
    sfControl.insertEdge(tsid0, said1);
    sfControl.insertEdge(tsid0, said2);
    sfControl.insertEdge(tsid0, said3);
    sfControl.insertEdge(said1, hcid4);
    sfControl.insertEdge(said2, hcid4);
    sfControl.insertEdge(said3, hcid4);
    sfControl.insertLoop(hcid4, tsid0, nloop);
    
    if (!sfControl.search (list))
    {
      std::cerr << "Error: Cannot execute search" << std::endl;
    }
    else
    {
      tspSolution route = *( (tspSolution*) list[0]);
      std::cout << "[Route] " << route << std::endl;
      std::cout << "[Fitness] " << route.evaluate () << std::endl;
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
    case _USERCLASSID_ + _CLSID_TWO_OPT_:
      return new tspTwoOpt;

    case _USERCLASSID_ + _CLSID_TWO_OPT_NEXT_:
      return new tspTwoOptNext;

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
