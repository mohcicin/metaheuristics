#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <math.h>

#include "../lib/eda.h"
#include "tspDefine.h"
using namespace std;

class Graph : public edaProblem {
public:
  Graph();
  Graph(const char *fileName);
  Graph(const Graph &g);
  ~Graph();

  Graph* clone() const;
  void load(const char *fileName);
  float distance(unsigned int from, unsigned int to);
  unsigned int size() const;
  double x(unsigned int id) const;
  double y(unsigned int id) const;
  Graph& operator = (const edaProblem &pro);   
  void Serialize(edaBuffer &buf, bool pack);
  void printOn(ostream &os) const;  
  setClassID(_USERCLASSID_ + _CLSID_GRAPH_);

private:
  void easer();
    
  unsigned int numVert;
  double *vectCoord;
};

#endif /*GRAPH_H_*/
