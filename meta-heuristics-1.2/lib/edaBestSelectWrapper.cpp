/* 
 * File:   edaBestSelectWrapper.cpp
 * Author: Tieu Minh
 * 
 * Created on August 22, 2013, 8:14 AM
 */

#include "edaBestSelectWrapper.h"

edaBestSelectWrapper::edaBestSelectWrapper() {}

bool edaBestSelectWrapper::select(edaSolutionList& list) const {
  //Checking the invalid list solution 
  if(list.size() == 0)
    return false;
  for(unsigned int i = 0; i < list.size(); i++) {
    if (list[i] == NULL)
      return false;
  }  
  edaSolution *sol = list.getBest()->clone();    
  list.easer();
  list.push_back(sol);
  return true;
}

edaBestSelectWrapper * edaBestSelectWrapper::clone() const {
  return new edaBestSelectWrapper();
}
