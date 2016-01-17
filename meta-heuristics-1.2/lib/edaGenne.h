/* 
 * File:   edaGenne.h
 * Author: tieuminh
 *
 * Created on April 27, 2012, 8:28 PM
 */

#ifndef __edaGenne_h__
#define	__edaGenne_h__

#include "edaSerialize.h"
using namespace std;
/// Lớp edaGenne là hiện thực đối tượng gen trong giải thuật tiến hóa.
class edaGenne: public edaSerialize {
public:
    /// Khởi tạo đối tượng
    edaGenne() {}
    /// Khởi tạo đối tượng
    /// \param value Giá trị dược gán vào gen
    edaGenne(double value) {}
    /// Khởi tạo đối tượng
    /// \param genne Đối tượng được sao chép
    edaGenne(const edaGenne& genne) {}
    /// Hủy đối tượng
    virtual ~edaGenne() {}
    /// Nhân bản đối tượng
    virtual edaGenne *clone() const = 0;
    /// Hoán đổi giá trị giữa 2 gen
    /// \param genne Gen dùng hoán đổi giá trị
    virtual void swap(edaGenne *genne) {}
    /// Thay đổi giá trị của gen
    /// \param rate Giá trị hoán đổi
    virtual void exchange(double rate) {}
    /// In thông tin (dạng chuổi) của đối tượng lên ostream
    virtual void printOn(ostream &os) const = 0;   
    virtual edaGenne& operator = (const edaGenne &genne) = 0;   
    virtual bool operator == (const edaGenne &genne) const = 0;   
    bool operator != (const edaGenne &genne) const;   
    virtual void Serialize( edaBuffer &buf, bool pack ) = 0; 

};
ostream& operator<< (ostream &os, const edaGenne &genne);
#endif	/* EDAGENNE_H */

