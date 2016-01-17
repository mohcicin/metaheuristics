#include "edaContinue.h"

void edaContinue::init()  {
  loop = 0;
}

bool edaContinue::check(const edaSolutionList &list) {
  loop++;
  return true;
}

void edaContinue::Serialize(edaBuffer &buf, bool pack) {
  if(pack) {
    buf.Pack( &loop, 1);
  }
  else {
    buf.UnPack( &loop, 1);
  }
}

void edaContinue::printOn(ostream &os) const {
  os << loop;
}

ostream& operator<< (ostream &os, const edaContinue &con) {
  con.printOn(os);
  return os;
}
