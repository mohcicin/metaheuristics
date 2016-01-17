#ifndef __edaTabuList_h__
#define __edaTabuList_h__

#include "edaMove.h"
#include "edaSolution.h"
#include "edaSerialize.h"
#include "edaDefine.h"
/// Lớp trừu tượng edaTabuList hiện thực danh sách Tabu theo các đối tượng khác nhau
class edaTabuList : public edaSerialize
{
  public:
    /// Khởi tạo danh sách Tabu
    edaTabuList() {}
    /// Hũy danh sách Tabu
    virtual ~edaTabuList() {}
    /// Nhân bản đối tượng
    virtual edaTabuList* clone() const = 0;
    /*
     * Procedure to add a move into the tabu list.
     *
     * \param _move a new tabu move.
     * \param _sol the original solution associated to this move.
     */
    
    /// Đưa bước chuyển vào danh sách Tabu
    /// \param move Bước chuyển
    /// \param sol lời giải hiện tại
    virtual void add(const edaMove* move, const edaSolution* sol) = 0;

    /*
     * Procedure to update tabu list content.
     */
    /// Cập nhật danh sách Tabu 
    virtual void update() = 0;

    /*
     * Procedure which initializes the tabu list.
     */
    /// Khởi động danh sách Tabu
    virtual void init() = 0;

    /*
     * Procedure to check that in current state, the _move is a tabu or not.
     *
     * \param _move A given move
     * \param _sol A solution
     * \return true or false
     */
    /// Kiểm tra bước chuyển có thuộc danh sách Tabu hay không
    /// \param move Bước chuyển
    /// \param Lời giải
    /// \return TRUE: nếu thuộc, FALSE: nếu không thuộc
    virtual bool check(const edaMove* move, const edaSolution * sol) = 0;

    setClassID(_SYSCLASSID_ + _CLSID_EDATABULIST_);

};

#endif
