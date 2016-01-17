#ifndef __edaMoveExpl_h__
#define __edaMoveExpl_h__

#include "edaMove.h"
#include "edaSolution.h"
/// Lớp trừu tượng edaMoveExpl hiện thực chiến lược khai phá không gian ứng với từng giải thuật
class edaMoveExpl : public edaSerialize
{
  public:
    /// Hũy đối tượng
    virtual ~edaMoveExpl() {};
    /// Nhân bản đối tượng
    virtual edaMoveExpl* clone() const = 0;
    /// Khai phá không gian tìm kiếm
    /// \param move Chiến lược di chuyển trong không gian
    /// \param oldSolution Lời giải trước khi áp dụng
    /// \param newSolution Lời giải sau khi áp dụng
    virtual void explore(const edaMove *move, 
                        edaSolution &oldSolution, 
                        edaSolution &newSolution) = 0;
};

#endif
