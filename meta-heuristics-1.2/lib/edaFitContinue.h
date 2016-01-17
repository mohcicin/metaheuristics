#ifndef __edaFitContinue_h__
#define __edaFitContinue_h__

#include "edaContinue.h"

/// Lớp edaFitContinue hiện thực điều kiện dừng theo hàm lượng giá.
class edaFitContinue : public edaContinue
{
 public:
  /// Khởi tạo đối tượng
  edaFitContinue();
  /// Khởi tạo đối tượng với giá trị fitness
  edaFitContinue(double fitness);
  /// Hủy đối tượng  
  ~edaFitContinue();
  virtual edaContinue *clone() const;
  void init();
  bool check(const edaSolutionList &list);
  virtual void Serialize(edaBuffer &buf, bool pack);
  
  setClassID(_SYSCLASSID_ + _CLSID_FIT_CONTINUE_);
  
 private:
  double fitness;
};

#endif
