/* 
 * File:   edaSimpleCrossOver.cpp
 * Author: root
 * 
 * Created on March 20, 2013, 12:40 PM
 */

#include "edaLambdaPointCrossover.h"
#include <stdlib.h>
#include <math.h>
#include <algorithm>

edaLambdaPointCrossover::edaLambdaPointCrossover(double rate, unsigned int num) {
    this->rate = rate;
    this->num = num;
}

edaLambdaPointCrossover::edaLambdaPointCrossover(const edaLambdaPointCrossover& cross) {
    this->rate = cross.rate;
    this->num = cross.num;
}

edaLambdaPointCrossover::~edaLambdaPointCrossover() {}

edaLambdaPointCrossover *edaLambdaPointCrossover::clone() const {
    return new edaLambdaPointCrossover(*this);
}    


void edaLambdaPointCrossover::update(edaPopulation &pop){
    vector<edaChromosome*> trash;  
    unsigned int length = pop[0]->getLength();
    num = num <=0 ? 0 : num;
    num = num > length/2 ? length/2 : num;
    
    unsigned int* cross_point = new unsigned int[num + 1];
    
    unsigned int size = pop.size();
    for(unsigned int i = 0; i < size; i++) {
        double p = rnd.uniform();
        if(p <= rate) {            
            trash.push_back(pop[i]);           
            if(trash.size() == 2) {               
                edaChromosome* A = trash[0];
                edaChromosome* B = trash[1];
                bool update = false;
                for(unsigned int j = 0; j < num; j++) {
                  cross_point[j] = rnd.random( (length - 1) + 1 );                
                }
                cross_point[num] = length;
                sort(cross_point, cross_point + num + 1);
                for(unsigned int j = 0; j < num; j+= 2) {
                    for(unsigned int k = cross_point[j]; k < cross_point[j+1]; k++) {
                      edaGenne *a = A->getGenne(k);
                      edaGenne *b = B->getGenne(k);
                      if(*a != *b) {
                          a->swap(b);
                          update = true;
                      }
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

void edaLambdaPointCrossover::Serialize(edaBuffer &buf, bool pack) {
    if(pack) {
        buf.Pack(&rate,1);
        buf.Pack(&num,1);
    }
    else {
        buf.UnPack(&rate,1);
        buf.UnPack(&num,1);
    }
}

void edaLambdaPointCrossover::setNumPoint(unsigned int num) {
    this->num = num;
}

void edaLambdaPointCrossover::setRate(double value) {
    rate = value;
}
