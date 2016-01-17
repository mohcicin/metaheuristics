#include "edaFitContinue.h"

edaFitContinue::edaFitContinue() {}

edaFitContinue::~edaFitContinue() {}


edaFitContinue::edaFitContinue(double _fitness) 
  : fitness (_fitness)
{
}

edaContinue *edaFitContinue::clone() const
{
  return new edaFitContinue(fitness);
}

void edaFitContinue::init() {
  edaContinue::init();
}

bool edaFitContinue::check(const edaSolutionList &list)
{
  edaContinue::check(list);
//  double best = -1e10;
//  list.evaluate()
//  for(unsigned int i = 0; i <list.size(); i++) {
//    double value = list[i]->evaluate();
//    best = value > best ? value : best;
//    if( best > fitness )
//      return false;
//  }
  return list.evaluate() < fitness;
}

void edaFitContinue::Serialize(edaBuffer &buf, bool pack)
{
  edaContinue::Serialize(buf, pack);
  if (pack)
  {
    buf.Pack(&fitness, 1);
  }
  else
  {
    buf.UnPack(&fitness, 1);
  }
}
