/* 
 * File:   edaCostWeightSelection.cpp
 * Author: root
 * 
 * Created on March 18, 2013, 4:21 PM
 */

#include <stdlib.h>
#include "edaRouletteWheelSelection.h"

edaRouletteWheelSelection::edaRouletteWheelSelection(const double rate, const double alpha) {
    this->rate = rate;
    this->alpha = alpha;
    weight = NULL;
}

edaRouletteWheelSelection::edaRouletteWheelSelection(const edaRouletteWheelSelection& slect) {
    rate = slect.rate;
    alpha = slect.alpha;
    weight = NULL;
}

edaRouletteWheelSelection::~edaRouletteWheelSelection() {
    easer();
}

edaRouletteWheelSelection* edaRouletteWheelSelection::clone() const {
    return new edaRouletteWheelSelection(*this);
} 
    
void edaRouletteWheelSelection::update(edaPopulation &pop) {

  unsigned int size = pop.size(); 
  unsigned int num = (unsigned int)(rate * size);
  pop.sort();
  computeCostWeight(pop);

  edaChromosome **set = new edaChromosome*[num];
  for(unsigned int i = 0; i < num; i++) { 
      set[num - i - 1] = pop.pop_back();
  }
  
  for(unsigned int i = 0; i < num; i++) {
      double p = rnd.uniform ();   
      unsigned int index = 0;
      while(weight[index] < p) index++;
      edaChromosome* chro = index < size - num ? pop[index] : set[index - size + num] ;
//      printDebug(5, "  + Prob = " << p << ", Weight[" 
//        << index << "] = " << weight[index] << ", select")  
//      printDebug(5, "    " << *chro)
      pop.push_back (chro->clone()); 
  }
  for(unsigned int i = 0; i < num; i++) 
      delete set[i];  
  delete[] set;
}
    
void edaRouletteWheelSelection::setAlpha(double value) {
    alpha = value;
}

void edaRouletteWheelSelection::Serialize( edaBuffer &buf, bool pack ) {
  if(pack) {
    buf.Pack(&rate,1);
    buf.Pack(&alpha,1);
  }
  else {
    easer();
    buf.UnPack(&rate,1);
    buf.UnPack(&alpha,1);
  }
}

void edaRouletteWheelSelection::computeCostWeight(const edaPopulation& pop) {   
  easer();
  unsigned int size = pop.size();
  weight = new double[size];
  double min = alpha *pop[size-1]->getFitness();  
  double sum = 0;  
  for(unsigned int i = 0; i < size; ++i) {
      weight[i] = pop[i]->getFitness() - min;        
      sum += weight[i];        
  }    
  weight[0] = weight[0]/sum;
  for(unsigned int i = 1; i < size; ++i) { 
      weight[i] = weight[i-1] + weight[i]/sum;    
  }
}

void edaRouletteWheelSelection::easer() {
  if(weight != NULL) {
    delete[] weight;
    weight = NULL;
  }
}

void edaRouletteWheelSelection::printOn(ostream& os) const {
  os << "rate " << rate << ", alpha " << alpha; 
}
