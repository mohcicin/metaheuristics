/* 
 * File:   edaFullSelectWrapper.h
 * Author: Tieu Minh
 *
 * Created on August 22, 2013, 10:30 PM
 */

#ifndef EDAFULLSELECTWRAPPER_H
#define	EDAFULLSELECTWRAPPER_H

#include "edaSelectionWrapper.h"

/// Lớp edaFullSelectWrapper thực hiện việc chọn tất cả các lời giải trong danh sách lời giải và đưa chúng vào nút tìm kiếm.
class edaFullSelectWrapper : public edaSelectionWrapper {
public:
  /// Khởi tạo đối tượng
  edaFullSelectWrapper(); 
  /// Hủy đối tượng
  ~edaFullSelectWrapper();

  edaFullSelectWrapper * clone() const;
  bool select(edaSolutionList &list) const;
};

#endif	/* EDAFULLSELECTWRAPPER_H */

