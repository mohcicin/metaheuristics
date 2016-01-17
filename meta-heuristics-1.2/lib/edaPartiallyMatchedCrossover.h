/* 
 * File:   edaPartiallyMatchedCrossover.h
 * Author: tieuminh
 *
 * Created on April 20, 2012, 2:48 PM
 */

#ifndef __edaPartiallyMatchedCrossover_h__
#define	__edaPartiallyMatchedCrossover_h__

#include "edaCrossover.h"
#include <vector>
/// Lớp edaPartiallyMatchedCrossover hiện thực chiến lược lai chéo PMX giữa các nhiệm sắc thể.
class edaPartiallyMatchedCrossover : public edaCrossover {
public:
    /// Khởi tạo đối tượng
    /// \param rate Tỷ lệ lai chéo
    /// \param num Số điểm lai chéo
    edaPartiallyMatchedCrossover(double rate = 1.0, unsigned int num = 1);
    /// Khởi tạo đối tượng với đối tượng cần sao chép
    edaPartiallyMatchedCrossover(const edaPartiallyMatchedCrossover &cross);
    /// Hủy đối tượng
    virtual ~edaPartiallyMatchedCrossover();
    /// Thiết lập tỷ lệ lai chéo
    /// \param value Tỷ lệ lai chéo  
    void setRate(double value);
    /// Thiết lập số điểm lai chéo
    /// \param value Số điểm lai chéo
    void setNumPoint(unsigned int num);
    edaPartiallyMatchedCrossover *clone() const;
    void update(edaPopulation &pop);
    void Serialize(edaBuffer &buf, bool pack);
    void printOn(ostream& os) const;
    setClassID(_SYSCLASSID_ + _CLSID_EDAPARTIALLYMATCHEDCROSSOVER_);


private:
    unsigned int num;
    double rate;

};
#endif	/* EDAPARTIALLYMATCHEDCROSSOVER_H */

