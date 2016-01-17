#ifndef __edaSimpleMoveTabuList_h__
#define __edaSimpleMoveTabuList_h__

#include <list>

#include "edaTabuList.h"
/// Lớp trừu tượng edaTabuList hiện thực danh sách Tabu theo lớp edaSolution
class edaSimpleMoveTabuList : public edaTabuList
{
  public:
    /// Khởi tạo danh sách Tabu  
    edaSimpleMoveTabuList();
    /// Khởi tạo danh sách Tabu
    /// \param maxSize Số lượng phần tử tối đa trong danh sách
    edaSimpleMoveTabuList(unsigned int maxSize);
    /// Khởi tạo danh sách Tabu
    /// \param tl Đối tượng cần sao chép
    edaSimpleMoveTabuList(const edaSimpleMoveTabuList &tl);
    /// Hũy đối tượng
    ~edaSimpleMoveTabuList();
    edaTabuList* clone() const;
    void init();    
    void add(const edaMove *_move, const edaSolution *_sol);
    void update();
    bool check(const edaMove *_move, const edaSolution *_sol);
    void Serialize(edaBuffer &buf, bool pack);

    setClassID(_SYSCLASSID_ + _CLSID_EDASIMPLEMOVETABULIST_);


  private:
    void removeMove(const edaMove *_move);
    unsigned int maxSize;
    unsigned int currentSize;

    std::list<edaMove *> tabuList;
};

#endif
