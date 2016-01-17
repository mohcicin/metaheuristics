#include <iostream>
#include "tspSolution.h"
#include "tspKOpt.h"

tspKOpt::tspKOpt()
  : edaMove(), graph (NULL)
{
}

tspKOpt::tspKOpt(const Graph &g)
  : edaMove(), graph (new Graph(g))
{
}

tspKOpt::tspKOpt(const tspKOpt &move) : 
  pair<unsigned int, unsigned int> (move),
  edaMove(move)
{
  graph = new Graph(*(move.graph));
}

tspKOpt::~tspKOpt()
{
  if (graph != NULL)
  {
    delete graph;
  }
}

edaMove* tspKOpt::clone() const
{
  return new tspKOpt(*this);
}

void tspKOpt::init(const edaSolution &sol)
{
  this->first = 0;
  this->second = 2;
}

double tspKOpt::incrEval(const edaSolution &sol) const
{
  tspSolution &route = (tspSolution &) sol;
  unsigned int v1 = route[this->first];
  unsigned int v1_next = route[this->first + 1];
  unsigned int v2 = route[this->second];
  unsigned int v2_next = route[this->second + 1];

  return route.evaluate()
    - graph->distance(v1, v2)
    - graph->distance(v1_next, v2_next)
    + graph->distance(v1, v1_next)
    + graph->distance(v2, v2_next);
}

void tspKOpt::update( edaSolution &sol ) const
{
  tspSolution &tspsol = (tspSolution &)sol;

  vector<unsigned int> seq_cities;

  for (unsigned int i = second; i > first; i--)
  {
    seq_cities.push_back(tspsol[i]);
  }
  
  unsigned int j = 0;
  for (unsigned int i = first + 1; i <= second; i++) {
    tspsol[i] = seq_cities[j++];
  }

  // request the re-evaluation of fitness
  tspsol.setCost(NAN);
  
}

void tspKOpt::Serialize( edaBuffer &buf, bool pack )
{
  if ( pack )
  {
    graph->doSerialize(buf, pack);
  }
  else
  {
    easer();
    graph = (Graph *)classGenerateFromBuffer(buf);
  }
}

edaMove& tspKOpt::operator = (const edaMove& _move)
{
  this->first = ((tspKOpt&)_move).first;
  this->second = ((tspKOpt&)_move).second;

  return (*this);
}

bool tspKOpt::operator == (const edaMove &_move) const
{
  return (*this) == _move;
}

void tspKOpt::printOn( ostream &os ) const
{
  os << "[" << this->first << "," << this->second << "]";
}

void tspKOpt::easer() {
  if (graph != NULL)
  {
    delete graph;
  } 
  graph = NULL;
}
