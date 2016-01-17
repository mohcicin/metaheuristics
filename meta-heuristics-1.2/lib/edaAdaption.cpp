#include <list>
#include "edaAdaption.h"
#include "edaRNG.h"


edaAdaption::edaAdaption(edaSearch *_lSearch, double _rate) {
  rate = _rate;
  lsearch = _lSearch->clone();
}

edaAdaption::edaAdaption(const edaAdaption& adapt) {
  rate = adapt.rate;
  lsearch = adapt.lsearch->clone();
}

edaAdaption* edaAdaption::clone() const {
  return new edaAdaption(*this);
}

void edaAdaption::update(edaSolutionList &list) const { 
  edaSolutionList* newList = new edaSolutionList();
  vector<unsigned int> index;
  for(unsigned int i = 0; i < list.size(); i++) {
    double prob = rnd.uniform();
    if(prob < rate) {       
      newList->push_back( list[i]->clone() );
      index.push_back(i);
    }
  } 
  __csvFlag = false;
  lsearch->search(*newList);  
  __csvFlag = true;
  for(unsigned int i = 0; i < newList->size(); i++) {
    *( list[ index[i] ] ) = *( newList->at(i) );
  }
  delete newList;
}

void edaAdaption::Serialize(edaBuffer &buf, bool pack) {
  if (pack)
  {
    // Pack the rate of Natural Selection
    buf.Pack(&rate, 1);
    lsearch->doSerialize(buf, pack);
  }
  else
  {
    buf.UnPack(&rate, 1);
    lsearch = (edaSearch*) classGenerateFromBuffer( buf );
  }
}

edaAdaption::~edaAdaption() {}

void edaAdaption::setRate(const double& _rate) {
  rate = _rate;
}

void edaAdaption::printOn(ostream& os) const {
  os << "Rate " << rate;
}

ostream& operator<< (ostream &os, const edaAdaption &adapt) {
  adapt.printOn(os);
  return os;
}
