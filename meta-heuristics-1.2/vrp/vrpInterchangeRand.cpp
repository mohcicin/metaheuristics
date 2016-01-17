#include "vrpInterchangeRand.h"

#include "vrpRoute.h"
#include <cstdlib> //for random
/*
 *	Constructor
 */

vrpInterchangeRand::vrpInterchangeRand(){
    _problem = NULL;
    lambda = 2;
}

vrpInterchangeRand::vrpInterchangeRand(vrpProblem* problem, unsigned int _lambda) {
  _problem = problem;
  lambda = _lambda;
}
vrpInterchangeRand::vrpInterchangeRand(const vrpInterchangeRand &orig) {
  _problem = orig._problem;
  lambda = orig.lambda;
}

vrpInterchangeRand::~vrpInterchangeRand() {
  _problem = NULL;
}

edaMoveGen* vrpInterchangeRand::clone() const {
  return new vrpInterchangeRand(*this);
}

bool vrpInterchangeRand::isFeasibleMove(vrpSolution* vrpSol, vrpInterchangeMove* move) {
    bool result = false;
    vector<unsigned int> list_1, list_2;

    vrpInterchangeMove& M = *move;    

    vrpRoute* route1 = vrpSol->at(M.ID_ROUTE_1)->clone();
    vrpRoute* route2 = vrpSol->at(M.ID_ROUTE_2)->clone();


    vrpSubRoute* sub1 = route1->at(M.ID_SUB_1);
    vrpSubRoute* sub2 = route2->at(M.ID_SUB_2); 
    if(M.POS_OPT_1 + M.NUM_OPT_1 > sub1->size() - 2
        || M.POS_OPT_2 + M.NUM_OPT_2 > sub2->size() - 2) goto FINISH;	    
    if(_problem->getStop(sub1->at(M.POS_OPT_1))->Type != REGULAR_STOP) goto FINISH;   
    if(_problem->getStop(sub1->at(M.POS_OPT_1 + M.NUM_OPT_1 - 1))->Type != REGULAR_STOP) goto FINISH;
    if(_problem->getStop(sub2->at(M.POS_OPT_2))->Type != REGULAR_STOP) goto FINISH;
    if(_problem->getStop(sub2->at(M.POS_OPT_2 + M.NUM_OPT_2 - 1))->Type != REGULAR_STOP)goto FINISH;  
    
    list_1 = sub1->removeStop(M.POS_OPT_1, M.NUM_OPT_1);
    list_2 = sub2->removeStop(M.POS_OPT_2, M.NUM_OPT_2);
    sub1->insertStop(list_2, M.POS_OPT_1);
    sub2->insertStop(list_1, M.POS_OPT_2);    
    route1->update(); route2->update();
    
    if(route1->getTotalMoveDist() > _problem->getMaxTotalDist() || 
            route2->getTotalMoveDist() > _problem->getMaxTotalDist() ) goto FINISH;
    
    if(sub1->isViolatation() ||
        sub2->isViolatation()) goto FINISH;
    
    M.INC_DIST = route1->getTotalMoveDist() - vrpSol->at(M.ID_ROUTE_1)->getTotalMoveDist() 
            + route2->getTotalMoveDist() - vrpSol->at(M.ID_ROUTE_2)->getTotalMoveDist() ;
    
    M.INC_MOVE_TIME = route1->getTotalMoveTime() - vrpSol->at(M.ID_ROUTE_1)->getTotalMoveTime() 
                + route2->getTotalMoveTime() - vrpSol->at(M.ID_ROUTE_2)->getTotalMoveTime();

    M.INC_WAIT_TIME = route1->getTotalWaitTime() - vrpSol->at(M.ID_ROUTE_1)->getTotalWaitTime()
                  + route2->getTotalWaitTime() - vrpSol->at(M.ID_ROUTE_2)->getTotalWaitTime();    
    result = true;
    
FINISH:   
	delete route1;
	delete route2;   
	return result;
}

/*
 * 	Virtual function from edaMoveGen
 */
