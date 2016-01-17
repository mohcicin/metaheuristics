#ifndef __edaMoveGen_h__
#define __edaMoveGen_h__

#include "edaMove.h"
#include "edaSerialize.h"

#include "edaDefine.h"
/// Lớp trừu tượng edaMoveGen mô tả các thông tin về thức tạo các bước chuyển trong không gian tìm kiếm của các giải thuật.
class edaMoveGen : public edaSerialize
{
 public:
  /// Khởi tạo đối tượng
  edaMoveGen() {}
  /// Khởi tạo đối tượng với đối tượng cần sao chép
  edaMoveGen(const edaMoveGen &m) {}
  /// Hủy đối tượng
  virtual ~edaMoveGen() {}
  /// Nhân bản đối tượng
  virtual edaMoveGen *clone() const = 0;
  /// Cập nhật bước chuyển mới cho lời giải
  /// \param move Bước chuyển cần được cập nhật
  /// \param sol Lời giải cần xác lập bước chuyển
  virtual bool generate( edaMove *move, const edaSolution &sol ) = 0;

  setClassID(_SYSCLASSID_ + _CLSID_EDAMOVEGEN_);
};

#endif
