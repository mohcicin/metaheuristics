#ifndef __edaAdaption_h__
#define	__edaAdaption_h__

#include "edaSearch.h"
#include "edaPopulation.h"
#include "edaRepresentation.h"

/// Lớp edaAdaption thực hiện việc cải tiến trên danh sách lời giải đầu vào dựa trên các giải thuật tìm kiếm cục bộ theo một tỷ lệ cho trước.
class edaAdaption: public edaSerialize {
public:

    /// Khởi tạo đối tượng
    edaAdaption() {}

    /// Khởi tạo đối tượng
    /// \param lSearch Toán tử tìm kiếm cục bộ trong đối tượng
    /// \param rate Tỷ lệ cải tiến trong danh sách lời giải (0 < rate < 1)
    edaAdaption(edaSearch *lSearch, double rate = 1.0);   
    

    /// Khởi tạo đối tượng
    /// \param adapt Đối tượng cần sao chép
    edaAdaption(const edaAdaption &adapt);
    
    /// Hủy đối tượng  
    ~edaAdaption();  

    /// Nhân bản đối tượng
    edaAdaption* clone() const;    

    /// Thiết lập tỷ lệ cải tiến trong danh sách lời giải
    /// \param rate Tỷ lệ cải tiến trong danh sách lời giải (0 < rate < 1) 
    void setRate(const double& rate);
    
    /// In thông tin (dạng chuổi) của đối tượng lên ostream
    void printOn(ostream& os) const;
    
    /// Thực hiện việc cải tiến lên danh sách lời giải
    /// \param list Danh sách các lời giải cần cải tiến
    void update(edaSolutionList &list) const;    
    
    /// Hiện thực việc đóng gói và mở gói các thông tin của đối tượng
    /// \param buf Bộ đệm có hổ trợ việc đóng gói và nhận các thông tin của đối tượng 
    /// \param pack Cờ hiệu: đóng gới (pack = 1), và giải gói (pack = 0))
    void Serialize( edaBuffer &buf, bool pack );
    
    /// Gán ID nhận dạng thuộc lớp edaAdaption cho đối tượng
    setClassID(_SYSCLASSID_ + _CLSID_EDAADAPTION_);

private:
    edaSearch *lsearch;
    float rate;
};
ostream& operator<< (ostream &os, const edaAdaption &adapt);
#endif

