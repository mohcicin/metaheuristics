#include "tspKOptNext.h"
#include "tspSolution.h"
#include "tspTwoOpt.h"

tspKOptNext::tspKOptNext()
  : graph(NULL)
{
}

tspKOptNext::tspKOptNext(const Graph &g)
  : graph(new Graph(g))
{
}

tspKOptNext::tspKOptNext(const tspKOptNext &m)
  : graph(new Graph(*(m.graph)))
{
}

tspKOptNext::~tspKOptNext()
{
  if (graph != NULL)
  {
    delete graph;
  }
}

edaMoveGen* tspKOptNext::clone() const
{
  return new tspKOptNext(*this);
}

bool tspKOptNext::generate(edaMove *move, const edaSolution &sol)
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

void tspKOptNext::Serialize(edaBuffer &buf, bool pack)
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

void tspKOptNext::easer() {
  if (graph != NULL)
  {
    delete graph;
  }
  graph = NULL;
}

