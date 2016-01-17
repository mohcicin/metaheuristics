#ifndef __tspKOptRand_h__
#define __tspKOptRand_h__

#include "../lib/eda.h"
#include "tspKOpt.h"
#include "tspDefine.h"
#include "graph.h"

class tspKOptRand: public edaMoveGen
{
 public:
  tspKOptRand();
  tspKOptRand(Graph &g);
  // Copy constructor
  tspKOptRand(const tspKOptRand &m);

  virtual ~tspKOptRand();
  edaMoveGen *clone() const;

  virtual bool generate( edaMove *move, const edaSolution &sol );

  setClassID(_USERCLASSID_ + _CLSID_K_OPT_RAND_);
  void Serialize(edaBuffer &buf, bool pack);

 private:

  Graph *graph;
};

#endif
