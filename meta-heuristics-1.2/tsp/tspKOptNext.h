#ifndef __tspKOptNext_h__
#define __tspKOptNext_h__

#include <utility>

#include "../lib/eda.h"
#include "tspDefine.h"
#include "graph.h"

class tspKOptNext: public edaMoveGen
{
 public:
  tspKOptNext();
  tspKOptNext(const Graph &g);
  tspKOptNext(const tspKOptNext &m);
  virtual ~tspKOptNext();

  edaMoveGen *clone() const;

  virtual bool generate( edaMove *move, const edaSolution &sol );
  void Serialize( edaBuffer &buf, bool pack );

  setClassID(_USERCLASSID_ + _CLSID_K_OPT_NEXT_);

 private:
  void easer();
  Graph *graph;
};

#endif
