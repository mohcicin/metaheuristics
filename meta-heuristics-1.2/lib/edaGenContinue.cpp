#include "edaGenContinue.h"

edaGenContinue::edaGenContinue() {
  maxNumGen = UINT_MAX;
  numGen = 0;
}

edaGenContinue::edaGenContinue(unsigned int _maxNumGen) 
  : maxNumGen (_maxNumGen), numGen(0)
{
}

edaContinue *edaGenContinue::clone() const
{
  return new edaGenContinue( maxNumGen );
}

void edaGenContinue::init()
{
  edaContinue::init();
  numGen = 0;
}

bool edaGenContinue::check(const edaSolutionList &list) {
  edaContinue::check(list);
  return (++numGen < maxNumGen);
}

void edaGenContinue::Serialize(edaBuffer &buf, bool pack)
{
  edaContinue::Serialize(buf, pack);
  if (pack)
  {
    buf.Pack(&maxNumGen, 1);
    buf.Pack(&numGen, 1);
  }
  else
  {
    buf.UnPack(&maxNumGen, 1);
    buf.UnPack(&numGen, 1);
  }
}
