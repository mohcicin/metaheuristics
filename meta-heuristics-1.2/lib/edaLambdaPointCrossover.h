/* 
 * File:   edaSimpleCrossOver.h
 * Author: root
 *
 * Created on March 20, 2013, 12:40 PM
 */

#ifndef EDALAMBDAPOINTCROSSOVER_H
#define	EDALAMBDAPOINTCROSSOVER_H
/// Lớp edaLambdaPointCrossover hiện thực chiến lược lai chéo giữa các nhiệm sắc thể với số diểm lai chéo là tùy chọn.
#include "edaCrossover.h"
class edaLambdaPointCrossover: public edaCrossover {
public:
    /// Khởi tạo đối tượng
    /// \param rate Tỷ lệ lai chéo
    /// \param num Số điểm lai chéo (num < nữa số lượng gen trong nhiễm sắc thể)
    edaLambdaPointCrossover(double rate = 1.0, unsigned int num = 1);
    /// Khởi tạo đối tượng với đối tượng cần sao chép
    edaLambdaPointCrossover(const edaLambdaPointCrossover& cross);
    /// Hủy đối tượng
    virtual ~edaLambdaPointCrossover();
    edaLambdaPointCrossover *clone() const;
    /// Thiết lập tỷ lệ lai chéo
    /// \param value Tỷ lệ lai chéo    
    void setRate(double value);
    /// Thiết lập số điểm lai chéo
    /// \param value Số điểm lai chéo
    void setNumPoint(unsigned int num);
    
    void update(edaPopulation &pop);
    void Serialize(edaBuffer &buf, bool pack);
    setClassID(_SYSCLASSID_ + _CLSID_EDALAMBDAPOINTCROSSOVER_);
protected:
    double rate;
    unsigned int num;
};

#endif	/* EDALAMBDAPOINTCROSSOVER_H */

