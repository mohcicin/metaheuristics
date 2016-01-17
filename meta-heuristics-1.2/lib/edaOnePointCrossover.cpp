/* 
 * File:   edaSimpleCrossOver.cpp
 * Author: root
 * 
 * Created on March 20, 2013, 12:40 PM
 */

#include "edaOnePointCrossover.h"
#include <stdlib.h>
#include <math.h>

edaOnePointCrossover::edaOnePointCrossover(double rate) {
    this->rate = rate;
    this->mode = MEDIAN;
}

edaOnePointCrossover::edaOnePointCrossover(const edaOnePointCrossover& cross) {
    this->rate = cross.rate;
    this->mode = cross.mode;
}

edaOnePointCrossover::~edaOnePointCrossover() {}

edaOnePointCrossover *edaOnePointCrossover::clone() const {
    return new edaOnePointCrossover(*this);
}    


void edaOnePointCrossover::update(edaPopulation &pop){
    vector<edaChromosome*> trash;  
    unsigned int length = pop[0]->getLength();
    
    unsigned int cross_point;
    if(mode == RANDOM) {
        cross_point = rnd.random( (length - 1) + 1 );
    }
    else {
        cross_point = length / 2;
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
                for(unsigned int j = cross_point; j < length; j++) {
                    edaGenne *a = A->getGenne(j);
                    edaGenne *b = B->getGenne(j);
                    if(*a != *b) {
                        a->swap(b);
                        update = true;
                    }
                }
                if(update) {
                    A->setFitness( NAN );
                    B->setFitness( NAN );
                }
                trash.pop_back();
                trash.pop_back();
            }
        }
    }   
}   

void edaOnePointCrossover::Serialize(edaBuffer &buf, bool pack) {
    if(pack) {
        buf.Pack(&rate,1);
        buf.Pack(&mode,1);
    }
    else {
        buf.UnPack(&rate,1);
        buf.UnPack(&mode,1);
    }
}

void edaOnePointCrossover::setMode(CrossPointMode mode) {
    this->mode = mode;
}

void edaOnePointCrossover::setRate(double value) {
  rate = value;
}
