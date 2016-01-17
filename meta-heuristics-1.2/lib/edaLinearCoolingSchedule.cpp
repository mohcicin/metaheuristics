#include "edaLinearCoolingSchedule.h"

edaLinearCoolingSchedule::edaLinearCoolingSchedule(double _threshold, double _quantity) 
  : threshold (_threshold), quantity (_quantity)
{

}

edaCoolingSchedule *edaLinearCoolingSchedule::clone() const
{
  return new edaLinearCoolingSchedule(threshold,quantity);
}

bool edaLinearCoolingSchedule::check(double &temperature)
{
  return (temperature -= quantity) > threshold;
}

void edaLinearCoolingSchedule::Serialize(edaBuffer &buf, bool pack)
{
  edaCoolingSchedule::Serialize(buf, pack);

  if (pack)
  {
    buf.Pack(&threshold, 1);
    buf.Pack(&quantity, 1);
  }
  else
  {
    buf.UnPack(&threshold, 1);
    buf.UnPack(&quantity, 1);
  }
}

void edaLinearCoolingSchedule::printOn(std::ostream& os) const {
  os << "threshold " << threshold << ", quantity " << quantity;
}
