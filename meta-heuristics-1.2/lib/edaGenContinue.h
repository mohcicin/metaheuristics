#ifndef __edaGenContinue_h__
#define __edaGenContinue_h__

#include "edaContinue.h"
#include "edaDefine.h"

/// Lớp edaGenContinue hiện thực điều kiện dừng theo theo số lần lặp.
class edaGenContinue : public edaContinue
{
 public:
  /// Khởi tạo đối tượng
  edaGenContinue();
  /// Khởi tạo đối tượng
  /// \param maxNumGen Số lần (thế hệ) lặp tối đa
  edaGenContinue(unsigned int maxNumGen);
  /// Hủy đối tượng  
  virtual ~edaGenContinue() {};
  virtual edaContinue *clone() const;
  void init();
  bool check(const edaSolutionList &list);
  virtual void Serialize(edaBuffer &buf, bool pack);
    
  setClassID(_SYSCLASSID_ + _CLSID_GEN_CONTINUE_);

 private:
  unsigned int maxNumGen;
  unsigned int numGen;

};

#endif
