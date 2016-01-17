#ifndef _vrpCyclicNext_h
#define _vrpCyclicNext_h

#include <utility>
#include "../lib/eda.h"
#include "vrpConst.h"
#include "vrpProblem.h"
#include "vrpCyclicMove.h"
#include "vrpSolution.h"
using namespace std;
class vrpCyclicNext: public edaMoveGen
{
 public:
  vrpCyclicNext(unsigned int lambda = 2);
  vrpCyclicNext(vrpProblem* pro, unsigned int lambda = 2);
  vrpCyclicNext(const vrpCyclicNext &m);
  edaMoveGen *clone() const;
  virtual ~vrpCyclicNext();

  virtual bool generate( edaMove *move, const edaSolution &sol );
  void Serialize( edaBuffer &buf, bool pack );
  setClassID(_USERCLASSID_ + _CLSID_VRP_CYCLIC_NEXT_);

  
private:  
  vrpProblem* problem;
  unsigned int lambda;
  bool isFeasibleMove(const vrpSolution* vrpSol, vrpCyclicMove* move);

 
};
#endif

