#ifndef __tspOrOptNext_h__
#define __tspOrOptNext_h__

#include <utility>

#include "../lib/eda.h"
#include "tspDefine.h"
#include "graph.h"

class tspOrOptNext: public edaMoveGen
{
 public:
  tspOrOptNext();
  tspOrOptNext(const Graph &g);
  // Copy constructor
  tspOrOptNext(const tspOrOptNext &m);

  ~tspOrOptNext();

  edaMoveGen *clone() const;

  virtual bool generate( edaMove *move, const edaSolution &sol );
  void Serialize( edaBuffer &buf, bool pack );

  setClassID(_USERCLASSID_ + _CLSID_OR_OPT_NEXT_);

 private:
  void easer();
  Graph *graph;
};

#endif
