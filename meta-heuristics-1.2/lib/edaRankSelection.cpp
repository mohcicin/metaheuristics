/* 
 * File:   edaRankWeightSelection.cpp
 * Author: root
 * 
 * Created on March 18, 2013, 4:10 PM
 */

#include <stdlib.h>
#include "edaRankSelection.h"

edaRankSelection::edaRankSelection(const double _rate) {
    rate = _rate;  
    rank = NULL;
}

edaRankSelection::edaRankSelection(const edaRankSelection& slect) {
    rate = slect.rate;
    rank = NULL;
//    for(unsigned int i = 0; i < slect.rank.size(); i++) {
//      rank.push_back(slect.rank[i]);
//    }
}

edaRankSelection::~edaRankSelection() {
    easer();
}

edaRankSelection* edaRankSelection::clone() const {
    return new edaRankSelection(*this);
}
void edaRankSelection::update(edaPopulation &pop) {
    
    unsigned int size = pop.size();
    unsigned int num = (unsigned int)(rate*size);
    
    pop.sort();    
    computeRankWeight( pop );
    
    edaChromosome **set = new edaChromosome*[num];
    for(unsigned int i = 0; i < num; i++) { 
        set[num - i - 1] = pop.pop_back();
    }

    for(unsigned int i = 0; i < num; i++) {
        double p = rnd.uniform();   
        unsigned int index = 0;
        while(rank[index] < p) index++;
        edaChromosome* chro = index < size - num ? pop[index] : set[index - size + num] ;
//        printDebug(5, "  + Prob = " << p << ", Rank[" 
//          << index << "] = " << rank[index] << ", select")  
//        printDebug(5, "    " << *chro)
        pop.push_back (chro->clone()); 
    }
    for(unsigned int i = 0; i < num; i++) 
        delete set[i];  
    delete[] set;
}

void edaRankSelection::Serialize( edaBuffer &buf, bool pack ) {
    if(pack) {
        buf.Pack(&rate,1);
    } else {
        easer();
        buf.UnPack(&rate,1);
    }
}

void edaRankSelection::computeRankWeight(const edaPopulation& pop) {
  easer();
  unsigned int size = pop.size();
  rank = new double[size];
  double sum = 0;  
  for(unsigned int i = 1; i <= size; ++i) {     
      sum += i;        
  }    
  rank[0] = 1.0 * size / sum;
  for(unsigned int i = 1; i < size; ++i) { 
      rank[i] = rank[i-1] + (1.0*size - i)/sum;    
  }
}

void edaRankSelection::setRate(double value) {
    rate = value;
}

void edaRankSelection::easer() {
  if(rank != NULL) {
    delete[] rank;
    rank = NULL;
  }
}

void edaRankSelection::printOn(ostream& os) const {
  os << "rate " << rate;
}
