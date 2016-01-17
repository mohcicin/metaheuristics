#ifndef __edaVarFitContinue_h__
#define __edaVarFitContinue_h__

#include "edaContinue.h"

/// Lớp edaVarFitContinue hiện thực điều kiện dừng theo theo hàm lượng giá có khả năng thay đổi
class edaVarFitContinue : public edaContinue
{
 public:
     
  /// Khởi tạo đối tượng
  edaVarFitContinue(unsigned int num_loop = 1);
  /// Hủy đối tượng  
  ~edaVarFitContinue();
  virtual edaContinue *clone() const;
  void init();
  bool check(const edaSolutionList &list);
  virtual void Serialize(edaBuffer &buf, bool pack);
  
  setClassID(_SYSCLASSID_ + _CLSID_VAR_FIT_CONTINUE_);
  
 private:
  double fitness;
  unsigned int count;
  unsigned int num_loop;
};

#endif
