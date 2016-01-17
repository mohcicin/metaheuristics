#include "edaCoolingSchedule.h"
void edaCoolingSchedule::printOn(std::ostream& os) const {
  os << "edaCoolingSchedule must be overridden !!!" << std::endl;
}
std::ostream& operator<< (std::ostream &os, const edaCoolingSchedule &cool) {
  cool.printOn(os);
  return os;
}
