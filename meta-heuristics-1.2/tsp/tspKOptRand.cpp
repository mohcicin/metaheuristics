#include "tspKOptRand.h"

tspKOptRand::tspKOptRand()
  : edaMoveGen(),
    graph(NULL)
{
}

tspKOptRand::tspKOptRand(Graph &g)
  : edaMoveGen(),
    graph(new Graph(g))
{
}

tspKOptRand::tspKOptRand(const tspKOptRand &m)
  : edaMoveGen(m),
    graph(new Graph(*(m.graph)))
{
}

tspKOptRand::~tspKOptRand()
{
  if (graph != NULL)
  {
    delete graph;
  }
}

edaMoveGen *tspKOptRand::clone() const
{
  return new tspKOptRand(*(this->graph));
}

bool tspKOptRand::generate(edaMove *move, const edaSolution &sol)
{
  tspKOpt *tspmove = (tspKOpt *)move;
  tspmove->first = rnd.random(graph->size() - 3);
  tspmove->second = tspmove->first + 2 + rnd.random(graph->size() - tspmove->first - 3);

  return true;
}

void tspKOptRand::Serialize(edaBuffer &buf, bool pack)
{
  if (pack)
  {
    graph->doSerialize(buf, pack);
  }
  else
  {
    if (graph != NULL)
    {
      delete graph;
    }
    else
    {
      graph = (Graph *) classGenerateFromBuffer(buf);
    }
  }
}
