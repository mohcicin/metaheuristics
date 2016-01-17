/* 
 * File:   edaME.h
 * Author: tieuminh
 *
 * Created on April 25, 2012, 9:43 PM
 */

#ifndef __edaMA_h__
#define	__edaMA_h__

#include "edaSearch.h"
#include "edaContinue.h"
#include "edaChromosome.h"
#include "edaPopulation.h"
#include "edaNaturalSelection.h"
#include "edaMutation.h"
#include "edaCrossover.h"
#include "edaSolution.h"
#include "edaAdaption.h"
/// Lớp edaMA thực hiện việc tối ưu theo giải thuật Memetic.
class edaMA: public edaSearch {
public:
    /// Khởi tạo đối tượng
    edaMA();
    /// Khởi tạo đối tượng
    /// \param con Điều kiện dừng
    /// \param repre Toán tử mã hóa
    /// \param slect Toán tử chọn lọc (tự nhiên)
    /// \param cross Toán tử lai chéo
    /// \param mute Toán tử đột biến
    /// \param adapt Toán tử cải tiến
    /// \param elite Số phần tử ưu việt
    /// \param timeout Thời gian thực thi tìm kiếm
    /// \param power Bậc tìm kiếm
    edaMA(edaContinue *con,
          edaRepresentation *repre,   
          edaNaturalSelection *slect,
          edaCrossover *cross,
          edaMutation *mute,
          edaAdaption *adapt,
          unsigned int elite = 1,
          int timeout = 0,
          int power = 0);
    
    /// Khởi tạo đối tượng
    /// \param ma Đối tượng search cần sao chép
    edaMA(const edaMA &ma);
    
    edaMA* clone() const;
    /// Hủy đối tượng
    virtual ~edaMA();
    
    bool search(edaSolutionList &list);

    virtual void Serialize(edaBuffer &buf, bool pack);
    setClassID( _SYSCLASSID_ + _CLSID_EDAMA_ );

    
private:  
    edaContinue *con;
    edaRepresentation *repre;
    edaNaturalSelection *nSlect;
    edaCrossover *cross;
    edaMutation *mute;
    edaAdaption *adapt;
    edaSolution *bestSol;
    unsigned int elite;
};

#endif

