#include <time.h>

#include "edaTimeContinue.h"

#ifdef _DEBUG_
#include <iostream>
using namespace std;
#endif

edaTimeContinue::edaTimeContinue()
  : maxTime (0), startTime (0), firstTime(true)
{
}

edaTimeContinue::edaTimeContinue(unsigned int _maxTime, unsigned int _startTime) 
  : maxTime (_maxTime), startTime (_startTime), firstTime(true)
{
}

edaContinue *edaTimeContinue::clone() const
{
  return new edaTimeContinue( maxTime, startTime );
}

void edaTimeContinue::init()
{
  edaContinue::init();
  if (firstTime)
  {
    startTime = time(NULL);
  }
}

bool edaTimeContinue::check(const edaSolutionList &list)
{
  edaContinue::check(list);
  return ((time(NULL) - startTime) < maxTime);
}

void edaTimeContinue::Serialize(edaBuffer &buf, bool pack)
{
  edaContinue::Serialize(buf, pack);
  if (pack)
  {
    buf.Pack(&maxTime, 1);
    buf.Pack(&startTime, 1);
  }
  else
  {
    buf.UnPack(&maxTime, 1);
    buf.UnPack(&startTime, 1);
  }
}
