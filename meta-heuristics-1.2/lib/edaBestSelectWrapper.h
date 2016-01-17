/* 
 * File:   edaBestSelectWrapper.h
 * Author: Tieu Minh
 *
 * Created on August 22, 2013, 8:14 AM
 */

#ifndef EDABESTSELECTWRAPPER_H
#define	EDABESTSELECTWRAPPER_H

#include "edaSelectionWrapper.h"
#include "edaSolutionList.h"

/// Lớp edaBestSelectWrapper thực hiện việc chọn lời giải có hàm lượng giá tốt nhất trong tập lời giải được đưa vào tại mỗi nút tìm kiếm.
class edaBestSelectWrapper : public edaSelectionWrapper {
public:
    /// Khởi tạo đối tượng
    edaBestSelectWrapper();     

    edaBestSelectWrapper * clone() const;    

    bool select(edaSolutionList &list) const;
  
private:

};

#endif	/* EDABESTSELECTWRAPPER_H */

