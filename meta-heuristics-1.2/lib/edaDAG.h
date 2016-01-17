#ifndef __edaDAG_h__
#define __edaDAG_h__

#include "edaDAGVertex.h"
#include "edaDAGEdge.h"
#include "edaException.h"
#include "edaSelectionWrapper.h"
#include "edaCluster.h"


using namespace std;

/*
 * Exception class
 */
/*
class edaEdgeNotFoundException : public edaException
{
  edaEdgeNotFoundException() : edaException()
  {
  }

  edaEdgeNotFoundException(std::string _errorMessage) : edaException(_errorMessage)
  {
  }
};
*/
/*
 * Exception class
 */
/*
class edaEdgeDuplicateException : public edaException
{
  edaEdgeDuplicateException() : edaException()
  {
  }

  edaEdgeDuplicateException(std::string _errorMessage) : edaException(_errorMessage)
  {
  }
};
*/

/*
 * Exception class
 */
/*
class edaVertexNotFoundException : public edaException
{
  edaVertexNotFoundException() : edaException()
  {
  }

  edaVertexNotFoundException(std::string _errorMessage) : edaException(_errorMessage)
  {
  }
};
*/
/*
 * Exception class
 */
/*
class edaVertexDuplicateException : public edaException
{
  edaVertexDuplicateException() : edaException()
  {
  }

  edaVertexDuplicateException(std::string _errorMessage) : edaException(_errorMessage)
  {
  }
};
*/
/// Lớp edaDAG hiện thực đồ thị có hướng không vòng với kiểu dữ liệu tùy biến   
template <class DataType>
class edaDAG
{
  public:
    /// Khởi tạo đồ thị  
    edaDAG() {}
    
    /// Hủy đồ thị   
    ~edaDAG()
    {
      map<int, edaDAGVertex *>::iterator vit;
      map<int, edaDAGEdge *>::iterator eit;
      map<int, edaDAGEdge *>::iterator lit;
      typename map<int, DataType>::iterator dit;
      for( vit=vertices.begin(); vit!=vertices.end(); vit++ )
        delete vit->second;
      for( eit=edges.begin(); eit!=edges.end(); eit++ )
        delete eit->second;
      for( lit=loops.begin(); lit!=loops.end(); lit++) 
        delete lit->second;
      for( dit=data.begin(); dit!=data.end(); dit++) 
        delete dit->second;
    }
    /// Lấy chiều dài dữ liệu
    int count() const
    {
      return data.size();
    }

    /*
     * Create new vertex
     * \param key The key of new vertex
     * \param data The data to insert
     * \throw edaVertexDuplicateException if found two vertex have the same keys
     */
    
    /// Tạo đỉnh mới
    /// \param key Khóa của đỉnh
    /// \param data Dữ liệu cần thêm vào đồ thị
    void insertVertex(int key, DataType &_data) //throw (edaVertexDuplicateException)
    {
      // Check for duplicate vertex
      if (vertices.find(key) != vertices.end())
      {
//        throw new edaVertexDuplicateException();
      }

      // Create new vertex
      edaDAGVertex *vertex = new edaDAGVertex(key);

      // insert to vertices list
      vertices[key] = vertex;

      // and insert to data list
      data[key] = _data;
    }
  
    /*
     * Create new edge
     * \param key Key of new edge
     * \param fromVertex Source vertex
     * \param toVertex Destination vertex
     * \throw edaVertexNotFoundException if the source or destination vertex not found
     * \throw edaEdgeDuplicateException if the edge is duplicate
     */ 
    
    /// Tạo cạnh mới
    /// \param key Khóa của cạnh
    /// \param fromVertex Khóa của đỉnh bắt đầu
    /// \param toVertex Khóa của đỉnh kết thúc
    void insertEdge(int key, int fromVertex, int toVertex) // throw (edaVertexNotFoundException, edaEdgeDuplicateException)
    {
      // Check for duplicate edge
      if (edges.find(key) != edges.end())
      {
//          throw new edaEdgeDuplicateException();
      }

      // Source vertex not found
      if (vertices.find(fromVertex) == vertices.end())
      {
//          throw new edaVertexNotFoundException(std::string("Source vertex not found"));
      }

      // Destination vertex not found
      if (vertices.find(toVertex) == vertices.end())
      {
//          throw new edaVertexNotFoundException("Destination vertex not found");
      }

      // Insert new edge
      edaDAGEdge *edge = new edaDAGEdge(key, vertices[fromVertex], vertices[toVertex]);
      edges[key] = edge;

      // Update inbound edge and outbound edge of vertex
      vertices[fromVertex]->insertOutEdge(edge);
      vertices[toVertex]->insertInEdge(edge);
    }
    
