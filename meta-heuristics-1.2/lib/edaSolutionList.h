/* 
 * File:   edaSoultionList.h
 * Author: Tieu Minh
 *
 * Created on August 18, 2013, 9:34 AM
 */

#ifndef EDASOLUTIONLIST_H
#define	EDASOLUTIONLIST_H
#include "edaDefine.h"
#include "edaSolution.h" 
#include <vector>
/// Lớp trừu tượng edaSolutionList hiện thực danh sách lời giải của bài toán
class edaSolutionList : public edaSerialize, 
        public std::vector<edaSolution *> {
public:
  /// Khởi tạo đối tượng  
  edaSolutionList();
  /// Khởi tạo đối tượng
  edaSolutionList(const edaSolutionList& orig);
  /// Hũy đối tượng
  virtual ~edaSolutionList();
  /// Nhân bản đối tượng
  /// \return Đối tượng cần nhân bản
  edaSolutionList* clone() const;
  /// Tính hàm lượng giá của lời giải
  /// \param \return Giá trị hàm lượng giá của lời giải
  double evaluate() const;
  /// Lấy giá trị lượng giá trung bình của tập lời giải
  /// \return Giá trị lượng giá trung bình 
  double mean() const;
  /// Lấy độ lệch chuẩn của lượng giá của tập lời giải
  /// \return Giá trị độ lệch chuẩn 
  double std() const;
  /// Lấy giá trị lượng giá thấp nhất của tập lời giải
  /// \return Giá trị lượng giá thấp nhất
  double min() const;
  /// Lấy giá trị lượng giá cao nhất của tập lời giải
  /// \return Giá trị lượng giá cao nhất
  double max() const; 
  /// Sắp xếp các cá thể trong tập lời giải theo thứ tự hàm lượng giá
  void sort();
  /// Thay thế (gán giá trị) cho tập lời giải
  /// \param list Tập lời giả cần thay thế
  bool replace(edaSolutionList& list);
  /// Lấy danh sách lời giải con với số lượng cho trước
  /// \param num Số lời giải cần lấy
  /// \return edaSolutionList Danh sách (tập) lời giải con
  edaSolutionList getList(unsigned int num);  
  void printOn(ostream &os) const;
  /// Lấy thông tin lời giải tốt nhất
  /// \return  edaSolution lời giải với giá trị lượng giá tốt nhất  
  edaSolution* getBest() const;
  /// Lấy thông tin ID lời giải tốt nhất
  /// \return  ID của lời giải với giá trị lượng giá tốt nhất
  unsigned int getBestID() const;
  virtual edaSolutionList& operator = (const edaSolutionList &sol);
  virtual void Serialize(edaBuffer &buf, bool pack);
  setClassID( _SYSCLASSID_ + _CLSID_EDASOLUTIONLIST_ );
  /// Xóa thông tin chứa trong đối tượngt
  void easer();
};
ostream& operator<< (ostream &os, const edaSolutionList &list);
#endif	/* EDASOULTIONLIST_H */

