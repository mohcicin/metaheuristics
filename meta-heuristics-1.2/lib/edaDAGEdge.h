#ifndef __edaDAGEdge_h__
#define __edaDAGEdge_h__

class edaDAGVertex;
/// Lớp edaDAGEdge là hiện thực của cạnh đồ thị DAG 
class edaDAGEdge
{
  public:
    /// Khởi tạo đối tượng
    edaDAGEdge(int _key, edaDAGVertex *_fromVertex, edaDAGVertex *_toVertex);
    
    /// Hủy đối tượng
    ~edaDAGEdge();
    
    /// Lấy khóa của đối tượng
    int getKey() const;
    
    /// Lấy đỉnh đầu
    edaDAGVertex* getSourceVertex() const;
    
    /// Lấy đỉnh cuối
    edaDAGVertex* getDestVertex() const;

  private:
    edaDAGVertex *fromVertex;
    edaDAGVertex *toVertex;
    int edgeKey;
};
#endif
