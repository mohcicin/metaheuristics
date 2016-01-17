/* 
 * File:   airSolution.cpp
 * Author: Tieu Minh
 * 
 * Created on April 25, 2013, 4:39 PM
 */

#include "airSolution.h"

airSolution::airSolution() 
    : pro(NULL), foil(NULL), cost(NAN) {
}

airSolution::airSolution(const airProblem &_pro, airFoil* _foil) {
    pro = _pro.clone();
    cost = NAN;
    if(_foil == NULL) {
        foil = _pro.createFoil();
//        while (evaluate() == -9999) {
//	    delete foil;
//	    foil = _pro.createFoil();
//        }
    }
    else {      

        foil = _foil->clone();     
    }
}

airSolution::airSolution(const airSolution& orig) 
    : pro(orig.pro->clone()), foil(orig.foil->clone()), cost(orig.cost) {
}

airSolution::~airSolution() {
    easer();
}

airSolution* airSolution::clone() const {
    return new airSolution(*this);
}

void airSolution::easer() {
    if(pro != NULL) {
        delete pro;
        pro = NULL;       
    }
    if(foil != NULL) {
        delete foil;
        foil = NULL;       
    }
}

double airSolution::evaluate() {
    cost = pro->run(*foil);
    return cost;
}

void airSolution::setCost(double value) {
    cost = value;
}

airSolution& airSolution::operator = (const edaSolution &sol) 
{
    easer();
    const airSolution& airSol = (const airSolution&) sol;
    pro = airSol.pro->clone();
    foil = airSol.foil->clone();
    cost = airSol.cost;
    return *this;
}

bool airSolution::operator == (const edaSolution &sol) const {
    airSolution &airSol = (airSolution&) sol;
    return *foil == *airSol.foil;
}

void airSolution::printOn(ostream &os) const {
    os << *foil;
}
string airSolution::name() const {
    return foil->name();
}

string airSolution::detail() const {
  return foil->detail();      
}

void airSolution::Serialize(edaBuffer &buf, bool pack) {
    if(pack) {
        pro->doSerialize(buf, pack);
        foil->doSerialize(buf, pack);
        buf.Pack(&cost);
    }
    else {
        easer();
        pro = (airProblem *) classGenerateFromBuffer(buf);
        foil = (airFoil *) classGenerateFromBuffer(buf);
        buf.UnPack(&cost);
    }
}
    
double airSolution::getCost() const {
    return cost;
}

airFoil* airSolution::getFoil() const {
    return foil;
}
