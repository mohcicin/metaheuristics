#ifndef __edaCoolingSchedule_h__
#define __edaCoolingSchedule_h__

#include "edaSerialize.h"
/// Lớp trừu tượng edaCoolingSchedule mô tả các thông tin về chiến lược làm lạnh nhiệt độ.
class edaCoolingSchedule : public edaSerialize
{
 public:
  /// Nhân bản đối tượng
  virtual edaCoolingSchedule *clone() const = 0;
  
  /// Kiểm tra nhiệt độ hiện tại với ngưỡng nhiệt độ
  /// \param temperature Nhiệt độ hiện tại
  virtual bool check(double &temperature) = 0;
  
  virtual void Serialize(edaBuffer &buf, bool &pack) {}
  
  /// In thông tin (dạng chuổi) của đối tượng lên ostream
  virtual void printOn(std::ostream& os) const;

};
std::ostream& operator<< (std::ostream &os, const edaCoolingSchedule &cool);
#endif
