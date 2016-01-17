/* 
 * File:   airGenne.h
 * Author: Tieu Minh
 *
 * Created on May 2, 2013, 10:05 PM
 */

#ifndef AIRGENNE_H
#define	AIRGENNE_H
#include "Define.h"

class airGenne: public edaGenne {
public:
    airGenne();
    airGenne(double value);
    airGenne(const airGenne& genne);
    virtual ~airGenne();
    airGenne *clone() const;
    double getValue() const;
    void swap(edaGenne *genne);
    void printOn(ostream& os) const;
    void Serialize(edaBuffer& buf,bool pack);
    airGenne& operator = (const edaGenne &genne); 
    airGenne& operator = (const double &value); 
    bool operator == (const edaGenne &genne) const;
    setClassID(_USERCLASSID_ + _CLSID_AIR_GENNE_);
private:
    double value;
};

#endif	/* AIRGENNE_H */

