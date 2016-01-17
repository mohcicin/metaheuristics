#ifndef __edaSerialize_h__
#define __edaSerialize_h__

#include "edaBuffer.h"
#include "edaDefine.h"
/// Lớp edaSerialize hiện thực cơ chế gói và giải gói cho các đối tượng phức tạp
class edaSerialize
{
public:
  virtual ~edaSerialize() {}
  /// Hiện thực việc đóng gói cho đối tượng
  /// \param buf Bộ đệm có hổ trợ việc đóng gói và nhận các thông tin của đối tượng 
  /// \param pack Cờ hiệu: đóng gới (pack = 1), và giải gói (pack = 0))
  void doSerialize(edaBuffer &buf, bool pack = true);
  /// Phục hồi đối đã được đóng gói từ bộ đệm
  /// \param buf Bộ đệm
  void* createObject(edaBuffer &buf);
  /// Hiện thực việc đóng gói và mở gói các thông tin của đối tượng
  /// \param buf Bộ đệm có hổ trợ việc đóng gói và nhận các thông tin của đối tượng 
  /// \param pack Cờ hiệu: đóng gới (pack = 1), và giải gói (pack = 0))
  virtual void Serialize(edaBuffer &buf, bool pack);
  setClassID( _SYSCLASSID_ + _CLSID_INVALID_ );
};

edaSerialize *classGenerateFromBuffer( edaBuffer &buf );
edaSerialize *userClassGenerate(int clsid);

#endif
