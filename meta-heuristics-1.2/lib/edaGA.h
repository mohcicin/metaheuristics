/* 
 * File:   edaGA.h
 * Author: tieuminh
 *
 * Created on April 25, 2012, 9:43 PM
 */

#ifndef __edaGA_h__
#define	__edaGA_h__

#include "edaSearch.h"
#include "edaContinue.h"
#include "edaChromosome.h"
#include "edaPopulation.h"
#include "edaNaturalSelection.h"
#include "edaMutation.h"
#include "edaCrossover.h"
#include "edaSolution.h"
#include "edaRepresentation.h"

/// Lớp edaGA thực hiện việc tối ưu theo giải thuật di truyền.
class edaGA: public edaSearch {
public:
    /// Khởi tạo đối tượng
    edaGA();
    /// Khởi tạo đối tượng
    /// \param con Điều kiện dừng
    /// \param repre Toán tử mã hóa
    /// \param slect Toán tử chọn lọc (tự nhiên)
    /// \param cross Toán tử lai chéo
    /// \param mute Toán tử đột biến
    /// \param elite Số phần tử ưu việt
    /// \param timeout Thời gian thực thi tìm kiếm
    /// \param power Bậc tìm kiếm
    edaGA(edaContinue *con, 
          edaRepresentation *repre, 
          edaNaturalSelection *slect,
          edaCrossover *cross,
          edaMutation *mute,
          unsigned int elite = 1,
          int timeout = 0,
          int power = 0);
    
    /// Khởi tạo đối tượng
    /// \param ga Đối tượng search cần sao chép
    edaGA(const edaGA &ga);
    
    edaGA* clone() const;
    
    /// Hủy đối tượng
    virtual ~edaGA();
    
    bool search(edaSolutionList &list);
    
    virtual void Serialize(edaBuffer &buf, bool pack);
    
    setClassID( _SYSCLASSID_ + _CLSID_EDAGA_ );

private:
    edaContinue *con;
    edaRepresentation *repre;
    edaNaturalSelection *nSlect;
    edaCrossover *cross;
    edaMutation *mute;
    unsigned int elite;
};

#endif

