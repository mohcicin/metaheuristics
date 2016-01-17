#ifndef __edaSolution_h__
#define __edaSolution_h__
#include "edaSerialize.h"
#include "edaProblem.h"
using namespace std;
/// Lớp trừu tượng edaSolution hiện thực lời giải của bài toán
class edaSolution : public edaSerialize
{
public:
  /// Khởi tạo đối tượng
  edaSolution() {}
  /// Khởi tạo đối tượng
  edaSolution(const edaSolution &sol) {}
  /// Khởi tạo đối tượng
  edaSolution(const edaProblem &pro) {}
  /// Hủy đối tượng
  virtual ~edaSolution() {}
  /// Nhân bản đối tượng
  /// \return Đối tượng cần nhân bản
  virtual edaSolution* clone() const = 0;
  /// Khởi động đối tượng
  virtual void init() {}
  /// Tính hàm lượng giá của lời giải
  /// \param \return Giá trị hàm lượng giá của lời giải
  virtual double evaluate() = 0;
  /// Lấy giá trị lượng giá (đã tính) của lời giải
  /// \param \return Giá trị hàm lượng giá của lời giải
  virtual double getCost() const = 0;
  /// Thiết lập giá trị lượng giá cho lời giải
  /// \param value Giá trị lượng giá
  virtual void setCost(double value) {}
  virtual edaSolution& operator = (const edaSolution &sol) = 0;
  virtual bool operator == (const edaSolution &sol) const = 0;
  virtual void printOn(ostream &os) const;
  virtual void Serialize(edaBuffer &buf, bool pack) = 0;
};

ostream& operator<< (ostream &os, const edaSolution &sol);
#endif
