/* 
 * File:   edaRepresentation.h
 * Author: root
 *
 * Created on March 15, 2013, 3:26 PM
 */

#ifndef EDAREPRESENTATION_H
#define	EDAREPRESENTATION_H
#include "edaSolutionList.h"
#include "edaChromosome.h"
#include "edaPopulation.h"

/// Lớp trừu tượng edaRepresentation hiện thực việc chứa phương pháp mã hóa từ lời giải thành nhiệm sắc thể.
class edaRepresentation: public edaSerialize {
public:
  /// Khởi tạo đối tượng
  edaRepresentation() {}
  /// Khởi tạo đối tượng
  /// \param pro Thông tin bài toán
  edaRepresentation(const edaProblem &pro) {}
  /// Khởi tạo đối tượng
  /// \param repre Đối tượng cần sao chép
  edaRepresentation(const edaRepresentation& repre) {}
  /// Nhân bản đối tượng
  virtual edaRepresentation* clone() const = 0;
  /// Hũy đối tượng
  virtual ~edaRepresentation() {}
  /// Khởi động đối tượng
  /// \param list Danh sách lời giải ban đầu
  /// \param pop Tập dân cư cần được mã hóa
  virtual void init(const edaSolutionList &list, edaPopulation &pop) const = 0;
  /// Mã hóa tập dân cư từ danh sách lời giải
  /// \param list Danh sách lời giải
  /// \param pop Tập dân cư
  virtual void decode(const edaPopulation &pop, edaSolutionList &list) const = 0;
  /// Giải mã danh sách lời giải từ tập dân cư
  /// \param list Danh sách lời giải
  /// \param pop Tập dân cư
  virtual void encode(const edaSolutionList &list, edaPopulation &pop) const = 0;  

  virtual void printOn(ostream &os) const;
  virtual void Serialize( edaBuffer &buf, bool pack ) = 0;   

};
ostream& operator<< (ostream &os, const edaProblem &problem);
#endif	/* EDAREPRESENTATION_H */

