#ifndef __edaHCMoveExpl_h__
#define __edaHCMoveExpl_h__

#include "edaMoveExpl.h"
#include "edaMoveGen.h"
#include "edaMoveSelect.h"
#include "edaDefine.h"
/// Lớp edaHCMoveExpl hiện thực chiến lược khai phá không gian ứng với giải thuật HC
class edaHCMoveExpl : public edaMoveExpl
{
  public:
    /// Khởi tạo đối tượng
    edaHCMoveExpl() {}
    /// Khởi tạo đối tượng
    /// \param moveNext Chiến lược tạo bước chuyển trong không gian tìm kiếm
    /// \param moveSelect Chiến lược chọn bước chuyển trong không gian tìm kiếm
    edaHCMoveExpl(const edaMoveGen *moveNext, const edaMoveSelect *moveSelect);
    /// Khởi tạo đối tượng
    edaHCMoveExpl(const edaHCMoveExpl &_moveExpl);
    /// Hũy đối tượng
    ~edaHCMoveExpl();

    edaHCMoveExpl* clone() const;
    void explore(const edaMove *move,
        edaSolution &oldSolution,
        edaSolution &newSolution);
    virtual void Serialize(edaBuffer &buf, bool pack);

    setClassID(_SYSCLASSID_ + _CLSID_EDAHCMOVEEXPL_);

  private:
    edaMoveGen *moveNext;
    edaMoveSelect *moveSelect;
};

#endif
