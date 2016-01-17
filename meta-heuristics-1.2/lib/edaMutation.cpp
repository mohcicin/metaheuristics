#include "edaMutation.h"
void edaMutation::printOn(ostream &os) const {
  os << "edaMutation must be overridden !!!" << endl;
}
ostream& operator<< (ostream &os, const edaMutation &mute) {
  mute.printOn(os);
  return os; 
}
