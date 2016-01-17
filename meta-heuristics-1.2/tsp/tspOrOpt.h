#ifndef __tspOrOpt_h__
#define __tspOrOpt_h__

#include "../lib/eda.h"
#include "tspDefine.h"
#include "graph.h"

using namespace std;

class tspOrOpt : public edaMove
{
 public:
  tspOrOpt(unsigned int lambda = 2);
  tspOrOpt(const tspOrOpt &move);
  tspOrOpt(const Graph &g, unsigned int lambda = 2);
  virtual ~tspOrOpt();

  edaMove* clone() const;
  void init(const edaSolution &sol);
  double incrEval(const edaSolution &sol) const;
  void update( edaSolution &sol ) const;
  void Serialize( edaBuffer &buf, bool pack );
  edaMove& operator = (const edaMove &_move);
  bool operator == (const edaMove &_move) const;
  void printOn( ostream &os ) const;
  setClassID(_USERCLASSID_ + _CLSID_OR_OPT_);
  
//Properties
  unsigned int LAMBDA;
  unsigned int FIRST;
  unsigned int SECOND;
  
private:
  void easer();
  Graph *graph;  

};

#endif
