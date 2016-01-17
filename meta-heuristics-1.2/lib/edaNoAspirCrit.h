#ifndef __edaNoAspirCrit_h__
#define __edaNoAspirCrit_h__

#include "edaAspirCrit.h"
/// Lớp edaImprBestFitAspirCrit không thực hiện việc thay đổi danh sách Tabu.
class edaNoAspirCrit : public edaAspirCrit
{
  public:
    /// Khởi tạo đối tượng
    edaNoAspirCrit();
    /// Nhân bản đối tượng
    /// \return Đối tượng được nhân bản
    edaNoAspirCrit(const edaNoAspirCrit &nac);
    /// Hủy đối tượng  
    ~edaNoAspirCrit();

    edaAspirCrit* clone() const;
    /// Khởi động đối tượng
    void init();
    bool check(const edaMove *_move, double fitness);

    void Serialize(edaBuffer &buf, bool pack);

    setClassID(_SYSCLASSID_ + _CLSID_EDANOASPIRCRIT_);

};

#endif
