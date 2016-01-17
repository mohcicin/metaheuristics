#ifndef __edaTimeContinue_h__
#define __edaTimeContinue_h__

#include "edaContinue.h"
#include "edaDefine.h"

/// Lớp edaTimeContinue hiện thực điều kiện dừng theo theo thời gian chạy.
class edaTimeContinue : public edaContinue
{
 public:
  /// Khởi tạo đối tượng
  edaTimeContinue();
  /// Khởi tạo đối tượng
  /// \param maxTime Thời gian giới hạn cho việc lặp
  /// \param startTime Thời gian bắt đầu (mặc định startTime = 0)
  edaTimeContinue(unsigned int maxTime, unsigned int startTime = 0);
  /// Hủy đối tượng  
  virtual ~edaTimeContinue() {};
  virtual edaContinue *clone() const;
  void init();
  bool check(const edaSolutionList &list);
  virtual void Serialize(edaBuffer &buf, bool pack);
    
  setClassID(_SYSCLASSID_ + _CLSID_TIME_CONTINUE_);

 private:
  unsigned int maxTime;
  unsigned int startTime;
  bool firstTime;

};

#endif