//bool vrpInterchangeRand::generate(edaMove *move, const edaSolution &sol) {	
//        vrpInterchangeMove &M = *(vrpInterchangeMove*)move;
//	vrpSolution &mySol = (vrpSolution&)sol; 
//	unsigned int count = 0;
//	
//START:
//	if(count++ > 9999) return false;
//    
//	M.ID_ROUTE_1 = M.ID_ROUTE_2 = 0;
//	while(M.ID_ROUTE_1 == M.ID_ROUTE_2)	{
//            M.ID_ROUTE_1 = rnd.random( mySol.size() - 1);
//            M.ID_ROUTE_2 = rnd.random( mySol.size() - 1);
//	}	
//	vrpRoute* route1 = mySol[M.ID_ROUTE_1];
//	vrpRoute* route2 = mySol[M.ID_ROUTE_2];
//
//	M.ID_SUB_1 = rnd.random( route1->size() - 1);
//	M.ID_SUB_2 = rnd.random( route2->size() - 1);
//	
//	vrpSubRoute* sub1 = route1->at(M.ID_SUB_1);
//	vrpSubRoute* sub2 = route2->at(M.ID_SUB_2);
//	
//        M.NUM_OPT_1 =  M.NUM_OPT_2 = 0;
//	while( M.NUM_OPT_1 ==  M.NUM_OPT_2) {
//            M.NUM_OPT_1 = rnd.random(lambda);
//            M.NUM_OPT_2 = rnd.random(lambda);
//	}
//	
//	unsigned int len1 = sub1->size();
//	unsigned int len2 = sub2->size();
//
//	if(M.ID_SUB_1 == route1->size() - 1) len1 --;	
//	if(M.ID_SUB_2 == route2->size() - 1) len2 --;
//	if(len1 <= 2 || len2 <= 2)  goto START;    
//	M.POS_OPT_1 = rnd.random (1, len1 - 2);
//	M.POS_OPT_2 = rnd.random (1, len2 - 2);
//        
//	if( ! isFeasibleMove(&mySol, &M)) 
//          goto START;	
//	else 
//          return true;
//}

bool vrpInterchangeRand::generate(edaMove *move, const edaSolution &sol) {    
    vrpInterchangeMove& M = *((vrpInterchangeMove*)move);
    vrpSolution &vrpSol = (vrpSolution&)sol; 
    if(vrpSol.size() < 2) return false;

    vrpRoute* route1 = NULL;
    vrpRoute* route2 = NULL;
    vrpSubRoute* sub1 = NULL;
    vrpSubRoute* sub2 = NULL;

START:
    
  route1 = vrpSol[M.ID_ROUTE_1];
  route2 = vrpSol[M.ID_ROUTE_2];
  if(route1 == NULL || route2 == NULL) return false;  

  sub1 = route1->at(M.ID_SUB_1);
  sub2 = route2->at(M.ID_SUB_2);
  if(sub1 == NULL || sub2 == NULL ) return false;

  int len1 = sub1->size();
  int len2 = sub2->size();
  if(M.ID_SUB_1 == route1->size() - 1) len1 --;
  if(M.ID_SUB_2 == route2->size() - 1) len2 --;

  if((int)(M.POS_OPT_2 + M.NUM_OPT_2)  < len2 - 2) 
  {
    M.POS_OPT_2 ++;    
  } 
  else 
  {
    M.POS_OPT_2 = 1;
    if((int)(M.POS_OPT_1 + M.NUM_OPT_1) < len1 - 2)
    {
      M.POS_OPT_1++;
    } 
    else 
    {
      M.POS_OPT_1 = 1;
      if(M.NUM_OPT_2 < lambda) 
      {
        M.NUM_OPT_2++;
      } 
      else 
      {
        if(M.NUM_OPT_1 < lambda) 
        {
          M.NUM_OPT_1++;
          M.NUM_OPT_2 = 0;
        } 
        else 
        {
          M.NUM_OPT_1 = 0;
          M.NUM_OPT_2 = 1;
          if(M.ID_SUB_2 < route2->size() - 1) 
          {
            M.ID_SUB_2++;
          } 
          else 
          {
            M.ID_SUB_2 = 0;
            if(M.ID_SUB_1  < route1->size() -1) 
            {
              M.ID_SUB_1++;
            } 
            else 
            {
              M.ID_SUB_1 = 0;
              if ( M.ID_ROUTE_2 < vrpSol.size() - 1) 
              {
                M.ID_ROUTE_2++;
              } 
              else 
              {
                if(M.ID_ROUTE_1 < vrpSol.size() - 2) 
                {
                  M.ID_ROUTE_1 ++;
                  M.ID_ROUTE_2 = M.ID_ROUTE_1 + 1;
                } 
                else 
                {                
                  return false;
                }                
              }                          
            }          
          }                  
        }      
      }          
    }
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

void vrpInterchangeRand::Serialize(edaBuffer &buf, bool pack)
{
    edaMoveGen::Serialize(buf,pack);
    if (pack) {
        buf.Pack( &lambda, 1 );
        _problem->doSerialize( buf, pack );

    }
    else {
        buf.UnPack( &lambda, 1 );
        if (_problem != NULL) delete _problem;
        _problem = (vrpProblem*)classGenerateFromBuffer( buf );
    }
}
