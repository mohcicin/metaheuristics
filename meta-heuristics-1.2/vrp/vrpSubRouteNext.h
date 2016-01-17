#ifndef __vrpSubNext_h__
#define __vrpSubNext_h__

#include <utility>
#include "../lib/eda.h"
#include "vrpConst.h"
#include "vrpSubRoute.h"
#include "vrpRoute.h"
#include "vrpSubRouteMove.h"
#include "vrpProblem.h"
using namespace std;
class vrpSubRouteNext: public edaMoveGen
{
 public:
    vrpSubRouteNext();
    vrpSubRouteNext(vrpProblem* problem);
    // Copy constructor
    vrpSubRouteNext(const vrpSubRouteNext &move);
    ~vrpSubRouteNext();
    edaMoveGen *clone() const;
    virtual bool generate( edaMove *move, const edaSolution &sol );
    void Serialize( edaBuffer &buf, bool pack );
    setClassID(_USERCLASSID_ + _CLSID_VRP_SUBROUTE_NEXT_);
private:
    bool isFeasibleMove(vrpSubRouteMove* move,vrpSubRoute *sub) ;
    vrpProblem* _problem;

};
#endif

