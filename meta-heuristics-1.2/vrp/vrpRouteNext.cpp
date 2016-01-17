#include "vrpRouteNext.h"
#include "vrpSolution.h"
#include "vrpRouteMove.h"

/*
 *	Constructor
 */

vrpRouteNext::vrpRouteNext() {
    _problem = NULL;
}
vrpRouteNext::vrpRouteNext(vrpProblem* problem) {
    _problem = problem;
}
vrpRouteNext::vrpRouteNext(const vrpRouteNext &m) {
    _problem = m._problem;
}

vrpRouteNext::~vrpRouteNext() {
    _problem = NULL;
}

edaMoveGen* vrpRouteNext::clone() const {
    return new vrpRouteNext(*this);
}

bool vrpRouteNext::isFeasibleMove(vrpRouteMove* move, vrpRoute* route) {    
    bool result = false;
    double rest_dist;
    vrpRouteMove& M = *move;
    vrpSubRoute* sub_1 = route->at(M.ID_SUB_1)->clone();
    vrpSubRoute* sub_2 = route->at(M.ID_SUB_2)->clone();
    vector<unsigned int> list_1, list_2;
    
    if(M.POS_OPT_1 + M.NUM_OPT_1 >= sub_1->size() - 2 ||
            M.POS_OPT_2 + M.NUM_OPT_2 > sub_2->size() - 2) goto FINISH; 
    
    if(_problem->getStop(sub_1->at(M.POS_OPT_1))->Type != REGULAR_STOP ||
      _problem->getStop(sub_1->at(M.POS_OPT_1 + M.NUM_OPT_1 - 1))->Type != REGULAR_STOP) goto FINISH; 
    
    if(_problem->getStop(sub_2->at(M.POS_OPT_2))->Type != REGULAR_STOP ||
      _problem->getStop(sub_2->at(M.POS_OPT_2 + M.NUM_OPT_2 - 1))->Type != REGULAR_STOP) goto FINISH; 
    
    list_1 = sub_1->removeStop(M.POS_OPT_1, M.NUM_OPT_1);
    list_2 = sub_2->removeStop(M.POS_OPT_2, M.NUM_OPT_2);
    sub_1->insertStop(list_2, M.POS_OPT_1);
    sub_2->insertStop(list_1, M.POS_OPT_2);    
    
    if(sub_1->isViolatation() ||
            sub_2->isViolatation()) goto FINISH;
    
    rest_dist = _problem->getMaxTotalDist() - route->getTotalMoveDist();
    
    M.INC_DIST = sub_1->getTotalMoveDist() - route->at(M.ID_SUB_1)->getTotalMoveDist()
            + sub_2->getTotalMoveDist() - route->at(M.ID_SUB_2)->getTotalMoveDist();
        
    if(M.INC_DIST > rest_dist) goto FINISH;
    
    M.INC_MOVE_TIME = sub_1->getTotalMoveTime() - route->at(M.ID_SUB_1)->getTotalMoveTime()
                + sub_2->getTotalMoveTime() - route->at(M.ID_SUB_2)->getTotalMoveTime();

    M.INC_WAIT_TIME = sub_1->getTotalWaitTime() - route->at(M.ID_SUB_1)->getTotalWaitTime()
                + sub_2->getTotalWaitTime() - route->at(M.ID_SUB_2)->getTotalWaitTime();
    
    result = true;
    
FINISH:    
    delete sub_1;
    delete sub_2;
    return result;
}

/*
 * 	Virtual function from edaMoveGen
 */
bool vrpRouteNext::generate(edaMove *move, const edaSolution &sol) {
    vrpRouteMove& M = *((vrpRouteMove*)move);
    vrpRoute &route = (vrpRoute&)sol;
    vrpSubRoute* sub_1 ;
    vrpSubRoute* sub_2 ;
 
START:    
    if(route.size() <= 1 ) 
        return false;
    
    sub_1 = route.at(M.ID_SUB_1);
    sub_2 = route.at(M.ID_SUB_2);
    int fsize = sub_1->size();
    int ssize = sub_2->size();
    
    if(M.ID_SUB_1 == route.size() - 1) fsize -- ;
    if(M.ID_SUB_2 == route.size() - 1) ssize --;
    if((int)(M.POS_OPT_2 + M.NUM_OPT_2) < ssize - 2 ) {
        M.POS_OPT_2++;
    } 
    else {
        M.POS_OPT_2 = 1;
        if((int)(M.POS_OPT_1 + M.NUM_OPT_1) < fsize - 2) {
            M.POS_OPT_1++;
        }
        else {            
            M.POS_OPT_1  = 1;
            if(M.NUM_OPT_2 < 2 ) {
                M.NUM_OPT_2++;
            }
            else {
                M.NUM_OPT_2 = 1;
                if(M.NUM_OPT_1 < 2) {
                    M.NUM_OPT_1++;
                }
                else {
                    M.NUM_OPT_1 = 0;
                    if(M.ID_SUB_2 < route.size() - 1) {
                        M.ID_SUB_2++;
                    }
                    else {
                        if(M.ID_SUB_1 < route.size() - 2) {
                            M.ID_SUB_2 = M.ID_SUB_1 + 2;	
                            M.ID_SUB_1 = M.ID_SUB_1 + 1;
                        }
                        else {
                            return false;
                        }
                    }
                }
            }
        }
    }

    if (!isFeasibleMove(&M,&route) ) {  
         goto START;    
    }
    else {
//        cout << M << M.incrEval(route)  << endl;
        return true;
    }
}


void vrpRouteNext::Serialize(edaBuffer &buf, bool pack)
{
  	edaMoveGen::Serialize(buf,pack);
	if (pack){
        _problem->doSerialize( buf, pack );
    } 
    else {
        if (_problem != NULL) delete _problem;
        _problem = (vrpProblem*)classGenerateFromBuffer(buf);
    }
}
    
