#include "edaNS.h"

edaNS::edaNS(int _power)
  : edaSearch(_power)
{
}

edaNS::edaNS(
    int _timeout,
    int _power)
  : edaSearch(_timeout, _power)
{
}

edaNS::edaNS(const edaNS &ns) 
  : edaSearch(ns) 
{
}

edaNS *edaNS::clone() const {
  return new edaNS(*this);
}


edaNS::~edaNS()
{
}

bool edaNS::search(edaSolutionList &list) 
{
  printCSVLog("NS", TaskID, ProcID, "F", list.getBestID() , "0", list);   
  return true;
}

void edaNS::Serialize(edaBuffer &buf, bool pack)
{
  edaSearch::Serialize(buf, pack);
}
