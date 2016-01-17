/* 
 * File:   PARSECCrossover.h
 * Author: Tieu Minh
 *
 * Created on May 13, 2013, 10:14 AM
 */

#ifndef AIRCROSSOVER_H
#define	AIRCROSSOVER_H
#include "Define.h"

class airCrossover: public edaCrossover {
public:
    airCrossover(double rate = 1.0);
    airCrossover(const airCrossover& orig);
    virtual ~airCrossover();
    void setRate(double value);
    airCrossover *clone() const;    
    void update(edaPopulation &pop);    
    void Serialize(edaBuffer &buf, bool pack);
    setClassID(_USERCLASSID_ + _CLSID_AIR_CROSSOVER_);

private:
    double rate;
};

#endif	/* AIRCROSSOVER_H */

