#ifndef __edaSeqSearchWrapper_h__
#define __edaSeqSearchWrapper_h__

#include "edaSearchWrapper.h"
/// Lớp trừu tượng edaSeqSearchWrapper điều khiển quá trình tối ưu bằng cơ chế tuần tự
class edaSeqSearchWrapper : public edaSearchWrapper
{
  public:
    /// Khởi tạo đối tượng
    edaSeqSearchWrapper();
    /// Khởi tạo đối tượng
    /// \param buf Bộ đệm
    edaSeqSearchWrapper(edaBuffer &buf);
    /// Hủy dối tượng
    virtual ~edaSeqSearchWrapper();

    void search( edaBuffer &_buf_in, edaBuffer &_buf_out );
};

#endif
