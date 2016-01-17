/* 
 * File:   edaSimpleCrossOver.h
 * Author: root
 *
 * Created on March 20, 2013, 12:40 PM
 */

#ifndef EDAONEPOINTCROSSOVER_H
#define	EDAONEPOINTCROSSOVER_H
/// Lớp edaOnePointCrossover hiện thực chiến lược lai chéo giữa các nhiệm sắc thể với một diểm lai chéo với các mode lai khác nhau.
#include "edaCrossover.h"
class edaOnePointCrossover: public edaCrossover {
public:
    /// Các mode lai chéo một điểm được hổ trợ
    /// \param MEDIAN Điểm lai chéo tại trung vị của chuổi gen
    /// \param RANDOM Điểm lai chéo được chọn ngẫu nhiên
    enum CrossPointMode { MEDIAN, RANDOM };
    /// Khởi tạo đối tượng
    /// \param rate Tỷ lệ lai chéo
    edaOnePointCrossover(double rate = 1.0);
    /// Khởi tạo đối tượng với đối tượng cần sao chép
    edaOnePointCrossover(const edaOnePointCrossover& cross);
    /// Hủy đối tượng
    virtual ~edaOnePointCrossover();
    edaOnePointCrossover *clone() const;   
    /// Thiết lập tỷ lệ lai chéo
    /// \param value Tỷ lệ lai chéo  
    void setRate(double value);
    /// Thiết lập mode lai chéo
    /// \param mode Mode lai chéo (mặc định là ngẫu nhiên) 
    void setMode(CrossPointMode mode = RANDOM);
    void update(edaPopulation &pop);
    void Serialize(edaBuffer &buf, bool pack);
    setClassID(_SYSCLASSID_ + _CLSID_EDAONEPOINTCROSSOVER_);
protected:
    double rate;
    unsigned int mode;
};

#endif	/* EDAONEPOINTCROSSOVER_H */