    /// Tạo vòng lặp mới
    /// \param key Khóa của vòng lặp
    /// \param fromVertex Khóa của đỉnh bắt đầu
    /// \param toVertex Khóa của đỉnh kết thúc
    bool insertLoop(int key, int &fromVertex, int &toVertex) 
    {
      // Check for simple loop
      bool checkInvert = clusterCheck(fromVertex, toVertex);     
      if (clusterCheck(toVertex, fromVertex) 
              || checkInvert ) 
      {

        if(checkInvert) 
        {       
          int tmp = fromVertex;
          fromVertex = toVertex;
          toVertex = tmp;
        }        
        if(! loops.empty()) 
        {
          edaCluster *newClus = getCluster(fromVertex, toVertex);
          map<int, edaDAGEdge*>::iterator lit;
          for(lit = loops.begin(); lit != loops.end(); lit++) 
          {
            edaCluster *clus = getCluster(lit->second->getSourceVertex()->getKey(),
                    lit->second->getDestVertex()->getKey() );            
            //Overlap between cluster
            if(!newClus->isCover(*clus) && !clus->isCover(*newClus) 
                    && newClus->isOverlap(*clus) ) return false;
            //Identical
             if(newClus->isCover(*clus) && clus->isCover(*newClus) ) return false;
          } 
        }    
        edaDAGEdge *loop = new edaDAGEdge(key, vertices[fromVertex], vertices[toVertex]);
        loops[key] = loop;
        return true;
      }
      return false;
    }
    
    /*
     * Check for cluster
     * \param cluster The node that have involved in the cycle
     * \return true if there is a cycle in graph
     */
    
    /// Kiểm tra vòng kết nối thỏa điều kiện cụm node hay không
    /// \param fromVertex Khóa của đỉnh bắt đầu
    /// \param toVertex Khóa của đỉnh kết thúc
    bool clusterCheck(const int &fromVertex,const int &toVertex) 
    {
      vector<edaDAGVertex *> stack;    
      
      //Checking left to right
      stack.push_back(vertices[fromVertex]);
      do 
      { 
        edaDAGVertex *vertex = stack.back();
        stack.pop_back();
        int key = vertex->getKey(); 
 
        //The final vertex must be toVertex
        if(vertex->getOutDegree() == 0 
                &&key != toVertex) {
          return false;          
        }        
       
        if(key != toVertex) {
          vector<edaDAGEdge *> * edgeList = vertex->getOutEdges();
          for(unsigned int i = 0; i < edgeList->size(); i++)     {  
            edaDAGVertex* nextVertex = edgeList->at(i)->getDestVertex();
            stack.push_back(nextVertex);
          }      
        }
      } while (!stack.empty());

      //Checking right to left
      stack.push_back(vertices[toVertex]);
      do 
      { 
        edaDAGVertex *vertex = stack.back();
        stack.pop_back();
        int key = vertex->getKey(); 
        if(vertex->getInDegree() == 0 
                &&key != fromVertex) {
          return false;
        }        
        if(key != fromVertex) {
          vector<edaDAGEdge *> * edgeList = vertex->getInEdges();
          for(unsigned int i = 0; i < edgeList->size(); i++)     {  
            edaDAGVertex* nextVertex = edgeList->at(i)->getSourceVertex();
            stack.push_back(nextVertex);
          }      
        }
      } while (!stack.empty());
      
      return true;
    }
    
