/* 
 * File:   vrpRoute.cpp
 * Author: Administrator
 * 
 * Created on June 7, 2012, 11:03 PM
 */

#include <algorithm>
#include "vrpRoute.h"

vrpRoute::vrpRoute() {}
vrpRoute::vrpRoute(const vrpRoute& route) {  
    for(unsigned int i = 0; i < route.size(); i++) {
        vrpSubRoute* sub = route[i]->clone();
        push_back(sub);
    }
}

vrpRoute::~vrpRoute() {
    for(unsigned int i = 0; i < size(); i++) {
        vrpSubRoute* sub =  at(i);
        if(sub != NULL) delete sub;
    }
    clear();
}

vrpRoute *vrpRoute::clone() const {
    return new vrpRoute (*this);
}

double vrpRoute::evaluate() {
    double _cost = 0;
    for(unsigned int i = 0; i < size(); i++) 
        _cost += at(i)->evaluate();
    return _cost;
}

void vrpRoute::update() {    
    at(0)->update();
    double coming = 0;
    for(unsigned int i = 1; i < size(); i++) {
        vrpSubRoute *prev = at(i - 1);  
        vrpSubRoute *sub = at(i);  
        coming = prev->getComingTime( at(i-1)->size() - 1 );
        sub->setComingTime(coming);
        sub->update();
//        if( sub->isRedundancy() ) 
//        {
//            prev->mergeSub(sub);
//            erase(begin() + i);
//            delete sub;
//            i--;
//        }
    }
}
double vrpRoute::getTotalMoveDist() const {
    double _dist = 0;
    for(unsigned int i = 0; i < size(); i++) 
        _dist += at(i)->getTotalMoveDist();
    return _dist;
}
double vrpRoute::getTotalLoad() const {
    double _load = 0;
    for(unsigned int i = 0; i < size(); i++) 
        _load += at(i)->getTotalLoad();
    return _load;
}
double vrpRoute::getTotalWaitTime() const {
    double _wait_time = 0;
    for(unsigned int i = 0; i < size(); i++) 
        _wait_time += at(i)->getTotalWaitTime();
    return _wait_time;
}
double vrpRoute::getTotalMoveTime() const {
    double _move_time = 0;
    for(unsigned int i = 0; i < size(); i++) 
        _move_time += at(i)->getTotalMoveTime();
    return _move_time;
}
double vrpRoute::getServiceTime() const {
    double _service_time = 0;
    for(unsigned int i = 0; i < size(); i++) 
        _service_time += at(i)->getTotalServicesTime();
    return _service_time;
}
double vrpRoute::getTotalUseTime() const {
    double _use_time = 0;
    for(unsigned int i = 0; i < size(); i++) 
        _use_time += at(i)->getTotalUseTime();
    return _use_time;
}
vrpConst* vrpRoute::getParameter() const {
    if(size() > 0) return at(0)->getParameter(); 
    return NULL;
}
double vrpRoute::getShapeMetric() const {
    double result = 0;
    for(unsigned int i = 0; i < size(); i++) 
        result += at(i)->getShapeMetric();
    return result;
}
void vrpRoute::printOn(ostream& os) const {
    for(unsigned int i = 0; i < size(); i++) {
        vrpSubRoute *subroute = at(i);
        subroute->printOn(os);
    }   
}
void vrpRoute::debug(ostream &os) const {
    for(unsigned int i = 0 ; i < size() ; i++) {
        vrpSubRoute* sub = at(i);
        sub->debug(os);
    }
}
edaSolution& vrpRoute::operator = (const edaSolution &sol) {
    vrpRoute &myRoute = (vrpRoute&) sol;    
    return operator = (myRoute);
}

vrpRoute& vrpRoute::operator = (const vrpRoute &route) {
    for(unsigned int i = 0; i < route.size(); i++)      
        push_back(route[i]->clone());
    return *this;
}

bool vrpRoute::operator == (const edaSolution &sol) const{
    vrpRoute &myRoute = (vrpRoute&) sol;
    unsigned int size = myRoute.size();
    if(size != this->size())
        return false;
    for(unsigned int i = 0; i < size; i++)         
        if(*(this->at(i)) != *(myRoute[i]))
            return false;    
    return true;
}

void vrpRoute::Serialize(edaBuffer &buf, bool pack ){
    if ( pack ){    
      unsigned int size  = this->size();
      buf.Pack( &size, 1 );
      for (unsigned int i=0; i< size; i++) {
        vrpSubRoute* sub = this->at(i);
        sub->doSerialize( buf,pack);
      }
    }
    else {
        unsigned int size;
        buf.UnPack( &size, 1 );
        if(this->size() > 0) {
            for(unsigned int i = 0; i < this->size(); i++) {
                vrpSubRoute* sub = this->at(i);
                delete sub;
            }
        }
        this->clear();
        for (unsigned int i = 0; i < size; i++) {
            vrpSubRoute* sub = (vrpSubRoute*)classGenerateFromBuffer( buf );
            this->push_back(sub);
        }
    }
}

double vrpRoute::getCost() const {
  return -1;
}

void vrpRoute::init() {}

bool vrpRoute::isRedundancy() const {
//    if( size() == 1 && at(0)->isRedundancy() ) {
//        cout << "Route: " << *this << endl;
//        return true;
//    }
    return false;
}
