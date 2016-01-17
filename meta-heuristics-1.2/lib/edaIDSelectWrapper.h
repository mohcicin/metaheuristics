/* 
 * File:   edaIDSelectWrapper.h
 * Author: Tieu Minh
 *
 * Created on August 22, 2013, 8:14 AM
 */

#ifndef edaIDSelectWrapper_H
#define	edaIDSelectWrapper_H

#include "edaSelectionWrapper.h"
#include "edaSolutionList.h"

/// Lớp edaIDSelectWrapper thực hiện việc chọn lời giải theo thứ tự của chúng trong sanh sách lời giải.
class edaIDSelectWrapper : public edaSelectionWrapper {
public:
  /// Khởi tạo đối tượng
  /// \param id Thứ tự của lời giải dược chọn trong danh sách lời giải (mặc định id = 0)
  edaIDSelectWrapper(unsigned int id = 0); 
  edaIDSelectWrapper * clone() const;
  bool select(edaSolutionList &list) const;
  
private:
  unsigned int id;
};

#endif	/* edaIDSelectWrapper_H */

