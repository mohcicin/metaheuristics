#ifndef __vrpCyclicRand_h__
#define __vrpCyclicRand_h__

#include <utility>
#include "../lib/eda.h"
#include "vrpConst.h"
#include "vrpProblem.h"
#include "vrpCyclicMove.h"
#include "vrpSolution.h"
using namespace std;
class vrpCyclicRand: public edaMoveGen
{
 public:
  vrpCyclicRand(unsigned int lambda = 2);
  vrpCyclicRand(vrpProblem* pro, unsigned int lambda = 2);
  vrpCyclicRand(const vrpCyclicRand &m);
  edaMoveGen *clone() const;
  virtual ~vrpCyclicRand();

  virtual bool generate( edaMove *move, const edaSolution &sol );
  void Serialize( edaBuffer &buf, bool pack );
  setClassID(_USERCLASSID_ + _CLSID_VRP_CYCLIC_RAND_);

  
private:  
  vrpProblem* problem;
  unsigned int lambda;
  bool isFeasibleMove(const vrpSolution* vrpSol, vrpCyclicMove* move);

 
};
#endif

