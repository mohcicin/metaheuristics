#include "tspOrOptRand.h"
#include "tspSolution.h"
#include "tspOrOpt.h"

tspOrOptRand::tspOrOptRand()
  : graph(NULL)
{
}

tspOrOptRand::tspOrOptRand(const Graph &g)
  : graph(new Graph(g))
{
}

tspOrOptRand::tspOrOptRand(const tspOrOptRand &m)
  : graph(new Graph(*(m.graph)))
{
}

tspOrOptRand::~tspOrOptRand()
{
  if (graph != NULL)
  {
    delete graph;
  }
}

edaMoveGen* tspOrOptRand::clone() const
{
  return new tspOrOptRand(*this);
}

bool tspOrOptRand::generate(edaMove *move, const edaSolution &sol)
{
    tspOrOpt *tspmove = (tspOrOpt *)move;

    tspmove->FIRST = rnd.random(1, graph->size() - tspmove->LAMBDA - 2);
    tspmove->SECOND = rnd.random(tspmove->FIRST + tspmove->LAMBDA, graph->size() - 1 );

  return true;
}

void tspOrOptRand::Serialize(edaBuffer &buf, bool pack)
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

void tspOrOptRand::easer() {
  if (graph != NULL)
  {
    delete graph;
  }
  graph = NULL;
}
