/* 
 * File:   afGenne.cpp
 * Author: root
 * 
 * Created on March 15, 2013, 9:33 AM
 */

#include "airGenne.h"

airGenne::airGenne() {}

airGenne::~airGenne() {}

airGenne::airGenne(double _value) {
    if(_value < 0 || _value > 1) {
        cout << "The value is not encoding ! " << endl;
        exit(1);
    }
    value = _value;
}

airGenne::airGenne(const airGenne& genne) {
    value = genne.value;
}

airGenne* airGenne::clone() const {
    return new airGenne(*this);
} 

void airGenne::Serialize(edaBuffer& buf,bool pack) {
    if (pack)
        buf.Pack(&value, 1);  
    else  
        buf.UnPack(&value, 1);  
}

airGenne& airGenne::operator = (const edaGenne &genne) {
    value = ((airGenne*)&genne)->value;
    return *this; 
}

bool airGenne::operator == (const edaGenne &genne) const {    
    return abs(value - ((airGenne*)&genne)->value) <  0.00001 ?  true : false;
}

void airGenne::printOn(ostream& os) const {
    os << value;
}

void airGenne::swap(edaGenne *genne) {    
    airGenne* airGen = (airGenne*)genne;
    double temp = value;
    value = airGen->value;
    airGen->value = temp;
}

double airGenne::getValue() const {
    return value;
}

airGenne& airGenne::operator = (const double &_value) {
    value = _value;
    return *this; 
}
