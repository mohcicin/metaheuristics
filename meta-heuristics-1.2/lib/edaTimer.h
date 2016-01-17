#ifndef _EDATIMER_H_
#define _EDATIMER_H_
#include <sys/time.h>
/// Lớp edaTimer hiện thực việc hổ trợ tính toán thời gian trong thư viện
class edaTimer {
 public:
  /// Khởi tạo đối tượng     
  edaTimer();
  /// Bắt đầu do thời gian chạy
  /// \param reset Có start lại từ đầu thời điểm 
  void start( bool reset = false );
  /// Dừng tính toán thời gian
  /// \return Trả lại thời điểm cuối cùng khi bắt đầu dừng
  double stop();
  /// Start lại quá trình tính toán thời gian
  /// \return Trả lại thời điểm cuối cùng khi bắt đầu restart lại
  double restart();
  /// Lấy thời điểm hiện tại
  /// \return Thời gian hiện tại
  double elapse() const;
  /// Lấy thời khoảng hiện tại
  /// \return Thời khoảng hiện tại
  double duration() const;
  
 private:
  struct timeval d_from, d_to;
  double d_acc;
};
std::ostream & operator << ( std::ostream &os, const edaTimer &t );
#endif
