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
    edaSimpleMoveTabuList tabuList;
    edaImprBestFitAspirCrit aspirCrit;
    edaGenContinue cont_criteria (1500);
    edaTS tsSearch (&two_opt, &two_opt_next, &tabuList, &aspirCrit, &cont_criteria);     


    // Use the declaration below to run on single machine:
    edaSeqWrapperControl sfControl;     
    sfControl.insertVertex (&tsSearch);         
    

    if (!sfControl.search (list))
    {
      std::cerr << "Error: Cannot execute search" << std::endl;
    }
    else
    {
      tspSolution route = *( (tspSolution*) list.getBest() );
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
