#include "edaSolution.h"

void edaSolution::printOn(ostream &os) const {
  os << "edaSolution must be overridden !!!" << endl;
}

ostream& operator<< (ostream &os, const edaSolution &sol) {
  sol.printOn(os);
  return os;
}
