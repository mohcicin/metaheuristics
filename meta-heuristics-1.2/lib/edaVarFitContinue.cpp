#include "edaVarFitContinue.h"

edaVarFitContinue::edaVarFitContinue(unsigned int _num_loop) {
    num_loop = _num_loop;
}

edaVarFitContinue::~edaVarFitContinue() {}

edaContinue *edaVarFitContinue::clone() const
{
  return new edaVarFitContinue(this->num_loop);
}

void edaVarFitContinue::init() {
  edaContinue::init();
  fitness = NAN;
  count = 0;
}

bool edaVarFitContinue::check(const edaSolutionList &list)
{
  edaContinue::check(list);
  double newFit = list.evaluate();
  if(fitness >= newFit) {
    count ++;
  }
  else {
    fitness = newFit;
    count = 0;
  }
  return count < num_loop;
}

void edaVarFitContinue::Serialize(edaBuffer &buf, bool pack)
{
  edaContinue::Serialize(buf, pack);
  if (pack)
  {
    buf.Pack(&fitness, 1);
    buf.Pack(&num_loop, 1);
    buf.Pack(&count, 1);
  }
  else
  {
    buf.UnPack(&fitness, 1);
    buf.UnPack(&num_loop, 1);   
    buf.UnPack(&count, 1); 
  }
}
