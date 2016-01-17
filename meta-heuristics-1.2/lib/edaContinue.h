#ifndef __edaContinue_h__
#define __edaContinue_h__

#include "edaSolution.h"
#include "edaSerialize.h"
#include "edaSolutionList.h"

/// Lớp trừu tượng edaContinue mô tả các thông tin về điều kiện dừng trong thư viện.
class edaContinue : public edaSerialize
{
 public:
  /// Hủy đối tượng     
  virtual ~edaContinue() {};
  
  /// Nhân bản đối tượng
  virtual edaContinue *clone() const = 0;
  
  /// Khởi động đối tượng
  virtual void init() = 0;
  
  /// Kiểm tra điều kiện dừng
  /// \param list Danh sách các lời giải cần kiểm tra với điều kiện dừng
  virtual bool check(const edaSolutionList &list) = 0;
  
  /// Hiện thực việc đóng gói và mở gói các thông tin của đối tượng
  /// \param buf Bộ đệm có hổ trợ việc đóng gói và nhận các thông tin của đối tượng 
  /// \param pack Cờ hiệu: đóng gới (pack = 1), và giải gói (pack = 0))
  virtual void Serialize(edaBuffer &buf, bool pack);
  
  /// In thông tin (dạng chuổi) của đối tượng lên ostream
  virtual void printOn(ostream &os) const;
private:
   unsigned int loop;
};
ostream& operator<< (ostream &os, const edaContinue &con);
#endif
