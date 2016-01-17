#ifndef __vrpRouteNext_h__
#define __vrpRouteNext_h__

#include <utility>
#include "../lib/eda.h"
#include "vrpConst.h"
#include "vrpSubRoute.h"
#include "vrpRoute.h"
#include "vrpRouteMove.h"
#include "vrpProblem.h"
using namespace std;
class vrpRouteNext: public edaMoveGen
{
 public:
  vrpRouteNext();
  vrpRouteNext(vrpProblem * problem);
  // Copy constructor
  vrpRouteNext(const vrpRouteNext &m);
  ~vrpRouteNext();
  edaMoveGen *clone() const;
  virtual bool generate( edaMove *move, const edaSolution &sol );
  void Serialize( edaBuffer &buf, bool pack );
  
  setClassID(_USERCLASSID_ + _CLSID_VRP_ROUTE_NEXT_);
private:
    bool isFeasibleMove(vrpRouteMove * move,vrpRoute *route) ;
    vrpProblem* _problem;

};
#endif

