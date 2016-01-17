#include "edaDAGVertex.h"
#include "edaDAGEdge.h"

edaDAGVertex::edaDAGVertex(int key) : vertexKey (key)
{
}

edaDAGVertex::~edaDAGVertex()
{
}

int edaDAGVertex::getKey() const
{
  return vertexKey;
}

void edaDAGVertex::insertInEdge(edaDAGEdge *inEdge)
{
  inEdges.push_back(inEdge);
}

void edaDAGVertex::insertOutEdge(edaDAGEdge *outEdge)
{
  outEdges.push_back(outEdge);
}

vector<edaDAGEdge *>* edaDAGVertex::getInEdges()
{
  return &inEdges;
}

vector<edaDAGEdge *>* edaDAGVertex::getOutEdges()
{
  return &outEdges;
}

bool edaDAGVertex::cycleCheck(int &cycleVertex)
{
  if (cycleCheckFlag == true)
  {
    cycleVertex = vertexKey;
    return true;
  }

  cycleCheckFlag = true;

  vector<edaDAGEdge *>::iterator vecIter;
  for (vecIter = outEdges.begin(); vecIter != outEdges.end(); vecIter++)
  {
    if ((*vecIter)->getDestVertex()->cycleCheck(cycleVertex) == true)
    {
      return true;
    }
  }

  cycleCheckFlag = false;
  return false;
}

void edaDAGVertex::setCycle(bool flag) {
  cycleCheckFlag = flag;
}

int edaDAGVertex::getInDegree() {
  return inEdges.size();
}
/**
 * Get indegree
 */
int edaDAGVertex::getOutDegree() {
  return outEdges.size();
}
