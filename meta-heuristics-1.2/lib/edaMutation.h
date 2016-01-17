/* 
 * File:   edaMutation.h
 * Author: tieuminh
 *
 * Created on April 30, 2012, 11:00 AM
 */

#ifndef __edaMutation_h__
#define	__edaMutation_h__

#include "edaSerialize.h"
#include "edaPopulation.h"
/// Lớp trừ tượng edaMutation hiện thực các chiến lược đột biến
class edaMutation: public edaSerialize {
public:
    /// Khởi tạo đối tượng
    edaMutation() {}
    edaMutation(const edaMutation& mute) {} 
    /// Hủy đối tượng
    virtual ~edaMutation() {}
    /// Nhân bản đối tượng
    virtual edaMutation* clone() const = 0;    
    /// Thực thi chiến lược đột biến lên tập dân cư
    /// \param pop Tập dân cư cần đột biến
    virtual void update(edaPopulation &pop) const = 0;
    virtual void Serialize(edaBuffer &buf, bool pack) = 0;
    virtual void printOn(ostream& os) const;

};
ostream& operator<< (ostream &os, const edaMutation &mute);
#endif	/* EDAMUTATION_H */

