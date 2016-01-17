#include "edaExpCoolingSchedule.h"

edaExpCoolingSchedule::edaExpCoolingSchedule(double _threshold, double _ratio) :
  threshold (_threshold), ratio (_ratio)
{
}

edaCoolingSchedule *edaExpCoolingSchedule::clone() const
{
  return new edaExpCoolingSchedule(threshold, ratio);
}

bool edaExpCoolingSchedule::check(double &temperature)
{
//  printDebug(6, "t: " << temperature << ", r: " << ratio << ", th: " << threshold);
  return (temperature *= ratio) > threshold;
}

void edaExpCoolingSchedule::Serialize(edaBuffer &buf, bool pack)
{
  edaCoolingSchedule::Serialize(buf, pack);

  if (pack)
  {
    buf.Pack(&threshold, 1);
    buf.Pack(&ratio, 1);
  }
  else
  {
    buf.UnPack(&threshold, 1);
    buf.UnPack(&ratio, 1);
  }
}
void edaExpCoolingSchedule::printOn(std::ostream& os) const {
  os << "threshold " << threshold << ", ratio " << ratio;
}
