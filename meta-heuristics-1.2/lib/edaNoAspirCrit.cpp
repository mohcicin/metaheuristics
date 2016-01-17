#include "edaNoAspirCrit.h"

edaNoAspirCrit::edaNoAspirCrit()
{
}

edaNoAspirCrit::edaNoAspirCrit(const edaNoAspirCrit &nac)
{
}

edaNoAspirCrit::~edaNoAspirCrit()
{
}

edaAspirCrit* edaNoAspirCrit::clone() const
{
  return new edaNoAspirCrit(*this);
}

void edaNoAspirCrit::init()
{
  // Do nothing
}

bool edaNoAspirCrit::check(const edaMove *_move, double fitness)
{
  // Check nothing
  return false;
}

void edaNoAspirCrit::Serialize(edaBuffer &buf, bool pack)
{
  // Pack/Unpack nothing
}
