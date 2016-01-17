/* 
 * File:   PARSECCrossover.cpp
 * Author: Tieu Minh
 * 
 * Created on May 13, 2013, 10:14 AM
 */

#include "airCrossover.h"
#include "airGenne.h"

airCrossover::airCrossover(double _rate) {
    rate = _rate;
}

airCrossover::airCrossover(const airCrossover& orig) {
    rate = orig.rate;            
}

airCrossover::~airCrossover() {
    
}

airCrossover *airCrossover::clone() const {
    return new airCrossover(*this);
}

void airCrossover::update(edaPopulation &pop) {
    vector<edaChromosome*> trash;      
    unsigned int mode =  rnd.random(4);
    unsigned int begin = 0, end = 0;
    switch (mode)
    {
      case 0: 
          begin = 0;
          end = 2;
          break;
      case 1: 
          begin = 2;
          end = 5;
          break;
      case 2:
          begin = 5;
          end = 8;
          break;
      case 3:
          begin = 8;
          end = 10;
          break;
      case 4: 
          begin = 10;
          end = 12;
          break;
    }
    
    unsigned int size = pop.size();
    for(unsigned int i = 0; i < size; i++) {
        double p = rnd.uniform();
        if(p <= rate) {            
            trash.push_back(pop[i]);           
            if(trash.size() == 2) {               
                edaChromosome* A = trash[0];
                edaChromosome* B = trash[1];
                bool update = false;
                for(unsigned int j = begin; j < end; j++) {
                    airGenne *a = (airGenne*)A->getGenne(j);
                    airGenne *b = (airGenne*)B->getGenne(j);
                    if(*a != *b) {
                        a->swap(b);
                        update = true;
                    }
                }
                if(update) {
                    A->setFitness(NAN);
                    B->setFitness(NAN);
                }
                trash.pop_back();
                trash.pop_back();
            }
        }
    }   
}  

void airCrossover::Serialize(edaBuffer &buf, bool pack) {
   if(pack) {
        buf.Pack(&rate,1);
    }
    else {
        buf.UnPack(&rate,1);
    }
}

void airCrossover::setRate(double value) {
    rate = value;
}
