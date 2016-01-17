/* 
 * File:   edaNoSelectWapper.cpp
 * Author: tieuminh
 * 
 * Created on September 25, 2013, 8:29 AM
 */

#include "edaNoSelectWapper.h"
#include "edaSolutionList.h"

edaNoSelectWapper::edaNoSelectWapper() {
}

edaNoSelectWapper::~edaNoSelectWapper() {
}

bool edaNoSelectWapper::select(edaSolutionList& list) const {
  //Checking the invalid list solution 
  if(list.size() > 0) 
    list.easer(); 
  return true;
}
edaNoSelectWapper * edaNoSelectWapper::clone() const {
  return new edaNoSelectWapper();
}
