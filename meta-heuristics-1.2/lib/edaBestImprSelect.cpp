#include "edaBestImprSelect.h"

edaBestImprSelect::edaBestImprSelect(const double epsilon)
  : edaMoveSelect(epsilon) {
  bestMove = NULL;
}

edaBestImprSelect::~edaBestImprSelect()
{
  if (bestMove != NULL)
  {
    delete bestMove;
  }
}

edaMoveSelect *edaBestImprSelect::clone() const
{
  return new edaBestImprSelect(epsilon);
}

void edaBestImprSelect::init(double fitness)
{
  bestFitness = oldFitness = fitness;  
}

bool edaBestImprSelect::update(const edaMove *move, double fitness)
{
//  double increase = fitness - oldFitness;
//  printDebug(5, "  + " << move->getClassName()  << " " << *move 
//    << ", increase " << increase );
  if (fitness - bestFitness > epsilon)
  {
    bestFitness = fitness;
    if (bestMove != NULL)
    {
      delete bestMove;
    }
    bestMove = move->clone();
  }

  return true;
}

bool edaBestImprSelect::save(edaMove *move, double &fitness) const
{
  if (bestFitness - oldFitness >  epsilon)
  {
    *move = *bestMove;
    fitness = bestFitness;
    return true;
  }
  return false;
}

void edaBestImprSelect::Serialize(edaBuffer &buf, bool pack)
{
  if (pack)
  {
//    bestMove->doSerialize(buf, pack);
    buf.Pack(&bestFitness, 1);
    buf.Pack(&oldFitness, 1);
  }
  else
  {
//    bestMove = (edaMove *)classGenerateFromBuffer( buf );
    buf.UnPack(&bestFitness, 1);
    buf.UnPack(&oldFitness, 1);
  }
}
