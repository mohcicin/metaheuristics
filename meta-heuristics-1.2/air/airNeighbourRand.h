/* 
 * File:   airNeighbourRanNext.h
 * Author: Tieu Minh
 *
 * Created on April 30, 2013, 9:13 AM
 */

#ifndef AIRNEIGHBOURRAND_H
#define	AIRNEIGHBOURRAND_H
#include "Define.h"
class airNeighbourRand: public edaMoveGen {
public:
    airNeighbourRand(unsigned int num = 3);
    airNeighbourRand(const airNeighbourRand& orig);
    virtual ~airNeighbourRand();
    airNeighbourRand *clone() const;
    void Serialize( edaBuffer &buf, bool pack );
    void setNumNeighbour(const unsigned int num);
    bool generate( edaMove *move, const edaSolution &sol );
    setClassID(_USERCLASSID_ + _CLSID_AIR_NEIGHBOURRAND_);
private:
    unsigned int count, num;
};

#endif	/* AIRNEIGHBOURNEXT_H */

