#include <iostream>
#include "tspSolution.h"
#include "tspOrOpt.h"

tspOrOpt::tspOrOpt(unsigned int lambda)
  : edaMove(), LAMBDA(lambda), graph (NULL)
{
}

tspOrOpt::tspOrOpt(const Graph &graph, unsigned int lambda)
  : edaMove(), LAMBDA(lambda), graph(graph.clone())
{
}

tspOrOpt::tspOrOpt(const tspOrOpt &move) : edaMove(move)
{
  graph = move.graph->clone();
  LAMBDA = move.LAMBDA;
  FIRST = move.FIRST;
  SECOND = move.SECOND;
}

tspOrOpt::~tspOrOpt()
{
  if (graph != NULL)
  {
    delete graph;
  }
}

edaMove* tspOrOpt::clone() const
{
  return new tspOrOpt(*this);
}

void tspOrOpt::init(const edaSolution &sol)
{
  FIRST = 1;
  SECOND = FIRST + LAMBDA;
}

double tspOrOpt::incrEval(const edaSolution &sol) const
{
  tspSolution &route = (tspSolution &) sol;

  unsigned int v1 = route[FIRST];   
  unsigned int v1_prev = route[FIRST - 1];  
  unsigned int v_lambda = route[FIRST + LAMBDA - 1];
  unsigned int v_lambda_next = route[FIRST + LAMBDA];
  unsigned int v2 = route[SECOND];
  unsigned int v2_next = route[ SECOND + 1 ];
//  cout << "- (" << v1_prev << ", " << v1 << ") " << endl;
//  cout << "- (" << v_lambda << ", " << v_lambda_next << ") " << endl;
//  cout << "- (" << v2 << ", " << v2_next << ") " << endl;
//  cout << "+ (" << v1_prev << ", " << v_lambda_next << ") " << endl;
//  cout << "+ (" << v2 << ", " << v1 << ") " << endl;
//  cout << "+ (" << v_lambda << ", " << v2_next << ") " << endl;
  return route.evaluate() 
    + graph->distance(v1_prev, v1)
    + graph->distance(v_lambda , v_lambda_next) 
    + graph->distance(v2, v2_next)
    - graph->distance(v1_prev, v_lambda_next)
    - graph->distance(v2, v1)
    - graph->distance(v_lambda, v2_next);
}

void tspOrOpt::update( edaSolution &sol ) const
{
  tspSolution &tspsol = (tspSolution &)sol;  
//  cout << "[Route] " << tspsol << ":" << tspsol.evaluate() << endl;
//  cout << LAMBDA << "-OrOpt [" << FIRST << ", " << SECOND << "]: " << incrEval(sol) << endl;
  vector<unsigned int> seq_cities;

  for (unsigned int i = 0; i < FIRST; i++)
    seq_cities.push_back( tspsol[i] );
  for (unsigned int i = FIRST + LAMBDA; i <= SECOND; i++)
    seq_cities.push_back( tspsol[i] );
  for (unsigned int i = FIRST; i < FIRST + LAMBDA; i++)
    seq_cities.push_back( tspsol[i] );
  for (unsigned int i = SECOND + 1; i < tspsol.size(); i++)
    seq_cities.push_back( tspsol[i] );
  for (unsigned int i = 0; i < tspsol.size(); i++)
    tspsol[i] = seq_cities[i];
  
//  cout << "[Route] " << tspsol << ":" << tspsol.evaluate() << endl;
  // request the re-evaluation of fitness
  tspsol.setCost(NAN);  
}

void tspOrOpt::Serialize( edaBuffer &buf, bool pack )
{
  if ( pack )
  {
    graph->doSerialize(buf, pack);
    buf.Pack(&LAMBDA);
  }
  else
  {
    easer();
    graph = (Graph *)classGenerateFromBuffer(buf);
    buf.UnPack(&LAMBDA);
  }
}

edaMove& tspOrOpt::operator = (const edaMove& _move)
{
  FIRST = ((tspOrOpt&)_move).FIRST;
  SECOND = ((tspOrOpt&)_move).SECOND;
  LAMBDA = ((tspOrOpt&)_move).LAMBDA;
  return (*this);
}

bool tspOrOpt::operator == (const edaMove &_move) const
{
  tspOrOpt& move = (tspOrOpt&)_move;  
  if( LAMBDA == move.LAMBDA && FIRST == move.FIRST 
          && SECOND == move.SECOND)
    return true;
  return false;
}

void tspOrOpt::printOn( ostream &os ) const
{
  os << "[" << this->FIRST << "," << this->SECOND 
         << ", " << this->LAMBDA << "]";
}

void tspOrOpt::easer() {
  if (graph != NULL)
  {
    delete graph;
    graph = NULL;
  } 
}

