#include "vrpCyclicNext.h"
#include "vrpRoute.h"

/*
 *	Constructor
 */
vrpCyclicNext::vrpCyclicNext(unsigned int _lambda)
{
  lambda = _lambda;
  problem = NULL;
}

vrpCyclicNext::vrpCyclicNext(vrpProblem *pro, unsigned int _lambda)
{
  lambda = _lambda;
  problem = pro->clone();
}

vrpCyclicNext::vrpCyclicNext(const vrpCyclicNext &m)
{
    lambda = m.lambda;
    problem = m.problem->clone();
}

vrpCyclicNext::~vrpCyclicNext()
{
  if(problem == NULL) delete problem; 
}

edaMoveGen* vrpCyclicNext::clone() const
{
  return new vrpCyclicNext(*this);
}

bool vrpCyclicNext::isFeasibleMove( const vrpSolution* vrpSol, vrpCyclicMove* move)
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
bool vrpCyclicNext::generate(edaMove *move, const edaSolution &sol)
{
  vrpCyclicMove& M = *((vrpCyclicMove*)move);
  vrpSolution &vrpSol = (vrpSolution&)sol; 
  unsigned int size = vrpSol.size();
  if( size < 2) return false;  
  
  vrpRoute* route;
  vrpSubRoute* sub;
  unsigned int sub_size, route_size;
  unsigned int index;
//  bool endSub;
  

  
START:  
  for(unsigned int i = 0; i < size; i++)
  {
    index = size - i - 1;
    route = vrpSol[index];
    route_size = route->size();
    sub = route->at(M.ID_SUB[index]);
    sub_size = sub->size();
 
    if(M.NUM_OPT[index] >= lambda )
    {
      M.NUM_OPT[index] = 0;     
    } 
    else
    {
      M.NUM_OPT[index]++;
      goto END;
    }
  }

  for(unsigned int i = 0; i < size; i++)
  { 
    index = size - i - 1;
    route = vrpSol[index];
    sub = route->at(M.ID_SUB[index]);
    sub_size = sub->size();
    route_size = route->size();
    if(M.ID_SUB[i] == route_size - 1) sub_size --; 
    if( M.POS_OPT[index] + M.NUM_OPT[index] >= sub_size ) 
    {
      M.POS_OPT[index] = 1;
    } 
    else 
    {
      M.POS_OPT[index]++;
      goto END;
    }
  }

  for(unsigned int i = 0; i < size; i++)
  { 
    index = size - i - 1;
    route = vrpSol[index];
    route_size = route->size();
    if(M.ID_SUB[index] >= route_size - 1 )
    {
      M.ID_SUB[index] = 0;  
    } 
    else 
    {
      M.ID_SUB[index]++;
      goto END;
    }
  }

  return false;
  
END:	
  if(!isFeasibleMove(&vrpSol, &M)) 
  {
    goto START;
  }
  else 
  { 
    return true;
  }

}


void vrpCyclicNext::Serialize(edaBuffer &buf, bool pack)
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
