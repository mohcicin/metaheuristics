/* 
 * File:   edaPopulation.cpp
 * Author: root
 * 
 * Created on March 17, 2013, 12:38 PM
 */

#include "edaPopulation.h"
#include <algorithm>
#include <math.h>


edaPopulation::edaPopulation() {}


edaPopulation::edaPopulation(const edaPopulation& pop) 
  : vector<edaChromosome*> (pop)  {}

edaPopulation::edaPopulation(unsigned int num) {
  resize(num);
  for( unsigned int i = 0; i < num; i++ ) {
    at(i) = NULL;
  }
}

edaPopulation::~edaPopulation() {
    easer();
}

edaPopulation& edaPopulation::operator = (const edaPopulation &pop) {
    easer();
    for(unsigned int i = 0; i < size(); i++) {
        push_back(pop[i]->clone());   
    }
    return *this;
}

void edaPopulation::printOn(ostream &os) const {
    for(unsigned int i = 0; i < size(); i++) {
      edaChromosome* chro = at(i);  
      os << "(" << i << ") "<< *chro;
      if(i != size() - 1) os << endl;
    }
}

void edaPopulation::Serialize( edaBuffer &buf, bool pack ) {
    if(pack) {
        unsigned int _size = size();
        buf.Pack(&_size, 1);
        for(unsigned int i = 0; i < _size; i++) {
            at(i)->doSerialize(buf,pack);    
        }
    }    
    else {
        easer();
        unsigned int _size;
        buf.UnPack(&_size,1);
        resize(_size);
        for(unsigned int i = 0; i < _size; i++) {
            at(i) = (edaChromosome*)classGenerateFromBuffer(buf); 
        }
    }
}


edaChromosome* edaPopulation::pop_back() {
    edaChromosome* chro = this->back();
    vector<edaChromosome*>* list = (vector<edaChromosome*>*)this;
    list->pop_back();
    return chro;
}

edaPopulation *edaPopulation::clone() const {
    return new edaPopulation(*this);
}

void edaPopulation::easer() {
  for(unsigned int i = 0; i < size(); i++) {
    if(at(i) != NULL) { 
      delete at(i);     
      at(i) = NULL;
    }
  }
  clear();
  
}

ostream& operator<< (ostream &os, const edaPopulation &pop) {
    pop.printOn(os);
    return os;
}



bool comparator(edaChromosome *A, edaChromosome *B) {
    return A->getFitness() > B->getFitness();
}

void edaPopulation::sort() {
  std::sort(begin(),end(),comparator);
} 

double edaPopulation::mean() const {
  double mean = 0;
  unsigned int _size = size();
  for(unsigned int i = 0; i < _size; i++) 
    mean += at(i)->getFitness();
  mean /= _size;
  return mean;
}  

double edaPopulation::std() const {
  double std = 0;
  double _mean = mean();
  unsigned int _size = size();
  for(unsigned int i = 0; i < _size; i++) 
    std += pow( at(i)->getFitness() - _mean, 2 );
  std = sqrt( std/_size );
  return std;
}

double edaPopulation::min() const {
  double min = at(0)->getFitness();
  unsigned int _size = size();
  for(unsigned int i = 1; i < _size; i++) {
    double value = at(i)->getFitness();
    if (value < min) {
      min = value;
    }
  }
  return min;
}

double edaPopulation::max() const {
  double max = at(0)->getFitness();
  unsigned int _size = size();
  for(unsigned int i = 1; i < _size; i++) {
    double value = at(i)->getFitness();
    if (value > max) {
      max = value;
    }
  }
  return max;
}
