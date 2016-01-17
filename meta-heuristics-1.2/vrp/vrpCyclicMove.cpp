#include "vrpCyclicMove.h"
#include "vrpSolution.h"

vrpCyclicMove::vrpCyclicMove()
	:edaMove()
{
  INC_DIST = INC_WAIT_TIME = INC_MOVE_TIME = 0;
}

vrpCyclicMove::vrpCyclicMove(const vrpCyclicMove &move)
  : edaMove(move) {
    unsigned int size = move.POS_OPT.size();
    ID_SUB.resize(size);
    POS_OPT.resize(size);
    NUM_OPT.resize(size);
    for(unsigned int i = 0; i < size; i++) {      
      POS_OPT[i] = move.POS_OPT[i];
      ID_SUB[i] = move.ID_SUB[i];
      NUM_OPT[i] = move.NUM_OPT[i];
    }
    INC_DIST = move.INC_DIST;
    INC_MOVE_TIME = move.INC_MOVE_TIME;
    INC_WAIT_TIME = move.INC_WAIT_TIME;
}

vrpCyclicMove::~vrpCyclicMove()
{
  easer();
}

edaMove* vrpCyclicMove::clone() const
{
    return new vrpCyclicMove(*this);
}

void vrpCyclicMove::init(const edaSolution &sol)
{
    vrpSolution& vrpSol = (vrpSolution&) sol;
    unsigned int size = vrpSol.size();
    ID_SUB.clear(); POS_OPT.clear(); NUM_OPT.clear();
    for(unsigned int i = 0 ; i < size ; i ++)
    {
        ID_SUB.push_back(0);
        POS_OPT.push_back(1);
        NUM_OPT.push_back(0);
    }	
}
	
double vrpCyclicMove::incrEval(const edaSolution &sol) const
{    
    vrpSolution & vrpSol = (vrpSolution&) sol;
    double result = vrpSol.evaluate();
    vrpConst& C = *vrpSol.getParameter(); 
    result -= C.THETA_1*INC_DIST + C.THETA_2*INC_MOVE_TIME + C.THETA_3*INC_WAIT_TIME;
    return result;	
}

void vrpCyclicMove::update( edaSolution &sol ) const
{
    vrpSolution & vrpSol = (vrpSolution&) sol;	
    unsigned int size = vrpSol.size();
    vector<unsigned int> list;
    for(unsigned int i = 0; i < size; i++ )	
    {
      vrpRoute* route = vrpSol[i];
      vrpSubRoute* sub = route->at( ID_SUB[i] );
      sub->insertStop(list, POS_OPT[i]);
      list = sub->removeStop( POS_OPT[i] + list.size(), NUM_OPT[i] );
    }
    vrpSol[0]->at( ID_SUB[0] )->insertStop(list, POS_OPT[0]);
    vrpSol.update();	
}

void vrpCyclicMove::Serialize( edaBuffer &buf, bool pack )
{
  if (pack)
  {
    unsigned int size = POS_OPT.size();
    buf.Pack(&size, 1);
    for(unsigned int i = 0; i < size; i++) {
      buf.Pack(&ID_SUB[i], 1);
      buf.Pack(&POS_OPT[i], 1);
      buf.Pack(&NUM_OPT[i], 1);
    }
    buf.Pack(&INC_DIST, 1);
    buf.Pack(&INC_MOVE_TIME, 1);
    buf.Pack(&INC_WAIT_TIME, 1);
  }
  else 
  {
    easer();
    unsigned int size;
    buf.UnPack(&size, 1);
    ID_SUB.resize(size);
    POS_OPT.resize(size);
    NUM_OPT.resize(size);
    for(unsigned int i = 0; i < size; i++) {      
      buf.UnPack(&ID_SUB[i], 1);
      buf.UnPack(&POS_OPT[i], 1);
      buf.UnPack(&NUM_OPT[i], 1);
    }
    buf.UnPack(&INC_DIST, 1);
    buf.UnPack(&INC_MOVE_TIME, 1);
    buf.UnPack(&INC_WAIT_TIME, 1);
  }
}

edaMove& vrpCyclicMove::operator = (const edaMove &_move)
{
  easer();
  vrpCyclicMove& move = (vrpCyclicMove&)_move;
  unsigned int size = move.POS_OPT.size();
  ID_SUB.resize(size);
  POS_OPT.resize(size);
  NUM_OPT.resize(size);
  for(unsigned int i = 0; i < size; i++) {      
    POS_OPT[i] = move.POS_OPT[i];
    ID_SUB[i] = move.ID_SUB[i];
    NUM_OPT[i] = move.NUM_OPT[i];
  }

  INC_DIST = move.INC_DIST;
  INC_MOVE_TIME = move.INC_MOVE_TIME;
  INC_WAIT_TIME = move.INC_WAIT_TIME;
  return (*this);
}

bool vrpCyclicMove::operator == (const edaMove &_move) const
{
  vrpCyclicMove& M = (vrpCyclicMove&)_move;
  unsigned int size = POS_OPT.size();
  if( size != M.POS_OPT.size() )
    return false;
  for(unsigned int i = 0; i < size; i++) 
  {
    if(POS_OPT[i] != M.POS_OPT[i] || ID_SUB[i] != M.ID_SUB[i] || NUM_OPT[i] != M.NUM_OPT[i] )
      return false;
  }
  return true;       
}

void vrpCyclicMove::printOn(ostream& os) const
{
  for(unsigned int i = 0; i < POS_OPT.size(); i++) {
    os << "[" << ID_SUB[i] << ", " << POS_OPT[i] << ", " << NUM_OPT[i] << "] ";
  }
} 


void vrpCyclicMove::easer() {
  ID_SUB.clear();
  POS_OPT.clear();
  NUM_OPT.clear();
}
