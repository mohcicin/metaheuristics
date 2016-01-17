#ifndef __tspTwoOptMoveRandom_h__
#define __tspTwoOptMoveRandom_h__

#include "../lib/eda.h"

#include "tspDefine.h"
#include "graph.h"

class tspTwoOptMoveRandom: public edaMoveGen
{
 public:
  tspTwoOptMoveRandom();
  tspTwoOptMoveRandom(Graph &g);
  // Copy constructor
  tspTwoOptMoveRandom(const tspTwoOptMoveRandom &m);

  virtual ~tspTwoOptMoveRandom();
  edaMoveGen *clone() const;

  virtual bool generate( edaMove *move, const edaSolution &sol );

  setClassID(_USERCLASSID_ + _CLSID_TWO_OPT_MOVE_RANDOM_);
  void Serialize(edaBuffer &buf, bool pack);

 private:

  Graph *graph;
};

#endif
