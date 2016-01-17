#ifndef __edaNS_h__
#define __edaNS_h__
#include "edaSearch.h"
#include "edaDefine.h"
/// Lớp edaNS là một chiến lược tối ưu rỗng (không thực hiện quá trình tối ưu).
class edaNS : public edaSearch
{
  public:
    /// Khởi tạo đối tượng
    edaNS(int _power);
    /// Khởi tạo đối tượng
    /// \param timeout Thời gian thực thi tìm kiếm
    /// \param power Bậc tìm kiếm
    edaNS(int timeout = 0, int power = 0);
    /// Khởi tạo đối tượng
    /// \param ns Đối tượng search cần sao chép
    edaNS(const edaNS &ns);
    edaNS *clone() const;
    /// Hủy đối tượng
    virtual ~edaNS();
    bool search(edaSolutionList &list);
    void Serialize(edaBuffer &buf, bool pack);

    setClassID( _SYSCLASSID_ + _CLSID_EDANS_ ); 
};

#endif
