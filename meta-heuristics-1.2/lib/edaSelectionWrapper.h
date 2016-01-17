/* 
 * File:   edaSelectionWrapper.h
 * Author: Tieu Minh
 *
 * Created on August 17, 2013, 9:07 AM
 */

#ifndef EDASELECTIONWRAPPER_H
#define	EDASELECTIONWRAPPER_H
#include "edaSolutionList.h"

/// Lớp trừu tượng edaSelectionWrapper thực hiện việc chọn lời giải với các chiến lược hổ trợ trong thư viện hoặc do người dùng xây dựng.
class edaSelectionWrapper {
public:
    /// Khởi tạo đối tượng
    edaSelectionWrapper() {}
    /// Khởi tạo đối tượng
    /// \param slect Đối tượng cần sao chép
    edaSelectionWrapper(const edaSelectionWrapper &slect) {}
    /// Hủy đối tượng
    virtual ~edaSelectionWrapper() {}
    /// Nhân bản đối tượng
    /// \return Đối tượng được nhân bản
    virtual edaSelectionWrapper * clone() const = 0;
    /// Chọn lựa các lời giải với chiến lược chọn tương ứng trong tập lời giải
    /// \return Nhận giá trị TRUE nếu chọn lựa thành công, 
    /// ngược lại giá trị đầu ra là FALSE
    virtual bool select(edaSolutionList &list) const = 0;
private:

};

#endif	/* EDASELECTIONWRAPPER_H */

