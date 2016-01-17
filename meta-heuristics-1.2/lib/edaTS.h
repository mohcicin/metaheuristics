#ifndef __edaTS_h__
#define __edaTS_h__

#include "edaSearch.h"
#include "edaMove.h"
#include "edaMoveGen.h"
#include "edaContinue.h"
#include "edaTabuList.h"
#include "edaAspirCrit.h"
#include "edaTSMoveExpl.h"
/// Lớp trừu tượng edaTS thực hiện việc tối ưu theo giải thuật tìm kiếm Tabu.
class edaTS: public edaSearch
{
 public:
  /// Khởi tạo đối tượng
  edaTS();
  /// Khởi tạo đối tượng
  /// \param power Bậc tìm kiếm
  edaTS(int power);
  /// Khởi tạo đối tượng
  /// \param move Chiến lược bước chuyển trong không gian tìm kiếm
  /// \param moveNext Phương pháp tạo bước chuyển trong không gian tìm kiếm
  /// \param aspirCrit Chiến lược kiểm tra sự hợp lệ của các bước chuyển ứng viên
  /// \param continueCriteria Điều kiện dừng
  /// \param timeout Thời gian thực thi tìm kiếm
  /// \param power Bậc tìm kiếm
  edaTS( edaMove *move,
         edaMoveGen *moveNext,
         edaTabuList *tabuList,
         edaAspirCrit *aspirCrit,
         edaContinue *continueCriteria,
         int timeout = 0,
         int power = 0);
  /// Khởi tạo đối tượng
  /// \param move Chiến lược bước chuyển trong không gian tìm kiếm
  /// \param edaTSMoveExpl Chiến lược khai phá không gian tìm kiếm cho giải thuật TS
  /// \param continueCriteria Điều kiện dừng
  /// \param timeout Thời gian thực thi tìm kiếm
  /// \param power Bậc tìm kiếm
  edaTS(edaMove *move,
        edaTSMoveExpl *moveExpl,
        edaContinue *continueCriteria,
        int timeout = 0,
        int power = 0);
  
  /// Khởi tạo đối tượng
  /// \param ma Đối tượng search cần sao chép
  edaTS(const edaTS &ts);
  
  edaTS* clone()const;
  
   /// Hủy đối tượng
  ~edaTS();

  bool search(edaSolutionList &list);
  virtual void Serialize(edaBuffer &buf, bool pack);

  setClassID( _SYSCLASSID_ + _CLSID_EDATS_ );

 private:
  void easer();

  edaMove *move;
  edaContinue *con;
  edaTSMoveExpl *moveExpl;
};

#endif
