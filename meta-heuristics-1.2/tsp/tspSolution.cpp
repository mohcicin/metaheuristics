
#include "graph.h"

#include <iostream>
#include <iterator>
#include <sstream>

#include "tspSolution.h"

tspSolution::tspSolution()
  : graph(NULL), cost(NAN) {}

tspSolution::tspSolution(const Graph &_graph) 
 : graph(_graph.clone()), cost(NAN) {}

void tspSolution::init() {
  unsigned int size = graph->size();
  if(graph != NULL) {
//    printDebug(4, "Graph size: " << graph->size());
    for (unsigned int i = 0; i < size; i++) {
      push_back(i);
    }
    // Swap cities
    for (unsigned int i = 0; i < size; i++) {
      unsigned int j = rnd.random(size);

      // Swap
      unsigned int city = (*this)[i];
      (*this)[i] = (*this)[j];
      (*this)[j] = city;
    }
  }
  else {
    cerr << "The graph doesn't exist!" << endl;
    exit(1);
  }
}
tspSolution::tspSolution(const tspSolution &sol)
  : vector<unsigned int>(sol), 
    graph(sol.graph->clone()), 
    cost(NAN) {}

tspSolution::~tspSolution() {
  easer();
}

edaSolution* tspSolution::clone() const {
  return new tspSolution(*this);
}

double tspSolution::evaluate() {
  if(this->size() < graph->size()) {
    cerr << "The solution is not initialized !" << endl;
    exit(1);
  }
  if ( cost != cost  ) {
    cost = .0;
    unsigned graphSize = graph->size();
    for (unsigned int i = 0; i < graphSize; i++) {
      cost -= graph->distance( (*this)[i], (*this)[(i + 1) % graphSize]);
    }
  }
  return cost;
}

double tspSolution::getCost() const {
  return cost;
}

void tspSolution::Serialize( edaBuffer &buf, bool pack ) {
  if (pack) {
    // Pack the Graph
    graph->doSerialize(buf, pack);
    
    // then pack the vector
    unsigned _size = this->size();
    buf.Pack(&_size, 1);

    vector<unsigned int>::iterator iter;
    for (iter = this->begin(); iter != this->end(); iter++) {
      buf.Pack((unsigned int *) &(*iter), 1);
    }
    
    //Pack the Cost
    buf.Pack(&cost, 1);
  }
  else {
    easer();
    
    // Unpack the Graph
    graph = (Graph*) classGenerateFromBuffer(buf);
    
    // then unpack the vector
    unsigned int _size;
    buf.UnPack(&_size, 1);
    this->resize(_size);

    for (unsigned int i = 0; i < _size; i++) {
      int atom;
      buf.UnPack((int *) &atom, 1);
      (*this)[i] = atom;
    }
    
    //UnPack the Cost
    buf.UnPack(&cost, 1);
  }
}

void tspSolution::printOn(ostream &os) const {
  copy( (*this).begin(), (*this).end(), ostream_iterator<int>( os, " " ) );
}

edaSolution& tspSolution::operator = (const edaSolution &sol) {
  easer();
  tspSolution& tspSol = (tspSolution&) sol;  
  vector<unsigned int>::operator = (tspSol);
  graph = tspSol.graph->clone();
  cost = tspSol.cost;
  return (*this);
}

bool tspSolution::operator == (const edaSolution &sol) const {
  return (vector<unsigned int>) 
          (*this) == (vector<unsigned int>) 
          (*((tspSolution *) &sol));
}

void tspSolution::easer() {
  if (graph != NULL) {
    delete graph;
  }
  graph = NULL;
  this->clear();
}

void tspSolution::setCost(double value) {
  cost = value;
}


void tspSolution::save(const char* filename) {
    ofstream file;
    file.open(filename);
    unsigned int size = this->size();
    for(unsigned int i = 0; i < size; i++)
        file << graph->x(at(i)) << " ";
    file << endl;
    for(unsigned int i = 0; i < size; i++)
        file << graph->y(at(i)) << " ";
    file.close();
}