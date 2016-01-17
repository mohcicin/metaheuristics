/* 
 * File:   edaProblem.h
 * Author: tieuminh
 *
 * Created on May 16, 2012, 1:50 PM
 */

#ifndef __edaProblem_h__
#define	__edaProblem_h__

#include "edaSerialize.h"
using namespace std;
/// Lớp trừu tượng edaProblem chứa thông tin bài toán cho từng vấn đề tối ưu cụ thể.
class edaProblem: public edaSerialize {
public:
    /// Khởi tạo đối tượng
    edaProblem() {}
    /// Khởi tạo đối tượng
    /// \param filename Tên file chứa thông tin của bài toán tối ưu
    edaProblem(const char* filename) {}
    /// Khởi tạo đối tượng
    /// \param pro Đối tượng cần sao chép
    edaProblem(const edaProblem& pro) {}
    /// Hũy đối tượng
    virtual ~edaProblem() {}
    /// Nhân bản đối tượng
    virtual edaProblem *clone() const = 0;  
    virtual edaProblem& operator = (const edaProblem &pro) = 0;
    virtual void printOn(ostream &os) const;  
    void Serialize(edaBuffer &buf, bool pack) = 0; 
};
ostream& operator<< (ostream &os, const edaProblem &problem);

#endif	/* EDAPROBLEM_H */

