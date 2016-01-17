#ifndef __edaHC_h__
#define __edaHC_h__

#include "edaSearch.h"
#include "edaHCMoveExpl.h"
#include "edaContinue.h"
#include "edaDefine.h"
/// Lớp edaHC thực hiện việc tối ưu theo giải thuật leo đồi.
class edaHC : public edaSearch
{
  public:
    /// Khởi tạo đối tượng
    edaHC();
    
    /// Khởi tạo đối tượng
    /// \param power Bậc tìm kiếm
    edaHC(int power);
    
    /// Khởi tạo đối tượng
    /// \param move Chiến lược bước chuyển trong không gian tìm kiếm
    /// \param moveNext Phương pháp tạo bước chuyển trong không gian tìm kiếm
    /// \param moveSelect Chiến lược chọn bước chuyển trong không gian tìm kiếm
    /// \param continueCrit Điều kiện dừng
    /// \param timeout Thời gian thực thi tìm kiếm
    /// \param power Bậc tìm kiếm 
    edaHC(edaMove *move,
        edaMoveGen *moveNext,
        edaMoveSelect *moveSelect,
        edaContinue *continueCrit,
        int timeout = 0,
        int power = 0);
    
    /// Khởi tạo đối tượng   
    /// \param move Chiến lược bước chuyển trong không gian tìm kiếm
    /// \param moveExpl Chiến lược khai phá không gian tìm kiếm    
    /// \param continueCrit Điều kiện dừng
    /// \param timeout Thời gian thực thi tìm kiếm
    /// \param power Bậc tìm kiếm 
    edaHC(edaMove *move,
        edaHCMoveExpl *moveExpl,
        edaContinue *continueCrit,
        int timeout = 0,
        int power = 0);
    
    /// Khởi tạo đối tượng   
    /// \param hc Đối tượng search cần sao chép
    edaHC(const edaHC &hc);
    
    edaHC *clone() const;
    
    /// Hủy đối tượng
    ~edaHC();
    
    bool search(edaSolutionList &list);
    void Serialize(edaBuffer &buf, bool pack);

    setClassID( _SYSCLASSID_ + _CLSID_EDAHC_ );


private:
    
    edaMove *move;
    edaHCMoveExpl *moveExpl;
    edaContinue *con;
};

#endif
