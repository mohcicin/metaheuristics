/* 
 * File:   edaSelection.h
 * Author: tieuminh
 *
 * Created on April 5, 2012, 11:05 AM
 */

#ifndef __edaNaturalSelection_h__
#define	__edaNaturalSelection_h__

#include "edaPopulation.h"
/// Lớp trừ tượng edaNaturalSelection hiện thực các chiến lược chọn lọc tự nhiên
class edaNaturalSelection: public edaSerialize {
public:
    /// Khởi tạo đối tượng
    edaNaturalSelection() {}
    /// Khởi tạo đối tượng với dối tượng cần sao chép
    /// \param Đối tượng cần sao chép
    edaNaturalSelection(const edaNaturalSelection& slect) {}
    /// Hủy đối tượng
    virtual ~edaNaturalSelection() {}
    /// Nhân bản đối tượng
    virtual edaNaturalSelection* clone() const = 0;    
    /// Cập nhật đối tượng với chiến lược chọn lọc tự nhiên
    /// \param pop Tập dân cư cần thực hiện chọn lọc
    virtual void update(edaPopulation &pop) = 0;      
    virtual void Serialize(edaBuffer &buf, bool pack) = 0;
    /// \Xóa thông tin chứa trong đối tượng
    virtual void easer() = 0;
    /// In thông tin (dạng chuổi) của đối tượng lên ostream
    virtual void printOn(ostream &os) const;
};
ostream& operator<< (ostream &os, const edaNaturalSelection &nslect);
#endif

