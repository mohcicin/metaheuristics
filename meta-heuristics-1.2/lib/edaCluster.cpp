/* 
 * File:   edaCluster.cpp
 * Author: Tieu Minh
 * 
 * Created on September 3, 2013, 9:44 AM
 */

#include "edaCluster.h"

bool edaCluster::isOverlap(const edaCluster& _clus) {
  int count = 0;
  for(unsigned int i = 0; i < size(); i++) {
    int key = at(i)->getKey();
    for(unsigned int j = 0; j < _clus.size(); j++) {
      if(key == _clus[j]->getKey() ) {
        count ++;
        break;
      }
    }
    if(count > 1)
      return true;
  }
  return false;  
}

bool edaCluster::isCover(const edaCluster& _clus) {
  unsigned int i, j;
  for(i = 0; i < _clus.size(); i++) {
    int key = _clus[i]->getKey();
    for(j = 0; j < size(); j++) {
      if(key == at(j)->getKey())
        break;
    }
    if(j == size() )
      return false;
  }
  return true; 
}
void edaCluster::printOn(ostream &os) const {
  for(unsigned int i = 0; i < size() - 1 ; i++) {
    os << at(i)->getKey() << " ";
  }
  os << at( size() - 1 )->getKey();
}
ostream& operator<< (ostream &os, const edaCluster &clus) {
  clus.printOn(os);
  return os;
}
