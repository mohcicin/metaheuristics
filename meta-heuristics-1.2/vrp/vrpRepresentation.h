/* 
 * File:   vrpRepresentation.h
 * Author: Tieu Minh
 *
 * Created on October 8, 2013, 4:03 PM
 */

#ifndef VRPREPRESENTATION_H
#define	VRPREPRESENTATION_H
#include "vrpDefine.h"
#include "vrpProblem.h"
#include "vrpConst.h"
#include "vrpSubRoute.h"
class vrpRepresentation: public edaRepresentation {
public:
  vrpRepresentation();
  vrpRepresentation(const vrpProblem &pro, const vrpConst &con);
  vrpRepresentation(const vrpRepresentation& orig);
  vrpRepresentation* clone() const;
  
  void init(const edaSolutionList &list, edaPopulation &pop) const;
  void decode(const edaPopulation &pop, edaSolutionList &list) const;
  void encode(const edaSolutionList &list, edaPopulation &pop) const; 
  
  virtual ~vrpRepresentation();
  void Serialize( edaBuffer &buf, bool pack );  
  setClassID(_USERCLASSID_ + _CLSID_VRP_REPRESENTATION_);   
private:
  vrpSubRoute* createSubRouteFormList(vrpStop* ref, double rest_dist, double coming_time, 
  vector<unsigned int>& list, vrpProblem* _problem, vrpConst* _const) const; 
  void decode(const edaChromosome *chro, edaSolution *sol) const;
  void encode(const edaSolution *sol, edaChromosome *chro) const; 
  void easer();
  vrpProblem* pro;
  vrpConst* con;
};

#endif	/* VRPREPRESENTATION_H */

