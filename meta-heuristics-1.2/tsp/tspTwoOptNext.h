#ifndef __tspTwoOptNext_h__
#define __tspTwoOptNext_h__

#include <utility>

#include "../lib/eda.h"

#include "tspDefine.h"
#include "graph.h"

class tspTwoOptNext: public edaMoveGen
{
 public:
  tspTwoOptNext();
  tspTwoOptNext(const Graph &g);
  // Copy constructor
  tspTwoOptNext(const tspTwoOptNext &m);

  ~tspTwoOptNext();

  edaMoveGen *clone() const;

  virtual bool generate( edaMove *move, const edaSolution &sol );
  void Serialize( edaBuffer &buf, bool pack );

  setClassID(_USERCLASSID_ + _CLSID_TWO_OPT_NEXT_);

 private:
  void easer();
  Graph *graph;
};

#endif
