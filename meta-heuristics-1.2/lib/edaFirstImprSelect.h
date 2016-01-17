#ifndef __edaFirstImprSelect_h__
#define __edaFirstImprSelect_h__

#include "edaMoveSelect.h"
#include "edaDefine.h"

/// Lớp edaBestImprSelect thực hiện việc chọn lựa các bước chuyển theo chiến lược First Best.
class edaFirstImprSelect : public edaMoveSelect
{
  public:
    edaFirstImprSelect(const double epsilon = 1e-4);
    ~edaFirstImprSelect();

    edaMoveSelect *clone() const;
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

    

    setClassID(_SYSCLASSID_ + _CLSID_EDAFIRSTIMPRSELECT_ );

    /*
     * Is the first time generate the move?
     */
  private:
    edaMove *firstMove;
    double firstFitness;
    double oldFitness;
};

#endif
