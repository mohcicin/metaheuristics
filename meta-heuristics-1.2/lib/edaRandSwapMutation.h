/* 
 * File:   edaRandSwapMutation.h
 * Author: tieuminh
 *
 * Created on April 30, 2012, 2:14 PM
 */

#ifndef __edaRandSwapMutation_h__
#define	__edaRandSwapMutation_h__
#include "edaMutation.h"
/// Lớp edaRandSwapMutation hiện thực chiến lược đột biến hoán đổi gen
class edaRandSwapMutation: public edaMutation {
public:
    /// Khởi tạo đối tượng
    /// \param rate Tỷ lệ đột biến
    edaRandSwapMutation(double rate = 0.1);
    /// Khởi tạo đối tượng
    /// \param mute Đối tượng cần sao chép
    edaRandSwapMutation(const edaRandSwapMutation& mute);
    /// Hủy đối tượng
    ~edaRandSwapMutation();
    edaRandSwapMutation* clone() const;
    void printOn(ostream& os) const;
    void update(edaPopulation &pop) const;    
    
    void Serialize(edaBuffer &buf, bool pack);
    setClassID(_SYSCLASSID_ + _CLSID_EDARANDSWAPMUTATION_);

protected:
    void getRandPermutation(edaChromosome *chro) const;
    double rate;
};

#endif	/* EDARANDSWAPMUTATION_H */

