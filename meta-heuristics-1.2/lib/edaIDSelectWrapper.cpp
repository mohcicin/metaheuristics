/* 
 * File:   edaIDSelectWrapper.cpp
 * Author: Tieu Minh
 * 
 * Created on August 22, 2013, 8:14 AM
 */

#include "edaIDSelectWrapper.h"


edaIDSelectWrapper::edaIDSelectWrapper(unsigned int id) {
	this->id = id; 
}

bool edaIDSelectWrapper::select(edaSolutionList& list) const {
  //Checking the invalid list solution 
  if(id + 1 > list.size() )
    return false;
  
  //Select the solution
  edaSolution *sol = list[id]->clone();
  list.easer();
  list.push_back(sol);
  return true;
}

edaIDSelectWrapper * edaIDSelectWrapper::clone() const {
  return new edaIDSelectWrapper(id);
}
