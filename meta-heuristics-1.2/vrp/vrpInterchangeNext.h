#ifndef __vrpInterchangeNext_h__
#define __vrpInterchangeNext_h__

#include <utility>
#include "../lib/eda.h"
#include "vrpConst.h"
#include "vrpProblem.h"
#include "vrpInterchangeMove.h"
#include "vrpSolution.h"
using namespace std;
class vrpInterchangeNext: public edaMoveGen
{
public:
    vrpInterchangeNext(unsigned int lambda = 2);
    vrpInterchangeNext(vrpProblem* problem, unsigned int lambda = 2);
    vrpInterchangeNext(const vrpInterchangeNext &m);
    ~vrpInterchangeNext();
    edaMoveGen *clone() const;
    virtual bool generate( edaMove *move, const edaSolution &sol );
    void Serialize( edaBuffer &buf, bool pack );
    setClassID(_USERCLASSID_ + _CLSID_VRP_INTERCHANGE_NEXT_);
    
private:
    vrpProblem* _problem;
    unsigned int lambda;
    bool isFeasibleMove(vrpSolution* vrpSol, vrpInterchangeMove* move);
};
#endif

