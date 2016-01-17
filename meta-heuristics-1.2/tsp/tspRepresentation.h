/* 
 * File:   tspRepresentation.h
 * Author: tieuminh
 *
 * Created on August 12, 2013, 10:12 AM
 */

#include "graph.h"
#include "tspDefine.h"
#include "tspSolution.h"
#ifndef TSPREPRESENTATION_H
#define	TSPREPRESENTATION_H

class tspRepresentation: public edaRepresentation {
public:
  tspRepresentation();
  tspRepresentation(const Graph &gra);
  tspRepresentation(const tspRepresentation& repre);
  virtual ~tspRepresentation();  
 
  tspRepresentation* clone() const;
  void init(const edaSolutionList &list, edaPopulation &pop) const;
  void decode(const edaPopulation &pop, edaSolutionList &list) const;
  void encode(const edaSolutionList &list, edaPopulation &pop) const; 
  void Serialize( edaBuffer &buf, bool pack );  
  setClassID(_USERCLASSID_ + _CLSID_TSP_REPRESENTATION_);    

private:
  void decode(const edaChromosome *chro, edaSolution *sol) const;
  void encode(const edaSolution *sol, edaChromosome *chro) const; 
  void easer();

  Graph *gra;
};

#endif	/* TSPREPRESENTATION_H */

