/* 
 * File:   tspRepresentation.cpp
 * Author: tieuminh
 * 
 * Created on August 12, 2013, 10:12 AM
 */

#include "tspRepresentation.h"
#include "tspGenne.h"

tspRepresentation::tspRepresentation()
    : gra(NULL) {}

tspRepresentation::tspRepresentation(const tspRepresentation& orig)
    : gra(orig.gra->clone()) {}

tspRepresentation::tspRepresentation(const Graph &graph)
    :gra(graph.clone()) {}

tspRepresentation* tspRepresentation::clone() const {
    return new tspRepresentation(*this);
}

tspRepresentation::~tspRepresentation() {
    easer();
}

void tspRepresentation::decode(const edaChromosome *chro, edaSolution *sol) const { 
    tspSolution* tspSol = (tspSolution*)sol;
    for(unsigned int i = 0; i < chro->getLength() ; i++ ) {
      tspGenne *genne = (tspGenne*)chro->getGenne(i);
      tspSol->push_back( (unsigned int) genne->getValue() );  
    }
    tspSol->setCost(chro->getFitness());
}

void tspRepresentation::encode(const edaSolution *sol, edaChromosome *chro) const {
    tspSolution *tspSol = (tspSolution*)sol;
    for(unsigned int i = 0; i < tspSol->size() ; i++) {      
      tspGenne genne = tspSol->at(i);
      chro->addGenne(genne);
    }
    chro->setFitness (tspSol->evaluate());
}

void tspRepresentation::easer() {
    if(gra != NULL)
        delete gra;
    gra = NULL;
}

void tspRepresentation::Serialize( edaBuffer &buf, bool pack ) {
  if(pack) {
    gra->doSerialize(buf,pack);
  }
  else {
    easer();
    gra = (Graph*) classGenerateFromBuffer(buf);
  }
}

void tspRepresentation::init(const edaSolutionList &list, edaPopulation &pop) const
{
  for(unsigned int i = 0; i < list.size(); i++) {
    edaChromosome *chro = new edaChromosome();
    encode(list[i], chro);  
    pop[i] = chro; 
  }
  for(unsigned int i = list.size(); i < pop.size(); i++) {
    edaChromosome *chro = new edaChromosome();
    tspSolution *tspSol = new tspSolution(*gra);
    tspSol->init();
    encode(tspSol, chro);     
    pop[i] = chro; 
  }
}

void tspRepresentation::decode(const edaPopulation &pop, edaSolutionList &list ) const {
  list.easer();
  for(unsigned int i = 0; i < pop.size(); i++) {
    edaChromosome *chro = pop[i];
    tspSolution *tspSol = new tspSolution(*gra);
    decode(chro, tspSol);
    list.push_back(tspSol);
  }
}

void tspRepresentation::encode(const edaSolutionList &list, edaPopulation &pop) const { 
  pop.easer();
  for(unsigned int i = 0; i < list.size(); i++) {
    edaSolution *sol = list[i];
    edaChromosome *chro = new edaChromosome();
    encode(sol, chro);
    pop.push_back(chro);
  }
}
