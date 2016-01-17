#ifndef __edaBestImprSelect_h__
#define __edaBestImprSelect_h__

#include "edaMoveSelect.h"
#include "edaDefine.h"

/// Lớp edaBestImprSelect thực hiện việc chọn lựa các bước chuyển theo chiến lược Global Best.
class edaBestImprSelect : public edaMoveSelect
{
  public:

    /// Khởi tạo đối tượng
    edaBestImprSelect(const double epsilon = 1e-4);
    
    /// Hủy đối tượng  
    ~edaBestImprSelect();

    /// Nhân bản đối tượng
    edaMoveSelect *clone() const;
    
    /// Khởi động đối tượng
    void init(double fitness);
    
    bool update(const edaMove *move, double fitness);
    
    /*
     * Save the best move and fitness
     * 
     * \param[in, out] move The current move, updated with new move.
     * \param[in, out] fitness The current fitness, updated with new fitness.
     * \throws edaEmptySelectionException When no improvement.
     */
    
    bool save(edaMove *move, double &fitness) const;
    
    void Serialize(edaBuffer &buf, bool pack);    
    
    /// Gán ID nhận dạng thuộc lớp edaAdaption cho đối tượng
    setClassID(_SYSCLASSID_ + _CLSID_EDABESTIMPRSELECT_);
  
    /*
     * Is the first time generate the move?
     */
  private:
    edaMove *bestMove;
    double bestFitness;
    double oldFitness;
};

#endif
