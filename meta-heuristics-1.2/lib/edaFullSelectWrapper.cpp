/* 
 * File:   edaFullSelectWrapper.cpp
 * Author: Tieu Minh
 * 
 * Created on August 22, 2013, 10:31 PM
 */

#include "edaFullSelectWrapper.h"

edaFullSelectWrapper::edaFullSelectWrapper() {}

bool edaFullSelectWrapper::select(edaSolutionList& list) const {
  //Checking the invalid list solution 
  if(list.size() == 0)
    return false;
  for(unsigned int i = 0; i < list.size(); i++) {
    if (list[i] == NULL)
      return false;
  }
  return true;
}
edaFullSelectWrapper * edaFullSelectWrapper::clone() const {
  return new edaFullSelectWrapper();
}

edaFullSelectWrapper::~edaFullSelectWrapper() {
}
