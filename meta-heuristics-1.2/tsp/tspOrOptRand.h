#ifndef __tspOrOptRand_h__
#define __tspOrOptRand_h__

#include <utility>

#include "../lib/eda.h"
#include "tspDefine.h"
#include "graph.h"

class tspOrOptRand: public edaMoveGen
{
 public:
  tspOrOptRand();
  tspOrOptRand(const Graph &g);
  tspOrOptRand(const tspOrOptRand &m);

  ~tspOrOptRand();

  edaMoveGen *clone() const;

  virtual bool generate( edaMove *move, const edaSolution &sol );
  void Serialize( edaBuffer &buf, bool pack );

  setClassID(_USERCLASSID_ + _CLSID_OR_OPT_RAND_);

 private:
  void easer();
  Graph *graph;
};

#endif
