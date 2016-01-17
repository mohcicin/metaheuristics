#ifndef __edaAspirCrit_h__
#define __edaAspirCrit_h__

#include "edaMove.h"
#include "edaSerialize.h"
#include "edaDefine.h"

/// Lớp trừu tượng edaAspirCrit thực hiện việc kiểm tra sự hợp lệ của các bước chuyển ứng viên.
class edaAspirCrit : public edaSerialize
{
  public:
    /// Khởi tạo đối tượng
    edaAspirCrit() {}
    
    /// Hủy đối tượng     
    ~edaAspirCrit() {}

    /// Nhân bản đối tượng
    /// \return Đối tượng được nhân bản
    virtual edaAspirCrit* clone() const = 0;

    /// Khởi động đối tượng
    virtual void init() = 0;

    /// Kiểm tra bước chuyển move trong giải thuật Tabu có được chấp nhận không
    /// \param move Bước trong cần kiểm tra
    /// \param fitness Lượng giá của bước chuyển
    virtual bool check(const edaMove* move, double fitness) = 0;
    
    /// Gán ID nhận dạng thuộc lớp edaAdaption cho đối tượng
    setClassID(_SYSCLASSID_ + _CLSID_EDAASPIRCRIT_);

};

#endif
