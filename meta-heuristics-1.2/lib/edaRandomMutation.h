/* 
 * File:   edaRandomMutation.h
 * Author: root
 *
 * Created on March 20, 2013, 6:36 PM
 */

#ifndef EDARANDOMMUTATION_H
#define	EDARANDOMMUTATION_H
#include "edaMutation.h"
/// Lớp edaRandomMutation hiện thực chiến lược đột biến phát sinh ngẫu nhiên
class edaRandomMutation: public edaMutation {
public:
    /// Khởi tạo đối tượng
    /// \param rate Tỷ lệ đột biến
    edaRandomMutation(double rare = 0.1);
    /// Khởi tạo đối tượng
    /// \param mute Đối tượng cần sao chép
    edaRandomMutation(const edaRandomMutation& mute);
    /// Hủy đối tượng
    virtual ~edaRandomMutation();
    virtual edaRandomMutation* clone() const;  
    /// Thiết lập tỷ lệ đột biến
    /// \param value Tỷ lệ đột biến
    virtual void setRate(double value);
    virtual void update(edaPopulation &pop) const;
    virtual void Serialize(edaBuffer &buf, bool pack);
    setClassID(_SYSCLASSID_ + _CLSID_EDARANDOMMUTATION_);
    
protected:
    double rate;
};

#endif	/* EDARANDOMMUTATION_H */

