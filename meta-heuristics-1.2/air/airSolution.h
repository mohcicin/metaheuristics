/* 
 * File:   airSolution.h
 * Author: Tieu Minh
 *
 * Created on April 25, 2013, 4:39 PM
 */

#ifndef AIRSOLUTION_H
#define	AIRSOLUTION_H
#include "Define.h"
#include "airProblem.h"

class airSolution: public edaSolution {
public:
    airSolution();
    airSolution(const airProblem &pro, airFoil* foil = NULL);
    airSolution(const airSolution& orig);
    airSolution* clone() const;
    double evaluate();
    double getCost() const;
    void setCost(double value);
    airFoil* getFoil() const;    
    string name() const;
    string detail() const;
    airSolution& operator = (const edaSolution &sol);
    bool operator == (const edaSolution &sol) const;
    void printOn(ostream &os) const;
    void Serialize(edaBuffer &buf, bool pack);
    setClassID(_USERCLASSID_ + _CLSID_AIR_SOLUTION_);    
    ~airSolution();
    
private:
    airProblem *pro;
    airFoil *foil;
    double cost;
    void easer();
    
};

#endif	/* AIRSOLUTION_H */

