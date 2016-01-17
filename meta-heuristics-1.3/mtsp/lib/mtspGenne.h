/* 
 * File:   mtspGenne.h
 * Author: Tieu Minh
 *
 * Created on April 23, 2014, 9:37 AM
 */

#ifndef TSPGENNE_H
#define	TSPGENNE_H


#include "mtspDefine.h"


class mtspGenne : public edaGenne 
{
public:
    
    mtspGenne(unsigned int value = eda::FLAG);
    
    ~mtspGenne();
    
    const char* className() const;

    void print(ostream &os) const;
    
    mtspGenne& operator = (const edaGenne &genne);
    
    mtspGenne& operator = (unsigned int value);
    
    operator unsigned int();
    
    bool operator == (const edaGenne &genne) const;
    
    mtspGenne * clone() const;
    
    void checkError() const;
    
protected:
    unsigned int _value;

};

#endif	/* TSPGENNE_H */

