#include "edaGenne.h"

  bool edaGenne::operator != (const edaGenne &genne) const {
    return ! operator ==(genne);
  } 

ostream& operator<< (ostream &os, const edaGenne &genne) {
    genne.printOn(os);
    return os;
}
