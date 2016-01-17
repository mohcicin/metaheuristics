#ifndef __edaCrossOver_h__
#define	__edaCrossOver_h__

#include "edaPopulation.h"
/// Lớp trừu tượng edaCrossover mô tả các thông tin về chiến lược lai chéo giữa các nhiệm sắc thể.
class edaCrossover: public edaSerialize {
public:
    /// Khởi tạo đối tượng
    edaCrossover() {}
    
    /// Khởi tạo đối tượng với đối tượng cần sao chép
    edaCrossover(const edaCrossover &cross) {}
    
    /// Hủy đối tượng
    virtual ~edaCrossover() {}
    
    /// Nhân bản đối tượng
    virtual edaCrossover *clone() const = 0;    
    
        
    /// Thực hiện việc cập nhật tập dân cư với chiến lược tương ứng với từng hiện thực cụ thể
    /// \param pop Tập dân cư cần lai chéo
    virtual void update(edaPopulation &pop) = 0;   
    
    /// Hiện thực việc đóng gói và mở gói các thông tin của đối tượng
    /// \param buf Bộ đệm có hổ trợ việc đóng gói và nhận các thông tin của đối tượng 
    /// \param pack Cờ hiệu: đóng gới (pack = 1), và giải gói (pack = 0))
    virtual void Serialize(edaBuffer &buf, bool pack) = 0;
    virtual void printOn(ostream &os) const;

};
ostream& operator<< (ostream &os, const edaCrossover &cross);
#endif	
