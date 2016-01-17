/* 
 * File:   mtspNeighbour.h
 * Author: Tieu Minh
 *
 * Created on April 15, 2014, 10:31 AM
 */

#ifndef TSPTWNEIGHBOUR_H
#define	TSPTWNEIGHBOUR_H

#include "mtspDefine.h"
#include "mtspSolution.h"

class mtspNeighbour : public edaNeighbour {
public:    
    // Construction
    mtspNeighbour() 
    {
        _route = NULL;
        _gain = NAN;
    }
    
    ~mtspNeighbour()
    {
        easer();
    }
    
    // Method
    virtual void set(const edaSolution& sol) 
    {  
        mtspSolution& route = (mtspSolution&) sol;
        route.checkError();
        _route = &route; 

    }
    
    virtual double evaluate() = 0;  
    
    virtual mtspNeighbour* clone() const = 0;
    
    virtual void update(edaSolution& sol) = 0;
    
    virtual void checkError() const
    {
        if(_route == NULL)
            throw edaException(this, "Not set route !");
    }
    
    virtual void next() = 0;
    
    virtual void rand() = 0;
    
    virtual void easer()
    {
        _route = NULL;
        _gain = NAN;
    }
    virtual void init() = 0;
    
    virtual void print(ostream& os) const = 0;
    
    virtual void serialize(edaBuffer& buf, bool pack) 
    {
        if(pack)
        {
            buf.pack( &_gain );
        }
        else
        {
            buf.unpack( &_gain );
        }
    }
    
    virtual mtspNeighbour& operator =(const edaNeighbour& neighb) = 0;
    
    virtual bool operator ==(const edaNeighbour& neighb) const = 0;
    
    virtual const char* className() const = 0;

protected:
    const mtspSolution* _route;
    double _gain;
};

#endif	/* TSPNEIGHBOUR_H */

