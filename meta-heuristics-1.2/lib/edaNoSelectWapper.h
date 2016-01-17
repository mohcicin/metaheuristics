/* 
 * File:   edaNoSelectWapper.h
 * Author: tieuminh
 *
 * Created on September 25, 2013, 8:29 AM
 */

#ifndef EDANOSELECTWAPPER_H
#define	EDANOSELECTWAPPER_H

#include "edaSelectionWrapper.h"

/// Lớp edaNoSelectWapper thực hiện việc loại bỏ tất cả các lời giải trong sanh sách lời giải.
class edaNoSelectWapper: public edaSelectionWrapper {
public:
  edaNoSelectWapper();
  virtual ~edaNoSelectWapper();
  edaNoSelectWapper * clone() const;
  bool select(edaSolutionList &list) const;
private:

};

#endif	/* EDANOSELECTWAPPER_H */

