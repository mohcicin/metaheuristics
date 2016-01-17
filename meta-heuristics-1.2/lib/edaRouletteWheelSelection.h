/* 
 * File:   edaCostWeightSelection.h
 * Author: root
 *
 * Created on March 18, 2013, 4:21 PM
 */

#ifndef EDACOSTWEIGHTSELECTION_H
#define	EDACOSTWEIGHTSELECTION_H
#include "edaNaturalSelection.h"
/// Lớp edaRouletteWheelSelection hiện thực chiến lược chọn lọc tự nhiên theo trọng số
class edaRouletteWheelSelection: public edaNaturalSelection {
public:
    /// Khởi tạo đối tượng
    /// \param rate Tỷ lệ chọn lọc
    /// \param alpha Hệ số nền dùng để tính trọng số cho cá thể được chọn lọc
    edaRouletteWheelSelection(const double rate = 1.0, const double alpha = 2);
    /// Khởi tạo đối tượng
    /// \param slect Đối tượng cần sao chép
    edaRouletteWheelSelection(const edaRouletteWheelSelection& slect);
    /// Hũy đối tượng
    virtual ~edaRouletteWheelSelection();    
    edaRouletteWheelSelection* clone() const;   
    void printOn(ostream& os) const;
    /// Tính toán trọng số cho các cá thể trong tập dân cư
    /// \param pop Tập dân cư cần tính toán
    void computeCostWeight(const edaPopulation &pop);
    /// Gán hệ số nền dùng để tính trọng số cho cá thể được chọn lọc
    /// \param value Hệ số nền
    void setAlpha(double value);
    void update(edaPopulation &pop);     
    void Serialize( edaBuffer &buf, bool pack );
    setClassID(_SYSCLASSID_ + _CLSID_EDAROULETTEWHEELSELECTION_);

private:
    void easer();
    double alpha;
    double rate;
    double *weight;
};

#endif	/* EDACOSTWEIGHTSELECTION_H */

