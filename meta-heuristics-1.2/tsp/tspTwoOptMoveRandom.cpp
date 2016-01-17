#include "tspTwoOpt.h"
#include "tspTwoOptMoveRandom.h"

tspTwoOptMoveRandom::tspTwoOptMoveRandom()
  : edaMoveGen(),
    graph(NULL)
{
}

tspTwoOptMoveRandom::tspTwoOptMoveRandom(Graph &g)
  : edaMoveGen(),
    graph(new Graph(g))
{
}

tspTwoOptMoveRandom::tspTwoOptMoveRandom(const tspTwoOptMoveRandom &m)
  : edaMoveGen(m),
    graph(new Graph(*(m.graph)))
{
}

tspTwoOptMoveRandom::~tspTwoOptMoveRandom()
{
  if (graph != NULL)
  {
    delete graph;
  }
}

edaMoveGen *tspTwoOptMoveRandom::clone() const
{
  return new tspTwoOptMoveRandom(*(this->graph));
}

bool tspTwoOptMoveRandom::generate(edaMove *move, const edaSolution &sol)
{
  tspTwoOpt *tspmove = (tspTwoOpt *)move;
  tspmove->first = rnd.random(graph->size() - 3);
  tspmove->second = tspmove->first + 2 + rnd.random(graph->size() - tspmove->first - 3);

  return true;
}

void tspTwoOptMoveRandom::Serialize(edaBuffer &buf, bool pack)
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
