/* 
 * File:   airRepresentation.cpp
 * Author: root
 * 
 * Created on March 15, 2013, 3:50 PM
 */

#include "airRepresentation.h"



airRepresentation::airRepresentation() {
    pro = NULL;
}

airRepresentation* airRepresentation::clone() const{
  return new airRepresentation(*this);
}

airRepresentation::airRepresentation(const airProblem &_pro) {
  pro = _pro.clone();
}

airRepresentation::airRepresentation(const airRepresentation& repre) {
  pro = repre.pro->clone();
}

airRepresentation::~airRepresentation() {
  earse();
}

void airRepresentation::decode(const edaChromosome *chro, edaSolution *sol) const {
  airSolution* airSol = (airSolution*)sol;
  airFoil* foil = airSol->getFoil();
  for(unsigned int i = 0; i < foil->size(); i++ ) {
    airGenne *genne = (airGenne*)chro->getGenne(i);
    foil->denorm  (i, genne->getValue());
  }
  airSol->setCost(chro->getFitness());

}

void airRepresentation::encode(const edaSolution *sol, edaChromosome *chro) const {
  airSolution* airSol = (airSolution*) sol;
  airFoil* foil = airSol->getFoil();
  for(unsigned int i = 0; i < foil->size(); i++) {      
    airGenne genne = foil->norm(i);
    chro->addGenne(genne);
  }
  chro->setFitness(airSol->evaluate());
}

void airRepresentation::Serialize( edaBuffer &buf, bool pack ) { 
  if(pack) {
    pro->doSerialize(buf,pack);
  }
  else {
    earse();
    pro = (airProblem*) classGenerateFromBuffer(buf);
  }   
} 

void airRepresentation::earse() {
  if(pro != NULL) {
    delete pro;
    pro = NULL;
  }
}

airProblem* airRepresentation::getProblem() const{
  return pro;
}

void airRepresentation::init(const edaSolutionList &list, edaPopulation &pop) const {
  for(unsigned int i = 0; i < list.size(); i++) {
    edaChromosome *chro = new edaChromosome();
    encode(list[i], chro);  
    pop[i] = chro; 
  }
  for(unsigned int i = list.size(); i < pop.size(); i++) {
    edaChromosome *chro = new edaChromosome();
    airSolution *airSol = new airSolution(*pro);
    airSol->init();
    encode(airSol, chro);     
    pop[i] = chro; 
  }   
}
void airRepresentation::decode(const edaPopulation &pop, edaSolutionList &list) const {
  list.easer();
  for(unsigned int i = 0; i < pop.size(); i++) {
    edaChromosome *chro = pop[i];
    airSolution *airSol = new airSolution(*pro);
    decode(chro, airSol);
    list.push_back(airSol);
  }
}

void airRepresentation::encode(const edaSolutionList &list, edaPopulation &pop) const {
  pop.easer();
  for(unsigned int i = 0; i < list.size(); i++) {
    edaSolution *sol = list[i];
    edaChromosome *chro = new edaChromosome();
    encode(sol, chro);
    pop.push_back(chro);
  }
}
