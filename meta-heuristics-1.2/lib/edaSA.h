#ifndef __edaSA_h__
#define __edaSA_h__

#include "edaSearch.h"
#include "edaMove.h"
#include "edaMoveGen.h"
#include "edaContinue.h"
#include "edaCoolingSchedule.h"
#include "edaRNG.h"
/// Lớp edaSA thực hiện việc tối ưu theo giải thuật mô phỏng luyện kim.
class edaSA: public edaSearch
{
 public:  
  /// Khởi tạo đối tượng   
  edaSA();
  
  /// Khởi tạo đối tượng
  /// \param power Bậc tìm kiếm
  edaSA(int _power);
  
  /// Khởi tạo đối tượng
  /// \param move Chiến lược bước chuyển trong không gian tìm kiếm
  /// \param moveRandom Phương pháp tạo bước chuyển ngẫu nhiên trong không gian tìm kiếm
  /// \param continueCriteria Điều kiện dừng
  /// \param coolingSchedule Chiến luộc làm lạnh nhiệt độ
  /// \param initTemperature Nhiệt độ khởi động ban đầu
  /// \param timeout Thời gian thực thi tìm kiếm
  /// \param power Bậc tìm kiếm 
  edaSA( edaMove *move,
        edaMoveGen *moveRandom,
        edaContinue *continueCriteria,
        double initTemperature,
        edaCoolingSchedule *coolingSchedule,
        int timeout = 0,
        int power = 0 );
  /// Khởi tạo đối tượng
  /// \param sa Đối tượng search cần sao chép
  edaSA(const edaSA &sa);
  edaSA *clone() const;

  ~edaSA();

  bool search(edaSolutionList &list);
  virtual void Serialize(edaBuffer &buf, bool pack);
  setClassID( _SYSCLASSID_ + _CLSID_EDASA_ );

  
 private:
  edaMove *move;
  edaMoveGen *moveRandom;
  edaContinue *con;
  double initTemperature;
  edaCoolingSchedule *coolingSchedule;
};

#endif
