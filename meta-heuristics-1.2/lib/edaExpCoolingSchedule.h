#ifndef __edaExpCoolingSchedule_h__
#define __edaExpCoolingSchedule_h__

#include "edaCoolingSchedule.h"

/// Lớp edaExpCoolingSchedule là hiện thực của chiến lược làm lạnh nhiệt độ theo hàm mũ.
class edaExpCoolingSchedule: public edaCoolingSchedule
{
 public:
  /// Khỏi tạo đối tượng 
  edaExpCoolingSchedule() {};
  
  /// Khỏi tạo đối tượng 
  /// \param threshold Ngưỡng nhiệt độ
  /// \param ratio Tỷ lệ giảm nhiệt độ (0 < ratio < 1)
  edaExpCoolingSchedule(double threshold, double ratio);
  
  virtual edaCoolingSchedule *clone() const;
  
  bool check(double &temperature);
  
  virtual void Serialize(edaBuffer &buf, bool pack);

  setClassID(_SYSCLASSID_ + _CLSID_EXP_COOLING_SCHEDULE_);
  
  void printOn(std::ostream& os) const;
 private:
  // Temperature threshold
  double threshold;
  // The ratio of decrease
  double ratio;
};

#endif
