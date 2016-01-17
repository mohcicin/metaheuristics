#include "edaNaturalSelection.h"
void edaNaturalSelection::printOn(ostream &os) const {
  os << "edaSelection must be overridden !!!" << endl;
}
ostream& operator<< (ostream &os, const edaNaturalSelection &nslect) {
  nslect.printOn(os);
  return os;
}
