#ifndef __edaImprBestFitAspirCrit_h__
#define __edaImprBestFitAspirCrit_h__

#include "edaAspirCrit.h"
/// Lớp edaImprBestFitAspirCrit thực hiện việc lấy bước chuyển ứng viên có hàm lượng giá tốt nhất.
class edaImprBestFitAspirCrit : public edaAspirCrit
{
  public:
    /// Khởi tạo đối tượng
    edaImprBestFitAspirCrit();
    /// Khởi tạo đối tượng
    /// \param ac Đối tượng cần sao chép
    edaImprBestFitAspirCrit(const edaImprBestFitAspirCrit &ac);
    /// Hủy đối tượng  
    ~edaImprBestFitAspirCrit();

    edaAspirCrit* clone() const;
    /// Khởi động đối tượng
    void init();
    bool check(const edaMove *_move, double fitness);

    void Serialize(edaBuffer &buf, bool pack);

    setClassID(_SYSCLASSID_ + _CLSID_EDAIMPRBESTFITASPIRCRIT_);

  private:
    double bestFit;
    bool firstTime;
};

#endif
