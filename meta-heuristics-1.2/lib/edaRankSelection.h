/* 
 * File:   edaRankWeightSelection.h
 * Author: root
 *
 * Created on March 18, 2013, 4:10 PM
 */

#ifndef EDARANKWEIGHTSELECTION_H
#define	EDARANKWEIGHTSELECTION_H

#include "edaNaturalSelection.h"

/// Lớp edaRankSelection hiện thực chiến lược chọn lọc tự nhiên theo thứ hạng
class edaRankSelection: public edaNaturalSelection {
public:
  /// Khởi tạo đối tượng
  /// \param rate Tỷ lệ chọn lọc
  edaRankSelection(const double rate = 1.0);
  /// Khởi tạo đối tượng
  /// \param slect Đối tượng cần sao chép
  edaRankSelection(const edaRankSelection& slect);
  /// Hũy đối tượng
  virtual ~edaRankSelection(); 
  
  edaRankSelection* clone() const;    
  
  /// Gán tỷ lệ chọn lọc
  /// \param value Tỷ lệ chọn lọc
  void setRate(double value);
  
  void update(edaPopulation &pop);    
  void Serialize( edaBuffer &buf, bool pack );
  void printOn(ostream& os) const;
  setClassID(_SYSCLASSID_ + _CLSID_EDARANKSELECTION_);

private:
  void computeRankWeight(const edaPopulation& pop);
  void easer();  
  double* rank;
  double rate;
};

#endif	/* EDARANKWEIGHTSELECTION_H */

