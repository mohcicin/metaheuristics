#ifndef __edaSearch_h__
#define __edaSearch_h__

#include "edaSolution.h"
#include "edaSerialize.h"
#include "edaSolutionList.h"

/// Lớp trừu tượng edaSearch thực hiện việc tối ưu với các chiến lược hổ trợ trong thư viện hoặc do người dùng xây dựng.
class edaSearch : public edaSerialize
{
 public:
  /// Khởi tạo đối tượng
  edaSearch();
  /// Khởi tạo đối tượng
  /// \param power Bậc tìm kiếm
  /// \param protocol Giao thức
  edaSearch(int power, const char *protocol="http");
  /// Khởi tạo đối tượng
  /// \param timeout Thời gian  thoát
  /// \param power Bậc tìm kiếm
  edaSearch(int timeout, int power);
  /// Khởi tạo đối tượng
  /// \param search Đối tượng search cần sao chép
  edaSearch(const edaSearch &search);
  /// Nhân bản đối tượng
  /// \return Đối tượng được nhân bản  
  virtual edaSearch* clone() const = 0;
  /// Hủy đối tượng
  virtual ~edaSearch();
  /// Thực thi tối ưu
  /// \param list Danh sách lời giải cần tối ưu
  /// \return TRUE: tối ưu thành công, FALSE: tối ưu thất bại
  virtual bool search(edaSolutionList &list) = 0;
  
  virtual void Serialize(edaBuffer &buf, bool pack);


public:
  //Properties
  int Timeout;
  int StartTime;
  double Epsilon;
  int Power;
  char Protocol[1024];
  int TaskID;
  int ProcID;
};

#endif
