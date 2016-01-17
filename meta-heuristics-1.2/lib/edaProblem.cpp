#include "edaProblem.h" 

void edaProblem::printOn(ostream &os) const {
  os << "edaProblem must be overridden !!!" << endl;
}

ostream& operator<< (ostream &os, const edaProblem &chro) {
  chro.printOn(os);
  return os;
}
