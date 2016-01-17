#include "edaDAGEdge.h"
#include "edaDAGVertex.h"

edaDAGEdge::edaDAGEdge(int _key, edaDAGVertex *_fromVertex, edaDAGVertex *_toVertex) :
  fromVertex (_fromVertex),
  toVertex (_toVertex),
  edgeKey (_key)
{
}

edaDAGEdge::~edaDAGEdge()
{
}

int edaDAGEdge::getKey() const
{
  return edgeKey;
}

edaDAGVertex* edaDAGEdge::getSourceVertex() const
{
  return fromVertex;
}

edaDAGVertex* edaDAGEdge::getDestVertex() const
{
  return toVertex;
}
