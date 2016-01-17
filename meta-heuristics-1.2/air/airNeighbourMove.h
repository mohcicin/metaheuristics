/* 
 * File:   AIRNEIGHBOURMOVE.h
 * Author: Tieu Minh
 *
 * Created on April 29, 2013, 10:55 AM
 */

#ifndef AIRNEIGHBOURMOVE_H
#define	AIRNEIGHBOURMOVE_H

#include "Define.h"


class airNeighbourMove: public pair<unsigned int, unsigned int>, public edaMove {
public:
    airNeighbourMove();
    airNeighbourMove(const airNeighbourMove& orig);
    virtual ~airNeighbourMove();
    airNeighbourMove* clone() const;
    void init(const edaSolution &sol);
    double incrEval(const edaSolution &sol) const;
    void update( edaSolution &sol ) const;
    airNeighbourMove& operator = (const edaMove& move);
    void Serialize( edaBuffer &buf, bool pack );
    bool operator == (const edaMove &_move) const;
    void printOn( ostream &os ) const;
    setClassID(_USERCLASSID_ + _CLSID_AIR_NEIGHBOURMOVE_);
};

#endif	/* AIRNEIGHBOURMOVE_H */

