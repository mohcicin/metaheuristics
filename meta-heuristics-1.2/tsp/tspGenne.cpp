/* 
 * File:   tspGenne.cpp
 * Author: root
 * 
 * Created on March 15, 2013, 9:33 AM
 */

#include "tspGenne.h"

tspGenne::tspGenne() {}

tspGenne::~tspGenne() {}

tspGenne::tspGenne(unsigned int _value) {
    if(_value < 0) {
        cerr << "The value is not encoding ! " << endl;
        exit(1);
    }
    value = _value;
}

tspGenne::tspGenne(const tspGenne& genne) {
    value = genne.value;
}

tspGenne* tspGenne::clone() const {
    return new tspGenne(*this);
} 

void tspGenne::Serialize(edaBuffer& buf,bool pack) {
    if (pack)
        buf.Pack(&value, 1);  
    else  
        buf.UnPack(&value, 1);  
}

tspGenne& tspGenne::operator = (const edaGenne &genne) {
    value = ((tspGenne*)&genne)->value;
    return *this; 
}

bool tspGenne::operator == (const edaGenne &genne) const {    
    return value - ((tspGenne*)&genne)->value ==  0 ?  true : false;
}

void tspGenne::printOn(ostream& os) const {
    os << value;
}

void tspGenne::swap(edaGenne *genne) {    
    tspGenne* tspGen = (tspGenne*)genne;
    unsigned int temp = value;
    value = tspGen->value;
    tspGen->value = temp;
}

double tspGenne::getValue() const {
  return value;
}
