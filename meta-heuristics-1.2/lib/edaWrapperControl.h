#ifndef __edaWrapperControl_h__
#define __edaWrapperControl_h__

#include <map>
#include <vector>

using namespace std;

#include "edaSearch.h"
#include "edaDAG.h"
#include "edaDefine.h"
#include "edaSelectionWrapper.h"
#include "edaContinue.h"
/// Lớp trừu tượng edaWrapperControl điều khiển quá trình tối ưu
class edaWrapperControl
{
  public:
    /// Khởi tạo đối tượng
    edaWrapperControl();
    /// Hủy dối tượng
    virtual ~edaWrapperControl();
    /// Thêm node tìm kiếm mới vào trình điều khiển
    /// \param sa Node tìm kiếm mới
    virtual int insertVertex(edaSearch *sa);
    /// Thêm node tìm kiếm mới vào trình diều khiển với điều kiên chọn
    /// \param sa Node tìm kiếm mới
    /// \param slect Chiến lược chọn lựa lời giải cho quá trình tối ưu
    virtual int insertVertex(edaSearch *sa, const edaSelectionWrapper &slect);
    /// Thêm cạnh mới vào trình diều khiển
    /// \param from Đỉnh đầu
    /// \param to Đỉnh cuối
    virtual int insertEdge(const int from, const int to);
    /// Thêm vòng lặp mới vào trình diều khiển
    /// \param from Đỉnh bắt đầu lặp
    /// \param to Đỉnh kết thúc vòng lặp
    /// \param con Điều kiện lặp
    virtual int insertLoop(const int from, const int to, const edaContinue &con);
    /// Thực thi việc tối ưu trên trình diều kiển
    /// \param list Danh sách các lời giải cần tối ưu
    virtual bool search(edaSolutionList &list) = 0;
    
  protected:
    virtual vector<int> findReadyTask() const;
    virtual int checkTaskStatus( int taskID);
    virtual int checkLoopStatus( int taskID);
    virtual edaSolutionList* chooseSolution( int taskID, edaSolutionList &list ) ;
    bool allDone();
    
    map<int, edaSolutionList*> taskSolutionList;
    map<int, edaSelectionWrapper *> taskSlect;
    map<int, edaContinue*> loopCond;
    edaDAG<edaSearch*> taskDAG;
    map<int, int> taskStatus;
    map<int, int> loopStatus;

    int edgeNum;
    int vertexNum;
    int loopNum;
};

#endif
