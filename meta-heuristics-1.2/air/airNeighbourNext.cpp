/* 
 * File:   airNeighbourNext.cpp
 * Author: Tieu Minh
 * 
 * Created on April 30, 2013, 9:13 AM
 */

#include "airNeighbourNext.h"
#include "airSolution.h"
#include "airNeighbourMove.h"

airNeighbourNext::airNeighbourNext() {
}

airNeighbourNext::airNeighbourNext(const airNeighbourNext& orig) {
}

airNeighbourNext::~airNeighbourNext() {
}

bool airNeighbourNext::generate( edaMove *move, const edaSolution &sol ) {
    airNeighbourMove *airMove = (airNeighbourMove *) move;
    airSolution& airSol = (airSolution&) sol;

    if ( ( airMove->first == ( airSol.getFoil() )->size() - 1) && 
        ( airMove->second ==  1 ) )
    {
      return false;
    }   
    else
    {
      airMove->second++;
      if ( airMove->second == 2 )
      {
        airMove->first++;
        
        if(airMove->first == 9)
            airMove->first++;
        
        airMove->second = 0;
      }
    }
    return true;
}

airNeighbourNext *airNeighbourNext::clone() const 
{
    return new airNeighbourNext(*this);
}

void airNeighbourNext::Serialize( edaBuffer &buf, bool pack ) {
    
}
