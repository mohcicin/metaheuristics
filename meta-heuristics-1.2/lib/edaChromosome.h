#ifndef __edaChromosomes_h__
#define	__edaChromosomes_h__

#include "edaSerialize.h"
#include "edaGenne.h"
#include <vector>


using namespace std;
/// Lớp edaChromosome chứa thông tin về nhiễm sắc thể và các phương thức tương ứng.
class edaChromosome: public edaSerialize {
public:
  /// Khởi tạo đối tượng
  edaChromosome();
  
  /// Khởi tạo đối tượng
  /// \param chro Đối tượng cần sao chép
  edaChromosome(const edaChromosome &chro);
  
  /// Hủy đối tượng  
  virtual ~edaChromosome();
  
  /// Nhân bản đối tượng
  virtual edaChromosome* clone() const; 
  
  /// Thêm đoạn gen và cuối nhiễm sắc thể
  /// \param genne Đoạn gen cần thêm 
  virtual void addGenne(const edaGenne & genne); 
  
  /// Lấy đoạn gen từ nhiễm sắc thể
  /// \param index Chỉ số của đoạn cần lấy 
  /// \return genne Đoạn gen cần lấy 
  virtual edaGenne *getGenne(unsigned int index) const;
  
  /// Lấy giá trị lượng giá của nhiễm sắc thể
  /// \return Giá trị lượng giá của nhiễm sắc thể
  virtual double getFitness() const;
  
  /// Gán giá trị lượng giá của nhiễm sắc thể
  /// \param finess Giá trị lượng giá của nhiễm sắc thể
  virtual void setFitness(double finess);
  
  /// Lấy chiều dài (số lượng gen) của nhiễm sắc thể
  /// \return Chiều dài của nhiễm sắc thể
  virtual unsigned int getLength() const;
  
  virtual edaChromosome& operator = (const edaChromosome &chro);
  virtual bool operator == (const edaChromosome &chro) const;
  virtual bool operator != (const edaChromosome &chro) const;
  
  /// In thông tin (dạng chuổi) của đối tượng lên ostream
  virtual void printOn(ostream &os) const;
  
  /// Hiện thực việc đóng gói và mở gói các thông tin của đối tượng
  /// \param buf Bộ đệm có hổ trợ việc đóng gói và nhận các thông tin của đối tượng 
  /// \param pack Cờ hiệu: đóng gới (pack = 1), và giải gói (pack = 0))
  virtual void Serialize( edaBuffer &buf, bool pack );  
  
  /// Gán ID nhận dạng thuộc lớp edaAdaption cho đối tượng
  setClassID(_SYSCLASSID_ + _CLSID_EDACHROMOSOME_);  
  
protected:  
  virtual void easer();
  vector<edaGenne*> list;
  double fitness;

};
ostream& operator<< (ostream &os, const edaChromosome &chro);
#endif	

