#ifndef __edaDAGVertex_h__
#define __edaDAGVertex_h__

#include <vector>

using namespace std;
class edaDAGEdge;
/// Lớp edaDAGEdge là hiện thực của đỉnh đồ thị DAG 
class edaDAGVertex
{
  public:

    /// Khởi tạo đối tượng
    edaDAGVertex(int key);
    
    /// Hủy đối tượng
    ~edaDAGVertex();
    
    /// Lấy khóa của đối tượng
    int getKey() const;

    /// Thêm cạnh vào 
    void insertInEdge(edaDAGEdge *inEdge);

    /// Thêm cạnh ra
    void insertOutEdge(edaDAGEdge *outEdge);

    /// Lấy tất cả các cạnh vào của đỉnh
    vector<edaDAGEdge *> *getInEdges();
    
    /// Lấy tất cả các cạnh ra của đỉnh
    vector<edaDAGEdge *> *getOutEdges();    
   
    /// Lấy tổng số cạnh vào
    int getInDegree();
    
    /// Lấy tổng số cạnh ra
    int getOutDegree();    
    
    /// Kiểm tra sự tồn tại chu trình tại đỉnh
    bool cycleCheck(int &cycleVertex);
    
    /// Thiết lập cờ đánh đấu sự xuất hiện của chu trình
    void setCycle(bool flag);
  private:
    vector<edaDAGEdge *> inEdges;
    vector<edaDAGEdge *> outEdges;
    bool cycleCheckFlag;
    int vertexKey;
};

#endif
