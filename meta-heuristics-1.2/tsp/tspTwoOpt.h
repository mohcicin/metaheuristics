#ifndef __tspTwoOpt_h__
#define __tspTwoOpt_h__

#include "../lib/eda.h"

#include <utility>
#include "tspDefine.h"
#include "graph.h"

using namespace std;

class tspTwoOpt : public pair<unsigned int, unsigned int>, public edaMove
{
 public:
  tspTwoOpt();
  tspTwoOpt(const tspTwoOpt &move);
  tspTwoOpt(const Graph &g);

  ~tspTwoOpt();

  edaMove* clone() const;
  void init(const edaSolution &sol);
  double incrEval(const edaSolution &sol) const;
  void update( edaSolution &sol ) const;
  void Serialize( edaBuffer &buf, bool pack );
  edaMove& operator = (const edaMove &_move);
  bool operator == (const edaMove &_move) const;
  void printOn( ostream &os ) const;

  setClassID(_USERCLASSID_ + _CLSID_TWO_OPT_);
  
 private:
  void easer();
  Graph *graph;
};

#endif
