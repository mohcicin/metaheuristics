#ifndef _vrpCyclicMove_h
#define _vrpCyclicMove_h

#include "../lib/eda.h"
#include <utility>
#include "vrpConst.h"

class vrpCyclicMove : public edaMove
{
public:
    vrpCyclicMove();
    vrpCyclicMove(const vrpCyclicMove &move);
    ~vrpCyclicMove();

    edaMove* clone() const;
    void init(const edaSolution &sol);
    double incrEval(const edaSolution &sol) const;
    void update( edaSolution &sol ) const;
    void Serialize( edaBuffer &buf, bool pack );
    edaMove& operator = (const edaMove &_move);
    bool operator == (const edaMove &_move) const;
    setClassID(_USERCLASSID_ + _CLSID_VRP_CYCLIC_MOVE_);
    void printOn(ostream& os) const;

  
//Properties  
    vector<unsigned int> NUM_OPT;
    vector<unsigned int> POS_OPT;
    vector<unsigned int> ID_SUB;

    double INC_DIST;
    double INC_MOVE_TIME;
    double INC_WAIT_TIME;

private:
  void easer();


};

#endif

