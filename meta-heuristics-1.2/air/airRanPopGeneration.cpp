/* 
 * File:   airRanPopGeneration.cpp
 * Author: root
 * 
 * Created on March 18, 2013, 9:41 AM
 */

#include "airRanPopGeneration.h"
#include "airSolution.h"

airRanPopGeneration::airRanPopGeneration()
  : num(0), repre(NULL) {}

airRanPopGeneration::airRanPopGeneration(const airRepresentation& _repre) {
  repre = _repre.clone();   
  num = 50;
}

airRanPopGeneration::airRanPopGeneration(const airRanPopGeneration& gen) 
  : num(gen.num), repre(gen.repre->clone()) {}

airRanPopGeneration* airRanPopGeneration::clone() const {
    return new airRanPopGeneration(*this);
}

void airRanPopGeneration::setNumberPopulation(unsigned int value) {
  num = value;
}

airRanPopGeneration::~airRanPopGeneration() {
  earse();
}

void airRanPopGeneration::generate(edaPopulation *pop) const {
    for(unsigned int i = 0; i < num; i++) {
//        airSolution *sol = new airSolution(*repre->getProblem());
        airSolution *sol = NULL;
        do {
            sol = new airSolution(*repre->getProblem());
            double cost = sol->evaluate();
            if(cost == MIN_VALUE) {
                delete sol;
                sol = NULL;
            }
        } while (sol == NULL);
        edaChromosome *chro = repre->encode(*sol);  
        pop->addBack(chro); 
    }
    pop->update();
}

void airRanPopGeneration::earse() {
  if(repre != NULL) {
    delete repre;
    repre = NULL;
  }
}

void airRanPopGeneration::Serialize( edaBuffer &buf, bool pack ) {
  if(pack) {
    repre->doSerialize(buf,pack);  
    buf.Pack(&num, 1);
  }
  else {
    earse();
    repre = (airRepresentation*)classGenerateFromBuffer(buf);  
    buf.UnPack(&num, 1);
  }
}
