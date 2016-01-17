#ifndef __edaMove_h__
#define __edaMove_h__

#include "edaSolution.h"
#include "edaDefine.h"
/// Lớp trừu tượng edaMove mô tả các thông tin về chiến lược duy chuyển trong không gian tìm kiếm của các giải thuật.
class edaMove: public edaSerialize
{
 public:
  /// Khởi tạo đối tượng
  edaMove() {}
  /// Khởi tạo đối tượng với đối tượng cần sao chép
  edaMove(const edaMove &move) {}
  /// Hủy đối tượng
  virtual ~edaMove() {}
  /// Nhân bản đối tượng
  virtual edaMove* clone() const = 0;
  /// Khởi dộng đối tượng
  virtual void init(const edaSolution &sol) = 0;
  /// Đánh giá sự thay đổi của hàm lượng giá so với lời giải cũ
  /// \param sol Lời giải chưa được cập nhật
  virtual double incrEval(const edaSolution &sol) const = 0;
  /// Cập nhật lời giải với bước chuyển đang có của đối tượng
  /// \param sol Lời giải hiện tại
  virtual void update( edaSolution &sol ) const = 0;
  virtual edaMove& operator = (const edaMove& _move) = 0;
  virtual void Serialize( edaBuffer &buf, bool pack ) = 0;
  virtual bool operator == (const edaMove &_move) const = 0;
  virtual void printOn( ostream &os ) const;

};

ostream& operator<< (ostream &os, const edaMove &sol);
#endif
