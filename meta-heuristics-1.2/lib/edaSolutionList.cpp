/* 
 * File:   edaSoultionList.cpp
 * Author: Tieu Minh
 * 
 * Created on August 18, 2013, 9:34 AM
 */

#include "edaSolutionList.h"
#include "edaRNG.h"
#include <limits.h>
#include <sstream>
#include <algorithm>
#include <list>

edaSolutionList::edaSolutionList() {
}

edaSolutionList::edaSolutionList(const edaSolutionList& orig) {
  for(unsigned int i = 0; i < orig.size(); i++) {
    push_back(orig[i]->clone());
  }
}

edaSolutionList::~edaSolutionList() {
  easer();
}

void edaSolutionList::Serialize(edaBuffer &buf, bool pack) {
   if (pack) {
      // then pack the vector
      unsigned _size = this->size();
      buf.Pack(&_size, 1);

      for (unsigned int i = 0; i < _size; i++) {
        edaSolution *sol = at(i);
        sol->doSerialize(buf);
    }    
   }
   else {
    // then unpack the vector
    easer();
    unsigned int _size;
    buf.UnPack(&_size, 1);
    this->resize(_size);
    for (unsigned int i = 0; i < _size; i++) {
      edaSolution *sol = (edaSolution*) classGenerateFromBuffer(buf);
      at(i) = sol;
    }
   }
  
}

edaSolutionList* edaSolutionList::clone() const {
  return new edaSolutionList(*this);
}

void edaSolutionList::easer() {
  for(unsigned int i = 0; i < size(); i++) {
    edaSolution *sol = at(i);
    delete sol;
  }
  clear();  
}

void edaSolutionList::printOn(ostream &os) const {
  for(unsigned int i = 0; i < size(); i++) {
    edaSolution * sol = at(i);        
    os << "(" << i << ") " << *sol;
    if( i != size() - 1)
      os << endl;          
  }
}

ostream& operator<< (ostream &os, const edaSolutionList &list) {
    list.printOn(os);
    return os;
}

edaSolutionList& edaSolutionList::operator = (const edaSolutionList &list) {
  easer();  
  for(unsigned int i = 0; i < list.size(); i++) 
    push_back(list[i]->clone());
  return *this;
}

bool comparator(edaSolution *A, edaSolution *B) {
    return A->getCost() > B->getCost();
}

void edaSolutionList::sort() {
  std::sort(begin(),end(),comparator);
} 

bool edaSolutionList::replace(edaSolutionList& list) {
    unsigned int n = size();
    unsigned int m = list.size();
    if( m > n ) return false;
    sort();
    for(unsigned int i = 0; i < m; i++) {
        edaSolution* sol = at(n - i - 1);
        *sol = *list[m - i - 1];
    } 
    return true;
}

edaSolutionList edaSolutionList::getList(unsigned int num) {
    edaSolutionList list;
    sort();
    for(unsigned int i = 0; i < num && i < size(); i++) {
        list.push_back(at(i)->clone());
    }
    return list;
}


double edaSolutionList::evaluate() const {
  return at(getBestID())->evaluate();
}

edaSolution* edaSolutionList::getBest() const {
  return at(getBestID());
}

unsigned int edaSolutionList::getBestID() const {
  double fitness = at(0)->evaluate();
  unsigned int index = 0;
  for(unsigned int i = 1; i < size(); i++) { 
    double value = at(i)->evaluate();
    if (value > fitness) {
      fitness = value;
      index = i ;
    }
  }
  return index;
}
double edaSolutionList::mean() const {
  double mean = 0;
  unsigned int _size = size();
  for(unsigned int i = 0; i < _size; i++) 
    mean += at(i)->evaluate();
  mean /= _size;
  return mean;
}  

double edaSolutionList::std() const {
  double std = 0;
  double _mean = mean();
  unsigned int _size = size();
  for(unsigned int i = 0; i < _size; i++) 
    std += pow( at(i)->evaluate() - _mean, 2 );
  std = sqrt( std/_size );
  return std;
}

double edaSolutionList::min() const {
  double min = at(0)->evaluate();
  unsigned int _size = size();
  for(unsigned int i = 1; i < _size; i++) {
    double value = at(i)->evaluate();
    if (value < min) {
      min = value;
    }
  }
  return min;
}

double edaSolutionList::max() const {
  double max = at(0)->evaluate();
  unsigned int _size = size();
  for(unsigned int i = 1; i < _size; i++) {
    double value = at(i)->evaluate();
    if (value > max) {
      max = value;
    }
  }
  return max;
}