    /// Lấy cụm node từ vòng kết nối
    /// \param fromVertex Khóa của đỉnh bắt đầu
    /// \param toVertex Khóa của đỉnh kết thúc 
    /// \return Đối tượng edaCluster thuộc vòng kết nối
    edaCluster* getCluster(const int &fromVertex,const int &toVertex) 
    { 
      vector<edaDAGVertex *> stack;    
      map<int, edaDAGVertex *> loop;
      edaCluster *cluster = new edaCluster () ;      

      stack.push_back(vertices[toVertex]);
      do 
      { 
        edaDAGVertex *vertex = stack.back();
        stack.pop_back();            
        if(vertex->getKey() != fromVertex) {
          vector<edaDAGEdge *> * edgeList = vertex->getOutEdges();
          for(unsigned int i = 0; i < edgeList->size(); i++)     {  
            edaDAGVertex* nextVertex = edgeList->at(i)->getDestVertex();
            stack.push_back(nextVertex);
          }     
        }
        loop[vertex->getKey()] = vertex;
      } while (!stack.empty());
      
      map<int, edaDAGVertex *>::iterator it;
      for(it = loop.begin(); it != loop.end(); it++ ) {
        cluster->push_back(it->second);
      }
      return cluster;
    }
    
    /// Lấy cụm node từ vòng kết nối
    /// \param loop Vòng lặp thuộc đồ thị
    /// \return Đối tượng edaCluster thuộc vòng lặp
    edaCluster* getCluster(const edaDAGEdge* loop) 
    {
      int fromVertex = loop->getSourceVertex()->getKey();
      int toVertex = loop->getDestVertex()->getKey();
      return getCluster(fromVertex, toVertex);    
    }
    
    /// Tìm vòng lặp liên kết với một node có khóa cho trước ứng với trạng thái sẳn sàng
    /// \param taskID Khóa của node
    /// \param loopStatus Trạng thái xử lý của vòng lặp
    /// \return Tập các cạnh edaDAGEdge là vòng lặp với trạng thái chờ sẳn sàng
    edaDAGEdge* findLoop(int taskID, map<int, int>& loopStatus) {
      map<int, edaDAGEdge *>::iterator mapIterator;
      vector<edaDAGEdge *> stack;
      for(mapIterator = loops.begin(); mapIterator != loops.end(); mapIterator++)
      {     
        edaDAGEdge* loop = mapIterator->second;
        if( loopStatus[loop->getKey()] != STATUS_FINISHED &&
                loop->getSourceVertex()->getKey() == taskID ) 
             stack.push_back(loop);
      }
      if(stack.size() == 1 ) 
        return stack[0];
      else if (stack.size() > 1){
        unsigned int min = 0;
        for(unsigned int i = 1; i < stack.size(); i++) {                  
          edaCluster *minCluster = getCluster(stack[min]);
          edaCluster *cluser = getCluster(stack[i]);
          if( minCluster->isCover(*cluser) ) {
            min = i;
          }
        }
        return stack[min];
      }
      else
        return NULL;
    }
    
    /// Dò tìm các vòng lặp con thuộc vòng lặp cho trước
    /// \param loop Vòng lặp cần tìm các vòng lặp con
    /// \return Tập các cạnh edaDAGEdge là vòng lặp con
    vector<edaDAGEdge*>* detectSubLoop(const edaDAGEdge& loop) {
      vector<edaDAGEdge*>* result = new vector<edaDAGEdge*>(); 
      edaCluster* base = getCluster(&loop);
      map<int, edaDAGEdge *>::iterator it;
      for(it = loops.begin(); it != loops.end(); it++ ) {
        edaCluster* sub = getCluster(it->second);
        bool isSub = base->isCover( *sub );
        if(isSub && !sub->isCover(*base) ) {
          result->push_back(it->second);
        }
        delete sub;
      }
      delete base;
      return result;
    }
    
