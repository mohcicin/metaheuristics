/* 
 * File:   edaRandSwapMutation.cpp
 * Author: tieuminh
 * 
 * Created on April 30, 2012, 2:14 PM
 */

#include "edaRandSwapMutation.h"
#include "edaPopulation.h"
#include <cstdlib>
#include <math.h>

edaRandSwapMutation::edaRandSwapMutation(double value):
    rate(value) {}

edaRandSwapMutation::edaRandSwapMutation(const edaRandSwapMutation& mute): 
    rate(mute.rate) {}

edaRandSwapMutation::~edaRandSwapMutation() {}

void edaRandSwapMutation::Serialize(edaBuffer &buf, bool pack) {
  if (pack)
  {
      buf.Pack(&rate,1);
  }
  else
  {
      buf.UnPack(&rate,1);
  }
}

edaRandSwapMutation *edaRandSwapMutation::clone() const {
    return new edaRandSwapMutation(*this);
}

void edaRandSwapMutation::update(edaPopulation &pop) const {
    unsigned int size = pop.size();
    unsigned int length = pop[0]->getLength();
    for(unsigned int i = 1; i < size; i++) {
       double p = rnd.uniform();
       unsigned int a, b;
       if(p <= rate) { 
//         printDebug(5, "  + Prob = " << p << " < Rate, select");
//         printDebug(5, "    " << *pop[i])
         edaChromosome* chro = pop[i];
         a = rnd.random (length);
         b = rnd.random (length);
         edaGenne *A = chro->getGenne(a);
         edaGenne *B = chro->getGenne(b);
         if(*A != *B) {
             A->swap(B);
             chro->setFitness(NAN);
         }
//         printDebug(5, "    Update: " << *pop[i])
       }
    }
}   

void edaRandSwapMutation::printOn(ostream& os) const {
  os << "Rate = " << rate;
}
