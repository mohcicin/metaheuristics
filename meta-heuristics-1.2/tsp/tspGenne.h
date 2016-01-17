/* 
 * File:   tspGenne.h
 * Author: Tieu Minh
 *
 * Created on May 2, 2013, 10:05 PM
 */

#ifndef _tspGenne_h_
#define	_tspGenne_h_
#include "tspDefine.h"

class tspGenne: public edaGenne {
public:
    tspGenne();
    tspGenne(unsigned int value);
    tspGenne(const tspGenne& genne);
    virtual ~tspGenne();
    tspGenne *clone() const;
    double getValue() const;
    void swap(edaGenne *genne);
    void printOn(ostream& os) const;
    void Serialize(edaBuffer& buf,bool pack);
    tspGenne& operator = (const edaGenne &genne); 
    bool operator == (const edaGenne &genne) const;
    setClassID(_USERCLASSID_ + _CLSID_TSP_GENNE_);
private:
    unsigned int value;
};

#endif	/* _tspGenne_h_ */

