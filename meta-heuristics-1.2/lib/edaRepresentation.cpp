#include "edaRepresentation.h" 



void edaRepresentation::printOn(ostream &os) const {
  os << "edaProblem must be overridden !!!" << endl;
}

ostream& operator<< (ostream &os, const edaRepresentation &repre) {
  repre.printOn(os);
  return os;
}


