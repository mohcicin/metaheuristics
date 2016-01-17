/* 
 * File:   airRepresentation.h
 * Author: root
 *
 * Created on March 15, 2013, 3:50 PM
 */

#ifndef AIRREPRESENTATION_H
#define	AIRREPRESENTATION_H
#include "Define.h"
#include "airSolution.h"
#include "airProblem.h"
#include "airGenne.h"

class airRepresentation: public edaRepresentation {
public:
  airRepresentation();
  airRepresentation(const airProblem &pro);
  airRepresentation(const airRepresentation& repre);
  virtual ~airRepresentation();
  
  airProblem* getProblem() const;
  airRepresentation* clone() const;

  
  void init(const edaSolutionList &list, edaPopulation &pop) const;
  void decode(const edaPopulation &pop, edaSolutionList &list) const;
  void encode(const edaSolutionList &list, edaPopulation &pop) const;  
  
  void Serialize( edaBuffer &buf, bool pack );  
  setClassID(_USERCLASSID_ + _CLSID_AIR_REPRESENTATION_);    
private:
  void decode(const edaChromosome *chro, edaSolution *sol) const;
  void encode(const edaSolution *sol, edaChromosome *chro) const; 
  void earse();
  airProblem *pro;
};

#endif	/* AIRREPRESENTATION_H */

