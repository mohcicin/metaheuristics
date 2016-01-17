#include "tspOrOptNext.h"
#include "tspSolution.h"
#include "tspOrOpt.h"

tspOrOptNext::tspOrOptNext()
  : graph(NULL)
{
}

tspOrOptNext::tspOrOptNext(const Graph &g)
  : graph(new Graph(g))
{
}

tspOrOptNext::tspOrOptNext(const tspOrOptNext &m)
  : graph(new Graph(*(m.graph)))
{
}

tspOrOptNext::~tspOrOptNext()
{
  if (graph != NULL)
  {
    delete graph;
  }
}

edaMoveGen* tspOrOptNext::clone() const
{
  return new tspOrOptNext(*this);
}

bool tspOrOptNext::generate(edaMove *move, const edaSolution &sol)
{
  tspOrOpt *tspmove = (tspOrOpt *)move;
  if ( (tspmove->FIRST == graph->size() - tspmove->LAMBDA - 2) &&
      (tspmove->SECOND == tspmove->FIRST + tspmove->LAMBDA ) )
  {
    return false;
  }
  else
  {
    tspmove->SECOND++;
    if (tspmove->SECOND == (graph->size() - 1))
    {
      tspmove->FIRST++;
      tspmove->SECOND = tspmove->FIRST + tspmove->LAMBDA;
    }
  }
  return true;
}

void tspOrOptNext::Serialize(edaBuffer &buf, bool pack)
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

void tspOrOptNext::easer() {
  if (graph != NULL)
  {
    delete graph;
  }
  graph = NULL;
}
