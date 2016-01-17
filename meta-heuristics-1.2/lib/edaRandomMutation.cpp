/* 
 * File:   edaRandomMutation.cpp
 * Author: root
 * 
 * Created on March 20, 2013, 6:36 PM
 */
#include "edaRandomMutation.h"
#include "edaRNG.h"


edaRandomMutation::edaRandomMutation(double rate) {
    this->rate = rate;
}

edaRandomMutation::edaRandomMutation(const edaRandomMutation& mute) {
    rate = mute.rate;
}

edaRandomMutation::~edaRandomMutation() {}

edaRandomMutation* edaRandomMutation::clone() const {
    return new edaRandomMutation(*this);
}    

void edaRandomMutation::update(edaPopulation &pop) const {    
    unsigned int size = pop.size();
    unsigned int length = pop[0]->getLength();
    for(unsigned int i = 0; i < size; i++) {
        double p = rnd.uniform();
        if(p <= rate) {       
            edaChromosome *chro = pop[i];
            unsigned int point = rnd.random(length);
            edaGenne *a = chro->getGenne(point); 
            double value = rnd.uniform();
            a->exchange(value);
            chro->setFitness(NAN);
        }
    }  
}

void edaRandomMutation::Serialize(edaBuffer &buf, bool pack) {
    if(pack) {
        buf.Pack(&rate,1);
    }
    else {
        buf.UnPack(&rate,1);

    }
}

void edaRandomMutation::setRate(double value) {
    rate = value;
}
