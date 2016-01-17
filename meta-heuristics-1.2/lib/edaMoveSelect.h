#ifndef __edaMoveSelect_h__
#define __edaMoveSelect_h__

#include "edaSerialize.h"
#include "edaMove.h"
#include "edaDefine.h"

/*
   class edaEmptySelectionException : public edaException {
   };
*/

/// Lớp trừu tượng edaMoveSelect thực hiện việc chọn lựa các bước chuyển theo chiến lược tương ứng.
class edaMoveSelect : public edaSerialize
{
  public:
    /// Khởi tạo đối tượng
    edaMoveSelect(const double epsilon)
      : epsilon(epsilon) {};
      
    /// Hủy đối tượng  
    virtual ~edaMoveSelect() {};
   
    /// Nhân bản đối tượng
    virtual edaMoveSelect* clone() const = 0;
    
    /// Khởi động đối tượng
    virtual void init(double fitness) = 0;
    
    /// Thực hiện việc chọn lựa với bước chuyển theo chiến lược tương ứng
    /// \param move Bước chuyển ứng viên 
    /// \param fitness Lượng giá của bước chuyển
    virtual bool update(const edaMove *move, double fit) = 0;
    
    /// Lấy thông tin bước chuyển ứng với chiến lược tương ứng
    /// \param move Bước chuyển ứng với chiến lược đề ra
    /// \param fitness Lượng giá của bước chuyển
    virtual bool save(edaMove *move, double &fit) const = 0;
    
    virtual void Serialize(edaBuffer &buf, bool pack) = 0;
    
    setClassID(_SYSCLASSID_ + _CLSID_EDAMOVESELECT_);

  
  protected:
    double epsilon;
};

#endif
