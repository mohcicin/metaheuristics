#ifndef _tspSolution_h_
#define _tspSolution_h_

#include <vector>
#include "../lib/eda.h"
#include "tspDefine.h"
#include "graph.h"

class tspSolution: public vector<unsigned int>, public edaSolution
{
 public:
  tspSolution();
  tspSolution(const Graph &_graph);
  tspSolution(const tspSolution &sol);
  virtual ~tspSolution();  
  edaSolution* clone() const; // Nh�n b?n ??i t??ng
  double evaluate(); // L??ng gi� t�nh to�n gi� tr? fitness
  double getCost() const; // L?y gi� tr? fitness ??a tr�n l?n l??ng gi� tr??c ?�
  void init(); // Kh?i t?o ng?u nhi�n nghi?m ban ??u
  void setCost(double value); // Thi?t l?p cho gi� tr? fitness
  void Serialize( edaBuffer &buf, bool pack ); // ?�ng g�i d? li?u v� t�i t?o l?i ??i t??ng 
  void printOn(ostream &os) const; // Xu?t k?t qu? ra output stream
  edaSolution& operator = (const edaSolution &sol);
  bool operator == (const edaSolution &sol) const;
  void setModified( bool status = true );
  setClassID(_USERCLASSID_ + _CLSID_TSP_SOLUTION_);
  void save(const char* filename);
private:
  void easer();  
  
  Graph *graph;
  double cost;
};

#endif
