#ifndef __edaSequentialControl_h__
#define __edaSequentialControl_h__

#include <map>
#include <vector>

using namespace std;

#include "edaDefine.h"
#include "edaSearch.h"
#include "edaDAG.h"
/// Lớp trừu tượng edaSequentialControl điều khiển quá trình thiết lập workflow tuần tự
class edaSequentialControl
{
  public:
    /// Khởi tạo đối tượng  
    edaSequentialControl();
    /// Đưa đỉnh tìm kiếm vào workflow
    /// \param sa Đỉnh tìm kiếm
    /// \return ID của đỉnh tìm kiếm
    int insertVertex(edaSearch *sa);
    /// Đưa cạnh tìm kiếm vào workflow
    /// \param from Đỉnh tìm kiếm bắt đầu của cạnh
    /// \param to Đỉnh tìm kiếm kết thúc của cạnh
    /// \return ID của cạnh tìm kiếm
    int insertEdge(const int from, const int to);
    /// Thực thi việc tối ưu trên trình diều kiển
    /// \param list Danh sách các lời giải cần tối ưu
    bool search(edaSolutionList &list);

  private:
    vector<int> findReadyNodes() const;
    bool allDone() const;

    edaDAG<edaSearch*> taskDAG;
    int edgeNum;
    map<int, int> taskStatus;
    int vertexNum;
};

#endif
