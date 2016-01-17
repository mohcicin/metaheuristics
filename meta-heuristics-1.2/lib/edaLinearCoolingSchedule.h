#ifndef __edaLinearCoolingSchedule_h__
#define __edaLinearCoolingSchedule_h__

#include "edaCoolingSchedule.h"
#include "edaBuffer.h"
#include "edaDefine.h"
/// Lớp edaExpCoolingSchedule là hiện thực của chiến lược làm lạnh nhiệt độ theo hàm tuyến tính.
class edaLinearCoolingSchedule: public edaCoolingSchedule
{
  /**
   * Default constructor
   */
 public:
  /// Khỏi tạo đối tượng 
  edaLinearCoolingSchedule() {}
  
  /// Khỏi tạo đối tượng 
  /// \param threshold Ngưỡng nhiệt độ
  /// \param ratio Lượng giảm nhiệt độ (0 < ratio < 1)
  edaLinearCoolingSchedule(double _threshold, double _quantity);
  
  edaCoolingSchedule *clone() const;
  
  bool check(double &temperature);
  
  void printOn(std::ostream& os) const;
  
  virtual void Serialize(edaBuffer &buf, bool pack);

  setClassID(_SYSCLASSID_ + _CLSID_LINEAR_COOLING_SCHEDULE_);
  
 private:
  // Temperature threshold
  double threshold;
  // Quantity of temperature allows to decrease
  double quantity;
};

#endif
