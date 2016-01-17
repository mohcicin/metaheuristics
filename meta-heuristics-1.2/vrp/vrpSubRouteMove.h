#ifndef _vrpSubMove_h
#define _vrpSubMove_h

#include "../lib/eda.h"
#include <utility>
#include "vrpConst.h"

class vrpSubRouteMove : public edaMove
{
public:
    vrpSubRouteMove();
    vrpSubRouteMove(const vrpSubRouteMove &move);
    ~vrpSubRouteMove();

    edaMove* clone() const;
    void init(const edaSolution &sol);
    double incrEval(const edaSolution &sol) const;
    void update( edaSolution &sol ) const;
    void Serialize( edaBuffer &buf, bool pack );
    edaMove& operator = (const edaMove &_move);
    bool operator == (const edaMove &_move) const;
    setClassID(_USERCLASSID_ + _CLSID_VRP_SUBROUTE_MOVE_);
    void printOn(ostream& os) const;

//Properties
    unsigned int NUM_OPT_1;
    unsigned int NUM_OPT_2;
    unsigned int POS_OPT_1;
    unsigned int POS_OPT_2;
    double INC_DIST;
    double INC_WAIT_TIME;
    double INC_MOVE_TIME;
};

#endif

