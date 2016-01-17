#ifndef __edaSimpleSolutionTabuList_h__
#define __edaSimpleSolutionTabuList_h__

#include <list>

#include "edaTabuList.h"
/// Lớp trừu tượng edaTabuList hiện thực danh sách Tabu theo lớp edaMove
class edaSimpleSolutionTabuList : public edaTabuList
{
  public:
    /// Khởi tạo danh sách Tabu  
    edaSimpleSolutionTabuList();
    /// Khởi tạo danh sách Tabu
    /// \param maxSize Số lượng phần tử tối đa trong danh sách
    edaSimpleSolutionTabuList(unsigned int maxSize);
    /// Khởi tạo danh sách Tabu
    /// \param tl Đối tượng cần sao chép
    edaSimpleSolutionTabuList(const edaSimpleSolutionTabuList &tl);
    /// Hũy đối tượng
    virtual ~edaSimpleSolutionTabuList();
    edaTabuList* clone() const;
    void init();
    void add(const edaMove *_move, const edaSolution *_sol);
    void update();
    bool check(const edaMove *_move, const edaSolution *_sol);
    void Serialize(edaBuffer &buf, bool pack);

    setClassID(_SYSCLASSID_ + _CLSID_EDASIMPLESOLUTIONTABULIST_);

  private:
    void removeSolution(const edaSolution *_sol);
    unsigned int maxSize;
    unsigned int currentSize;

    std::list<edaSolution *> tabuList;
};

#endif
