#include <cstring>

#include "graph.h"
#include <strings.h>

Graph::Graph()
  : numVert(0), vectCoord(NULL) {}

Graph::Graph(const char *fileName)
  : numVert(0), vectCoord(NULL) {
    load(fileName);
}

Graph::Graph(const Graph &g) {
  
  this->numVert = g.numVert;
  
  this->vectCoord = new double[this->numVert * 2];
  memcpy(this->vectCoord, g.vectCoord, sizeof(double) * 2 * this->numVert);

}

Graph::~Graph() {
  easer(); 
}

Graph* Graph::clone() const {
  return new Graph(*this);
}

void Graph::load(const char *fileName) {
  
  ifstream f(fileName);
  cout << ">> Loading [" << fileName << "]" << endl;

  if (f) {
    
    easer();    
    f >> numVert;
     
    vectCoord = new double[numVert * 2];
    for (unsigned int i = 0; i < numVert; i++) {
      f >> vectCoord[i * 2] >> vectCoord[i *  2 + 1];
    }

    f.close();
//    computeDistances();
  }
  else {
    cerr << fileName << " doesn't exist!" << endl;
    exit(1);
  }
}

unsigned int Graph::size() const {
  return numVert;
}

float Graph::distance(unsigned int from, unsigned int to) {
  double distX = (double)(vectCoord[from * 2] - vectCoord[to * 2]);
  double distY = (double)(vectCoord[from * 2 + 1] - vectCoord[to * 2 + 1]);
  return sqrt(distX * distX + distY * distY) ; 
}

double Graph::x(unsigned int id) const {
    return vectCoord[id * 2];
}

double Graph::y(unsigned int id) const {
    return vectCoord[id * 2 + 1];
}

void Graph::easer() {
  if ( vectCoord != NULL )
    delete[] vectCoord;    
  vectCoord = NULL;
}

void Graph::Serialize(edaBuffer &buf, bool pack) {
  if (pack) {
    // First, pack the numVert
    buf.Pack(&numVert, 1);

    // And the vector coordinates
    buf.Pack(vectCoord, numVert * 2);
  }
  else {  
    easer();
    // First, unpack the numVert
    buf.UnPack(&numVert, 1);

    // And the vectCoord
    vectCoord = new double[numVert * 2];
    buf.UnPack(vectCoord, numVert * 2);

  }
}

Graph& Graph::operator = (const edaProblem &pro) {
  easer();
  Graph &g = (Graph&) pro;
  
  this->numVert = g.numVert;
  
  this->vectCoord = new double[2 * numVert];
  memcpy(this->vectCoord, g.vectCoord, numVert * 2 * sizeof(double));

  return *this;
}

void Graph::printOn(ostream &os) const {
    os << numVert << endl;
    for (unsigned int i = 0; i < numVert; i++) {
      os << vectCoord[i * 2] << "\t" << vectCoord[i *  2 + 1] << endl;
    }
}
