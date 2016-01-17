#include "edaFirstImprSelect.h"

edaFirstImprSelect::edaFirstImprSelect(const double epsilon)
  : edaMoveSelect(epsilon) {
  firstMove = NULL;
}

edaFirstImprSelect::~edaFirstImprSelect()
{
  if (firstMove != NULL)
  {
    delete firstMove;
  }
}

edaMoveSelect *edaFirstImprSelect::clone() const
{
  return new edaFirstImprSelect(epsilon);
}

void edaFirstImprSelect::init(double fitness)
{
  oldFitness = firstFitness = fitness;
}

bool edaFirstImprSelect::update(const edaMove *move, double fitness)
{
  double increase = fitness - oldFitness;
//  printDebug(5, "  + " << move->getClassName() << " " << *move 
//    << ", increase " << increase );
  if ( increase > epsilon )
  {
      firstFitness = fitness;
      if (firstMove != NULL)
      {
          delete firstMove;
      }
      firstMove = move->clone();
      return false;
  }
  return true;
}

bool edaFirstImprSelect::save(edaMove *move, double &fitness) const
{
  if (firstFitness - oldFitness > epsilon)
  {
    *move = *firstMove;
    fitness = firstFitness;
    return true;
  }
  return false;
}

void edaFirstImprSelect::Serialize(edaBuffer &buf, bool pack)
{
  if (pack)
  {
//    firstMove->doSerialize(buf, pack);
    buf.Pack(&firstFitness, 1);
    buf.Pack(&oldFitness, 1);
  }
  else
  {
//    firstMove = (edaMove *)classGenerateFromBuffer( buf );
    buf.UnPack(&firstFitness, 1);
    buf.UnPack(&oldFitness, 1);
  }
}
