#include "tspTwoOptNext.h"
#include "tspSolution.h"
#include "tspTwoOpt.h"

tspTwoOptNext::tspTwoOptNext()
  : graph(NULL)
{
}

tspTwoOptNext::tspTwoOptNext(const Graph &g)
  : graph(new Graph(g))
{
}

tspTwoOptNext::tspTwoOptNext(const tspTwoOptNext &m)
  : graph(new Graph(*(m.graph)))
{
}

tspTwoOptNext::~tspTwoOptNext()
{
  if (graph != NULL)
  {
    delete graph;
  }
}

edaMoveGen* tspTwoOptNext::clone() const
{
  return new tspTwoOptNext(*this);
}

bool tspTwoOptNext::generate(edaMove *move, const edaSolution &sol)
{
  tspTwoOpt *tspmove = (tspTwoOpt *)move;

  if ((tspmove->first == graph->size() - 4) && 
      (tspmove->second == tspmove->first + 2))
  {
    return false;
  }
  else
  {
    tspmove->second++;
    if (tspmove->second == (graph->size() - 1))
    {
      tspmove->first++;
      tspmove->second = tspmove->first + 2;
    }
  }
  return true;
}

void tspTwoOptNext::Serialize(edaBuffer &buf, bool pack)
{
  edaMoveGen::Serialize(buf, pack);

  if (pack)
  {
    graph->doSerialize(buf, pack);
  }
  else
  {
    easer();
    graph = (Graph *)classGenerateFromBuffer(buf);
  }
}

void tspTwoOptNext::easer() {
  if (graph != NULL)
  {
    delete graph;
  }
  graph = NULL;
}
