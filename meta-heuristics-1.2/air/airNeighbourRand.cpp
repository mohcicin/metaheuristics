/* 
 * File:   airNeighbourRanNext.cpp
 * Author: Tieu Minh
 * 
 * Created on April 30, 2013, 9:13 AM
 */

#include "airNeighbourRand.h"
#include "airSolution.h"
#include "airNeighbourMove.h"

airNeighbourRand::airNeighbourRand(unsigned int _num) {
    count = 0;
    num = _num;
}

airNeighbourRand::airNeighbourRand(const airNeighbourRand& orig) {
    count = orig.count;
    num = orig.num;
}

airNeighbourRand::~airNeighbourRand() {
}

bool airNeighbourRand::generate( edaMove *move, const edaSolution &sol ) {
    airNeighbourMove *airMove = (airNeighbourMove *) move;
//    airSolution& airSol = (airSolution&) sol;

    if ( count == num )
    {
      count = 0;
      return false;
    }   
    else
    {
        do 
        {            
            airMove->first = rnd.random(12);
            
        } while(airMove->first == 9);
        
        airMove->second = rnd.random(2);
    }
    count++;
    return true;
}

airNeighbourRand *airNeighbourRand::clone() const 
{
    return new airNeighbourRand(*this);
}

void airNeighbourRand::Serialize( edaBuffer &buf, bool pack ) {
    if(pack) {
        buf.Pack(&count);
        buf.Pack(&num);
    }
    else {
        buf.UnPack(&count);
        buf.UnPack(&num);
    }
}
void airNeighbourRand::setNumNeighbour(const unsigned int _num) {
    num = _num;
}
