/* 
 * File:   edaCluster.h
 * Author: Tieu Minh
 *
 * Created on September 3, 2013, 9:44 AM
 */

#ifndef EDACLUSTER_H
#define	EDACLUSTER_H

#include "edaSerialize.h"
#include "edaDAGVertex.h"
#include <vector>
using namespace std;

/// Lớp edaCluster chứa thông tin vì các cụm node tìm kiếm và các thao tác trên chúng.
class edaCluster: public vector<edaDAGVertex*>  {
public:
  /// Khởi tạo đối tượng
  edaCluster() {}
  
  /// Hủy đối tượng  
  virtual ~edaCluster() {}
  
  /// Kiểm tra xem 2 cụm node tìm kiếm có phủ nhau hay không
  bool isOverlap(const edaCluster& _clus);
  
  /// Kiểm tra xem 2 cụm node tìm kiếm có chứa nhau hay không
  bool isCover(const edaCluster& _clus);
  
  /// In thông tin (dạng chuổi) của đối tượng lên ostream
  void printOn(ostream &os) const;
};
ostream& operator<< (ostream &os, const edaCluster &clus);
#endif	/* EDACLUSTER_H */

