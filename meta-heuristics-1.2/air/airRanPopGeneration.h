/* 
 * File:   airRanPopGeneration.h
 * Author: root
 *
 * Created on March 18, 2013, 9:41 AM
 */

#ifndef AIRRANPOPGENERATION_H
#define	AIRRANPOPGENERATION_H
#include "../lib/eda.h"
#include "Define.h"
#include "airProblem.h"
#include "airRepresentation.h"

class airRanPopGeneration:public edaPopGeneration {
public:
  airRanPopGeneration();
  airRanPopGeneration(const airRepresentation& repre); 
  airRanPopGeneration(const airRanPopGeneration& gen);
  virtual ~airRanPopGeneration();
  airRanPopGeneration *clone() const;
  void generate(edaPopulation *pop) const; 
  void setNumberPopulation(unsigned int value);
  setClassID(_USERCLASSID_ + _CLSID_AIRRANPOPGENERATION_);
  void printOn(ostream &os);
  void Serialize( edaBuffer &buf, bool pack );    

private:
  void earse();
  unsigned int num;
  airRepresentation* repre;
  
};

#endif	/* AIRRANPOPGENERATION_H */

