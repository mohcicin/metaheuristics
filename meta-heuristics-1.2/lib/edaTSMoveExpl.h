#ifndef __edaTSMoveExpl_h__
#define __edaTSMoveExpl_h__

#include "edaMoveExpl.h"
#include "edaMoveGen.h"
#include "edaTabuList.h"
#include "edaAspirCrit.h"
#include "edaDefine.h"
#include "edaBestImprSelect.h"
/// Lớp edaTSMoveExpl hiện thực chiến lược khai phá không gian ứng với giải thuật TS
class edaTSMoveExpl : public edaMoveExpl
{
  public:
    /// Khởi tạo đối tượng
    edaTSMoveExpl();
    /// Khởi tạo đối tượng
    /// \param moveNext Chiến lược tạo bước chuyển trong không gian tìm kiếm
    /// \param tabuList Danh sách Tabu 
    /// \param aspirCrit Chiến lược chọn bước chuyển trong không gian tìm kiếm
    edaTSMoveExpl(const edaMoveGen *moveNext,
		  const edaTabuList *tabuList,
		  const edaAspirCrit *aspirCrit);
    /// Khởi tạo đối tượng
    /// \param moveExpl Đối tượng cần sao chép
    edaTSMoveExpl(const edaTSMoveExpl &moveExpl);
    /// Hũy đối tượng
    virtual ~edaTSMoveExpl();

    virtual edaTSMoveExpl* clone() const;
    virtual void explore(const edaMove *move,
			 edaSolution &oldSolution,
			 edaSolution &newSolution);

    virtual void Serialize(edaBuffer &buf, bool pack);

    setClassID(_SYSCLASSID_ + _CLSID_EDATSMOVEEXPL_);


  protected:
    void clean();

    edaMoveGen *moveNext;
    edaTabuList *tabuList;
    edaAspirCrit *aspirCrit;
    edaBestImprSelect *moveSelect;
};

#endif
