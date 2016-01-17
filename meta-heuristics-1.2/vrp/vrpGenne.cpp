/* 
 * File:   vrpGenne.cpp
 * Author: tieuminh
 * 
 * Created on May 16, 2012, 12:13 PM
 */

#include "vrpGenne.h"

vrpGenne::vrpGenne() {}

vrpGenne::vrpGenne(vrpStop *stop) {   
    _value = stop->ID;
}

vrpGenne* vrpGenne::clone() const {
    return new vrpGenne(*this);
}

void vrpGenne::swap(edaGenne *genne) {
    vrpGenne* vrpGen = (vrpGenne*)genne;
    unsigned int temp = _value;
    _value = vrpGen->_value;
    vrpGen->_value = temp;
}

vrpGenne::vrpGenne(const vrpGenne& orig) {
    _value = orig._value;
}
vrpGenne::vrpGenne(const unsigned int stop_id) {
    _value = stop_id;
}
vrpGenne::~vrpGenne() {}

unsigned int vrpGenne::getValue() const {
    return _value;
}

bool vrpGenne::operator == (const edaGenne &genne) const {   
    return _value == ((vrpGenne*)&genne)->_value;
}

vrpGenne& vrpGenne::operator = (const edaGenne &genne) {  
    _value = ((vrpGenne*)&genne)->_value;
    return *this; 
}

void vrpGenne::printOn(ostream &os) const {
    os << _value;
}

void vrpGenne::Serialize(edaBuffer& buf, bool pack) {
    if (pack){    
        buf.Pack(&_value, 1 );
    } 
    else {
        buf.UnPack(&_value, 1);
    }
}

vrpGenne& vrpGenne::operator = (const char *code) {
  _value = atoi(code);
  return *this;
}
