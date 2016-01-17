/* 
 * File:   edaWriter.h
 * Author: Tieu Minh
 *
 * Created on October 28, 2013, 8:58 PM
 */

#ifndef EDAWRITER_H
#define	EDAWRITER_H
/// Lớp edaWriter hiện thực việc hổ trợ đọc và ghi file
class edaWriter {
public:
  /// Khởi tạo đối tượng  
  edaWriter();
  /// Khởi tạo đối tượng  
  /// \param orig Đối tượng gốc cần sao chép
  edaWriter(const edaWriter& orig);
  /// Hủy đối tượng
  virtual ~edaWriter();
private:

};

#endif	/* EDAWRITER_H */

