#include "vrpContinue.h"


vrpContinue::vrpContinue(unsigned int _maxNumGen, double PAR_0, double PAR_1) 
  : maxNumGen (_maxNumGen), numGen(0)
{
    _par_0 = PAR_0;
    _par_1 = PAR_1;
}

edaContinue *vrpContinue::clone() const
{
  return new vrpContinue( maxNumGen, _par_0,_par_1);
}

void vrpContinue::init()
{
    numGen = 0;
    _count = _numRepeat = 2;
    _prev = MIN_NUMBER;
}

bool vrpContinue::check(edaSolutionList &pop)
{
  if(++numGen > maxNumGen)
      return false;
  double max = MIN_NUMBER;
  double avg = pop.mean();
  _next = _par_0*max + _par_1*avg; 
  if(1.0 - _next/_prev > 0.001) {
      if(_count == 0)
        return false;
      else 
        _count--;
  }
  else {
      _count = _numRepeat;      
  }   
  _prev = _next;
  return true;
}

void vrpContinue::Serialize(edaBuffer &buf, bool pack)
{
  edaGenContinue::Serialize(buf, pack);
  if (pack)
  {
    buf.Pack(&maxNumGen, 1);
    buf.Pack(&numGen, 1);
    buf.Pack(&_prev, 1);
    buf.Pack(&_next, 1);
    buf.Pack(&_numRepeat, 1);
    buf.Pack(&_count, 1);
    buf.Pack(&_par_0, 1);
    buf.Pack(&_par_1, 1);
  }
  else
  {
    buf.UnPack(&maxNumGen, 1);
    buf.UnPack(&numGen, 1);
    buf.UnPack(&_prev, 1);
    buf.UnPack(&_next, 1);
    buf.UnPack(&_numRepeat, 1);
    buf.UnPack(&_count, 1);
    buf.UnPack(&_par_0, 1);
    buf.UnPack(&_par_1, 1);
  }
}
