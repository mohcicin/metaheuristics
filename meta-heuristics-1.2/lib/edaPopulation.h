/* 
 * File:   edaPopulation.h
 * Author: tieuminh
 *
 * Created on April 25, 2012, 10:22 PM
 */

#ifndef __edaPopulation_h__
#define	__edaPopulation_h__

#include "edaChromosome.h"
/// Lớp edaPopulation hiện thực đối tượng quần thể trong giải thuật tiến hóa.
class edaPopulation: public edaSerialize, public vector<edaChromosome*> {
public:
    /// Khởi tạo đối tượng
    edaPopulation();
    /// Khởi tạo đối tượng
    /// \param num Số dân cư trong quẩn thể
    edaPopulation(unsigned int num);
    //Khởi tạo đối tượng
    /// \param pop Đối tượng cần sao chép
    edaPopulation(const edaPopulation &pop);
    /// Nhân bản đối tượng
    edaPopulation *clone() const;
    void printOn(ostream &os) const;
    /// Hũy đối tượng
    virtual ~edaPopulation();
    /// Lấy cá thể nằm cuối tập dân cư
    /// \return Cá thể edaChromosome nằm ở vị trí cuối tập dân cư
    edaChromosome* pop_back(); 
    /// Lấy giá trị lượng giá trung bình của tập dân cư
    /// \return Giá trị lượng giá trung bình 
    double mean() const;
    /// Lấy độ lệch chuẩn của lượng giá của tập dân cư
    /// \return Giá trị độ lệch chuẩn 
    double std() const;
    /// Lấy giá trị lượng giá thấp nhất của tập dân cư
    /// \return Giá trị lượng giá thấp nhất
    double min() const;
    /// Lấy giá trị lượng giá cao nhất của tập dân cư
    /// \return Giá trị lượng giá cao nhất
    double max() const;  
    edaPopulation& operator = (const edaPopulation &pop);
    void Serialize(edaBuffer& buf, bool pack);  
    setClassID(_SYSCLASSID_ + _CLSID_EDAPOPULATION_);  
    /// Xóa thông tin trong đối tượng  
    void easer();
    /// Sắp xếp các cá thể trong tập dân cư theo thứ tự hàm lượng giá
    void sort();    
};
ostream& operator<< (ostream &os, const edaPopulation &pop);
#endif	

