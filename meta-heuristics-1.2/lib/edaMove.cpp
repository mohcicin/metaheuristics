#include "edaMove.h"

void edaMove::printOn(ostream &os) const {
  os << "edaMove must be overridden !!!" << endl;
}

ostream& operator<< (ostream &os, const edaMove &sol) {
  sol.printOn(os);
  return os;
}


