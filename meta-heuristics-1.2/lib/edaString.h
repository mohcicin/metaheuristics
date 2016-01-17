/* 
 * File:   edaString.h
 * Author: Tieu Minh
 *
 * Created on October 28, 2013, 8:18 PM
 */

#ifndef EDASTRING_H
#define	EDASTRING_H
/// Lớp edaString hiện thực việc hổ trợ xử lý chuổi trong thư viện
class edaString {
public:
  /// Khởi tạo đối tượng    
  edaString();
  /// Khởi tạo đối tượng  
  /// \param orig Đối tượng gốc cần sao chép
  edaString(const edaString& orig);
  /// Hủy đối tượng
  virtual ~edaString();
private:

};

#endif	/* EDASTRING_H */

