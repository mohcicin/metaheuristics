/* 
 * File:   airNeighbourNext.h
 * Author: Tieu Minh
 *
 * Created on April 30, 2013, 9:13 AM
 */

#ifndef AIRNEIGHBOURNEXT_H
#define	AIRNEIGHBOURNEXT_H
#include "Define.h"
class airNeighbourNext: public edaMoveGen {
public:
    airNeighbourNext();
    airNeighbourNext(const airNeighbourNext& orig);
    virtual ~airNeighbourNext();
    airNeighbourNext *clone() const;
    void Serialize( edaBuffer &buf, bool pack );
    bool generate( edaMove *move, const edaSolution &sol );
    setClassID(_USERCLASSID_ + _CLSID_AIR_NEIGHBOURNEXT_);
private:

};

#endif	/* AIRNEIGHBOURNEXT_H */

