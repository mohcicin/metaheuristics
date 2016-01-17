#ifndef __edaSearchWrapper_h__
#define __edaSearchWrapper_h__

#include "edaSearch.h"
/// Lớp edaSearchWrapper hổ trợ cơ chế tối ưu với thông tin tìm kiếm đã được đóng gói.
class edaSearchWrapper
{
  public:
    /// Khởi tạo đối tượng
    edaSearchWrapper();
    /// Khởi tạo đối tượng với bộ đệm
    /// \param buf Bộ đệm
    edaSearchWrapper(edaBuffer &buf);
    /// Hũy đối tượng
    virtual ~edaSearchWrapper();
    /// Thực thi tìm kiếm
    /// \param buf_in Bộ đệm đầu vào
    /// \param buf_out Bộ đệm đầu ra
    virtual void search( edaBuffer & buf_in, edaBuffer & buf_out ) = 0;

  protected:
    void setAlgorithm( edaBuffer &_buf );

    edaSearch *searchAlgorithm;
};

#endif
