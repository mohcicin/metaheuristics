/* 
 * File:   AIRNEIGHBOURMOVE.cpp
 * Author: Tieu Minh
 * 
 * Created on April 29, 2013, 10:55 AM
 */

#include "airNeighbourMove.h"
#include "airSolution.h"

airNeighbourMove::airNeighbourMove()
{
    this->first = 0;
    this->second = 0;    
}

airNeighbourMove::airNeighbourMove(const airNeighbourMove& orig) 
{
    first = orig.first;
    second = orig.second;
}

airNeighbourMove::~airNeighbourMove() {

}

airNeighbourMove* airNeighbourMove::clone() const {
    return new airNeighbourMove(*this);
}

void airNeighbourMove::init(const edaSolution &sol) {
    this->first = 0;
    this->second = 0;
    
}
double airNeighbourMove::incrEval(const edaSolution &sol) const
{
    airSolution &airSol =  (airSolution&) sol;
    airSolution newSol = airSol;
    airFoil* foil = newSol.getFoil();
    if (foil->incrEval(first, second) )
        return newSol.evaluate() - airSol.evaluate();
    return -1.0; 
}

void airNeighbourMove::update( edaSolution &sol ) const
{
    airSolution &airSol =  (airSolution&) sol;
    airFoil* foil = airSol.getFoil();
    foil->incrEval(first, second);    
}

airNeighbourMove& airNeighbourMove::operator = (const edaMove& move) {
    airNeighbourMove &airMove = (airNeighbourMove &)move;
    first = airMove.first;
    second = airMove.second;
    return *this;
}

void airNeighbourMove::Serialize( edaBuffer &buf, bool pack ) {
    if(pack) {
        buf.Pack(&first);
        buf.Pack(&second);
    }
    else {
        buf.UnPack(&first);
        buf.UnPack(&second);
    }
}

bool airNeighbourMove::operator == (const edaMove &move) const {
    airNeighbourMove &airMove = (airNeighbourMove &)move;
    if(first == airMove.first && second == airMove.second)
        return true;
    return false;
}
    
void airNeighbourMove::printOn( ostream &os ) const {
    os << "Operation [" << first << ", " << second << "]" << endl; 
}
