/* 
 * File:   mtspGenne.cpp
 * Author: Tieu Minh
 * 
 * Created on April 23, 2014, 9:37 AM
 */

#include "mtspGenne.h"


mtspGenne::mtspGenne(unsigned int value)
{
    _value = value;
}

mtspGenne::~mtspGenne() 
{
}

const char* mtspGenne::className() const
{
    return "mtspGenne";
}

void mtspGenne::print(ostream &os) const 
{
    os << _value;
}

mtspGenne& mtspGenne::operator = (unsigned int value)
{
    _value = value;
    return *this;
}

mtspGenne& mtspGenne::operator = (const edaGenne &genne) 
{
     mtspGenne& stop = (mtspGenne&) genne;
     _value = stop._value;
     return *this;
}

bool mtspGenne::operator == (const edaGenne &genne) const
{
    const mtspGenne& stop = (mtspGenne&) genne; 
    return _value == stop._value;
}

mtspGenne* mtspGenne::clone() const
{
    mtspGenne* genne = new mtspGenne();
    genne->_value = _value;
    return genne; 
}

void mtspGenne::checkError() const 
{
    if(_value == eda::FLAG)
        throw edaException(this, "The value of genne is not set !");
}

mtspGenne::operator unsigned int()
{
    return _value;
}
