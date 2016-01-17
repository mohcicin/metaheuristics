#include "edaImprBestFitAspirCrit.h"

edaImprBestFitAspirCrit::edaImprBestFitAspirCrit()
{
  firstTime = true;
}

edaImprBestFitAspirCrit::edaImprBestFitAspirCrit(const edaImprBestFitAspirCrit &ac)
{
  firstTime = ac.firstTime;
  bestFit = ac.bestFit;
}

edaImprBestFitAspirCrit::~edaImprBestFitAspirCrit()
{
}

edaAspirCrit* edaImprBestFitAspirCrit::clone() const
{
  return new edaImprBestFitAspirCrit(*this);
}

void edaImprBestFitAspirCrit::init()
{
  firstTime = true;
}

bool edaImprBestFitAspirCrit::check(const edaMove *_move, double fitness)
{
  if (firstTime)
  {
    bestFit = fitness;
    firstTime = false;

    return true;
  }
  
  if (fitness < bestFit)
  {
    return false;
  }

  bestFit = fitness;
  return true;
}

void edaImprBestFitAspirCrit::Serialize(edaBuffer &buf, bool pack)
{
  if (pack)
  {
    buf.Pack(&bestFit, 1);
    buf.Pack(&firstTime, 1);
  }
  else
  {
    buf.UnPack(&bestFit, 1);
    buf.UnPack(&firstTime, 1);
  }
}
