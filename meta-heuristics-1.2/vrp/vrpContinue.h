#ifndef __vrpContinue_h__
#define __vrpContinue_h__

#include "../lib/eda.h"
#include "vrpDefine.h"
#include "vrpConst.h"
class vrpContinue : public edaGenContinue
{
 public:
  vrpContinue() {};
  vrpContinue(unsigned int _maxNumGen, double PAR_0, double PAR_1);
  virtual ~vrpContinue() {};
  virtual edaContinue *clone() const;
  void init();
  bool check(edaSolutionList &pop);
  virtual void Serialize(edaBuffer &buf, bool pack);
    
  setClassID(_USERCLASSID_ + _CLSID_VRP_CONTINUE_);

 private:
  double _prev, _next;
  unsigned int _numRepeat, _count;
  double _par_0, _par_1;
  unsigned int maxNumGen;
  unsigned int numGen;
};

#endif
