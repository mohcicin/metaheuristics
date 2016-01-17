#include "vrpCyclicRand.h"
#include "vrpRoute.h"

/*
 *	Constructor
 */
vrpCyclicRand::vrpCyclicRand(unsigned int _lambda)
{
  lambda = _lambda;
  problem = NULL;
}

vrpCyclicRand::vrpCyclicRand(vrpProblem *pro, unsigned int _lambda)
{
  lambda = _lambda;
  problem = pro->clone();
}

vrpCyclicRand::vrpCyclicRand(const vrpCyclicRand &m)
{
    lambda = m.lambda;
    problem = m.problem->clone();
}

vrpCyclicRand::~vrpCyclicRand()
{
  if(problem == NULL) delete problem; 
}

edaMoveGen* vrpCyclicRand::clone() const
{
  return new vrpCyclicRand(*this);
}

bool vrpCyclicRand::isFeasibleMove( const vrpSolution* vrpSol, vrpCyclicMove* move)
{  
  bool result = false;
  vrpCyclicMove& M = *move;    
  vector<unsigned int> list;
  vrpSolution* tmpSol = vrpSol->clone();
  unsigned int size = tmpSol->size();

  if( rnd.sum(M.NUM_OPT) == 0 ) 
    goto FINISH;     
  
  for(unsigned int i = 0; i < size; i++)
  { 
      vrpRoute* route = vrpSol->at(i);
      vrpSubRoute* sub = route->at( M.ID_SUB[i] );
      unsigned int sub_size = sub->size();
      if(M.ID_SUB[i] == route->size() - 1) sub_size --; 
      if( M.POS_OPT[i] + M.NUM_OPT[i] >= sub_size ) 
        goto FINISH;     
  }
  
  
  for(unsigned int i = 0 ; i < size ; i++)
  {
    vrpRoute* route = tmpSol->at(i);
    vrpSubRoute* sub = route->at( M.ID_SUB[i] );    
    sub->insertStop(list, M.POS_OPT[i]);
    list = sub->removeStop( M.POS_OPT[i] + list.size(), M.NUM_OPT[i]);    
  }
  tmpSol->at(0)->at(M.ID_SUB[0])->insertStop(list, M.POS_OPT[0]);
  tmpSol->update();  
  size = tmpSol->size(); 
  for(unsigned int i = 0 ; i < size ; i++)
  {
    vrpRoute* route = tmpSol->at(i);
    vrpSubRoute* sub = route->at( M.ID_SUB[i] );
    if( route->getTotalMoveDist() > problem->getMaxTotalDist() ) 
        goto FINISH;
    if( sub->isViolatation() ) 
        goto FINISH; 
  }
  M.INC_DIST = tmpSol->getTotalDist() - vrpSol->getTotalDist();
  M.INC_MOVE_TIME = tmpSol->getTotalMoveTime() - vrpSol->getTotalMoveTime();
  M.INC_WAIT_TIME = tmpSol->getTotalWaitTime() - vrpSol->getTotalWaitTime() ;
  result = true;
  
FINISH: 
  delete tmpSol;
  return result;    	
}

/*
 * 	Virtual function from edaMoveGen
 */
bool vrpCyclicRand::generate(edaMove *move, const edaSolution &sol)
{
  vrpCyclicMove& M = *((vrpCyclicMove*)move);
  vrpSolution &vrpSol = (vrpSolution&)sol; 
  unsigned int n = vrpSol.size();
  unsigned int count = 0;
  if( n < 2) return false;  
  
  vrpRoute* route;
  vrpSubRoute* sub;
  unsigned int size, len;

  
START:  
  if(count++ > 9999) return false;
  
  for(unsigned int i = 0; i < n; i++)
  {
      route = vrpSol[i];
      size = route->size();      
      M.ID_SUB[i] = rnd.random(size);
      
      sub = route->at(M.ID_SUB[i]);
      len = sub->size();
      if(M.ID_SUB[i] == size - 1) len --; 
      
      M.NUM_OPT[i] = rnd.random(lambda);
      M.POS_OPT[i] = rnd.random(1, len - 2 - M.NUM_OPT[i]);    
  }

  if(!isFeasibleMove(&vrpSol, &M)) 
  {
    goto START;
  }
  else 
  { 
    return true;
  }
}


void vrpCyclicRand::Serialize(edaBuffer &buf, bool pack)
{
  edaMoveGen::Serialize(buf, pack);
  if (pack)
  {
    problem->doSerialize(buf, pack);
    buf.Pack(&lambda, 1);
  }
  else 
  {
    if(problem == NULL) delete problem; 
    problem = (vrpProblem*)classGenerateFromBuffer( buf );
    buf.UnPack(&lambda, 1);
  }
}
