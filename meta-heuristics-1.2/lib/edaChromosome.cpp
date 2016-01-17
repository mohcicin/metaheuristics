#include "edaChromosome.h"
#include <math.h>

edaChromosome::edaChromosome() {
  fitness = NAN;
}

edaChromosome::edaChromosome(const edaChromosome& chro) {
  for(unsigned int i = 0; i < chro.list.size(); i++) 
    list.push_back(chro.list[i]->clone());
  fitness = chro.fitness;
}

edaChromosome::~edaChromosome() {
  easer();
}

edaChromosome* edaChromosome::clone() const {
  return new edaChromosome(*this); 
}

void edaChromosome::addGenne(const edaGenne & genne) {
  fitness = NAN;
  list.push_back(genne.clone());    
}

edaGenne *edaChromosome::getGenne(unsigned int index) const{
  return list[index];
}

unsigned int edaChromosome::getLength() const {
  return list.size();
}
edaChromosome& edaChromosome::operator = (const edaChromosome &chro) {
  easer();
  for(unsigned int i = 0; i < chro.list.size(); i++) 
    list.push_back(chro.list[i]->clone());    
  fitness = chro.fitness;
  return *this;
}
bool edaChromosome::operator == (const edaChromosome &chro) const {
  for(unsigned int i = 0; i < list.size(); i++) 
      if( !(*list[i] == *chro.list[i]) )
          return false;    
  return true;
}

 void edaChromosome::Serialize( edaBuffer &buf, bool pack ) {
  if (pack) {                
    unsigned int size = list.size();
    buf.Pack(&size, 1);
    for(unsigned int i = 0; i < size; i++) {
      edaGenne *genne = list[i];
      genne->doSerialize(buf,pack);
    }
    buf.Pack(&fitness,1);                
  }       
  else {
    easer();
    unsigned int size;
    buf.UnPack(&size, 1);
    list.resize(size);
    for (unsigned int i = 0; i < size; i++) 
      list[i] = (edaGenne*)classGenerateFromBuffer(buf);
    buf.UnPack(&fitness,1);
  }
 }
 
 void edaChromosome::printOn(ostream &os) const {      
  for(unsigned int i = 0; i < list.size(); i++)
    os << *list[i] << " ";
 }
 
ostream& operator<< (ostream &os, const edaChromosome &chro) {
  chro.printOn(os);
  return os;
}

void edaChromosome::easer() {
  for(unsigned int i = 0; i < list.size(); i++) 
    delete list[i];    
  list.clear();    
}

bool edaChromosome::operator != (const edaChromosome &chro) const {
  return ! operator == (chro);
}

double edaChromosome::getFitness() const {
  return fitness;
}

void edaChromosome::setFitness(double _finess) {
  fitness = _finess;
}
