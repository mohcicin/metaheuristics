#ifndef __tspKOpt_h__
#define __tspKOpt_h__

#include "../lib/eda.h"

#include <utility>
#include "tspDefine.h"
#include "graph.h"

using namespace std;

class tspKOpt : public pair<unsigned int, unsigned int>, public edaMove
{
 public:
  tspKOpt();
  tspKOpt(const tspKOpt &move);
  tspKOpt(const Graph &g);
  virtual ~tspKOpt();

  edaMove* clone() const;
  void init(const edaSolution &sol);
  double incrEval(const edaSolution &sol) const;
  void update( edaSolution &sol ) const;
  void Serialize( edaBuffer &buf, bool pack );
  edaMove& operator = (const edaMove &_move);
  bool operator == (const edaMove &_move) const;
  void printOn( ostream &os ) const;
  setClassID(_USERCLASSID_ + _CLSID_K_OPT_);
  
 private:
  void easer();
  Graph *graph;
};

#endif