    /// Dò tìm các vòng lặp liên kết với một node có khóa cho trước chưa xử lý torng đồ thị
    /// \param taskID Khóa của node
    /// \param loopStatus Trạng thái xử lý của vòng lặp
    /// \return Tập các cạnh edaDAGEdge là vòng lặp với chưa xử lý trong đồ thị  
    edaDAGEdge* detectLoop(int taskID, map<int, int>& loopStatus ) {
      map<int, edaDAGEdge *>::iterator mapIterator;
      vector<edaDAGEdge *> stack;
      for(mapIterator = loops.begin(); mapIterator != loops.end(); mapIterator++)
      {
        edaDAGEdge* loop = mapIterator->second;
        if( loopStatus[loop->getKey()] != STATUS_FINISHED &&
                loop->getDestVertex()->getKey() == taskID ) 
             stack.push_back(loop);
      }
      if(stack.size() == 1 ) 
        return stack[0];
      else if (stack.size() > 1){
        unsigned int min = 0;
        for(unsigned int i = 1; i < stack.size(); i++) {
          edaCluster *minCluster = getCluster(stack[min]);
          edaCluster *cluser = getCluster(stack[i]);
          if( minCluster->isCover(*cluser) )
            min = i;
        }
        return stack[min];
      }
      else
        return NULL;
    }
    
    /// Lấy vòng lặp từ thông tin khóa của chính nó
    edaDAGEdge* getLoop(int loopID) {
      map<int, edaDAGEdge *>::iterator mapIterator;
      mapIterator = loops.find(loopID);

      // Not found
      if (mapIterator == loops.end())
      {
        return NULL;
      }
      return (*mapIterator).second;
    }   
    
    /// Kiểm tra sự tồn tại vòng trong đồ thị
    bool cycleCheck(int &cycleVertex)
    {
      map<int, edaDAGVertex *>::iterator mapIterator;
      // Unset the flag of vertices
      for (mapIterator = vertices.begin(); mapIterator != vertices.end(); mapIterator++)
      {
        (*mapIterator).second->setCycle(false); 
      }

      // Run the cycle check
      for (mapIterator = vertices.begin(); mapIterator != vertices.end(); mapIterator++)
      {
        if ((*mapIterator).second->cycleCheck(cycleVertex))
        {
          // There is a cycle
          return true;
        }
      }
    }

    /// Lấy đỉnh từ thông tin khóa của chính nó
    edaDAGVertex* getVertex(int key)
    {
      map<int, edaDAGVertex *>::iterator mapIterator;
      mapIterator = vertices.find(key);

      // Not found
      if (mapIterator == vertices.end())
      {
        return NULL;
      }
      return (*mapIterator).second;
    }

    /// Lấy cạnh từ thông tin khóa của chính nó
    edaDAGEdge* getEdge(int key)
    {
      map<int, edaDAGEdge *>::iterator mapIterator;
      mapIterator = edges.find(key);

      // Not found
      if (mapIterator == edges.end())
      {
        return NULL;
      }
      return (*mapIterator).second;
    }

    /**
     * Get the reference to data
     * \param key The key of vertex to get data
     */
    DataType& operator [](int key) //throw (edaVertexNotFoundException)
    {
      /*
      map<int, edaDAGVertex *>::iterator mapIterator;
      mapIterator = vertices.find(key);

      // Not found
      if (mapIterator == vertices.end())
      {
//        throw new edaVertexNotFoundException();
      }

      return (*mapIterator).second;
      */
      return data[key];
    }

    /// Lấy các đỉnh cha từ thông tin khóa của đỉnh con
    vector<int> getParentNodes(int key) const
    {
      vector<int> parentNodes;
 
      edaDAGVertex *vertex;
      vector<edaDAGEdge *> *inEdges;

      map<int, edaDAGVertex *>::const_iterator mci;

      mci = vertices.find(key);
      vertex = mci->second;
      inEdges = vertex->getInEdges();

      vector<edaDAGEdge *>::const_iterator edgeIter;
      for (edgeIter = inEdges->begin(); edgeIter != inEdges->end(); edgeIter++)
      {
        parentNodes.push_back(((*edgeIter)->getSourceVertex())->getKey());
      }      
      return parentNodes;
      
    }
    
    /// Duyệt qua đồ thị 
    vector<int> traverse() const
    {
      vector<int> nodeList;
      typename map<int, DataType>::const_iterator iter;

      for (iter = data.begin(); iter != data.end(); iter++)
      {
        nodeList.push_back(iter->first);
      }

      return nodeList;
    }

  private:

    map<int, edaDAGVertex *> vertices;
    map<int, edaDAGEdge *> edges;
    map<int, edaDAGEdge *> loops;
    map<int, DataType> data;
};

#endif
