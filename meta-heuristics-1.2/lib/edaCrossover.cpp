#include "edaCrossover.h"
void edaCrossover::printOn(ostream &os) const {
  os << "edaCrossover must be overridden !!!" << endl;
}
ostream& operator<< (ostream &os, const edaCrossover &cross) {
  cross.printOn(os);
  return os;        
}
