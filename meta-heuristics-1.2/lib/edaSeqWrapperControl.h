#ifndef __edaSeqWrapperControl_h__
#define __edaSeqWrapperControl_h__

#include "edaWrapperControl.h"
/// Lớp trừu tượng edaWrapperControl điều khiển quá trình tối ưu tuần tự
class edaSeqWrapperControl : public edaWrapperControl
{
  public:
    /// Khởi tạo đối tượng  
    edaSeqWrapperControl();
    /// Thực thi việc tối ưu trên trình diều kiển
    /// \param list Danh sách các lời giải cần tối ưu
    bool search(edaSolutionList &list);
};

#endif
