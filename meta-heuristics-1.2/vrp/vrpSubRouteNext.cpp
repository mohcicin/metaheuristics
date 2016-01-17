#include "vrpSubRouteNext.h"
#include "vrpSolution.h"
#include "vrpSubRouteMove.h"

/*
 *	Constructor
 */
vrpSubRouteNext::vrpSubRouteNext():edaMoveGen() {
    _problem = NULL;
}
vrpSubRouteNext::vrpSubRouteNext(vrpProblem* problem) {
    _problem = problem;
}
vrpSubRouteNext::vrpSubRouteNext(const vrpSubRouteNext &move) {
    _problem = move._problem;
}
vrpSubRouteNext::~vrpSubRouteNext() {
    _problem = NULL;
}

edaMoveGen* vrpSubRouteNext::clone() const {
    return new vrpSubRouteNext(*this);
}

bool vrpSubRouteNext::isFeasibleMove(vrpSubRouteMove* move,vrpSubRoute* sub) {    
  vrpSubRouteMove& M = *move;
	if(M.POS_OPT_1 + M.NUM_OPT_1 >= M.POS_OPT_2 ||
            M.POS_OPT_2 + M.NUM_OPT_2 > sub->size() - 2)	
		return false;    

  vrpSubRoute* mySub = sub->clone();    
  vector<unsigned int> list_2 = mySub->removeStop(M.POS_OPT_2,M.NUM_OPT_2);
  vector<unsigned int> list_1 = mySub->removeStop(M.POS_OPT_1,M.NUM_OPT_1);
  mySub->insertStop(list_2, M.POS_OPT_1);
  mySub->insertStop(list_1, M.POS_OPT_2 + M.NUM_OPT_2 - M.NUM_OPT_1); 
	if(mySub->isViolatation()) {
        delete mySub;
		return false;		
	}
	M.INC_DIST = mySub->getTotalMoveDist() - sub->getTotalMoveDist();
	M.INC_MOVE_TIME = mySub->getTotalMoveTime() - sub->getTotalMoveTime();
	M.INC_WAIT_TIME = mySub->getTotalWaitTime() - sub->getTotalWaitTime();
    delete mySub;
	return true;
}

/*
 * 	Virtual function from edaMoveGen
 */
bool vrpSubRouteNext::generate(edaMove *move, const edaSolution &sol) {
    vrpSubRouteMove& M = *((vrpSubRouteMove*) move);
    vrpSubRoute& mySub = (vrpSubRoute&)sol;
    int size = mySub.size();
    START:    
    if(M.NUM_OPT_2 < 2)
    	M.NUM_OPT_2++ ;
    else {
    	M.NUM_OPT_2 = 0;
    	if(M.NUM_OPT_1 < 2)    	
    		M.NUM_OPT_1++;
    	else {
    		M.NUM_OPT_1 = 0;
    		M.NUM_OPT_2 = 1;
    		if( (int)M.POS_OPT_2 < size - 2)
                M.POS_OPT_2++;
    		else {
    			if( (int)M.POS_OPT_1 < size - 4) {
    				M.POS_OPT_1++ ;
    				M.POS_OPT_2 = M.POS_OPT_1 + 1;
    			}
                else 
                    return false;                   			
            }
        }
    } 
    if (!isFeasibleMove(&M,&mySub) ) {       
        goto START;
    }
    else {
        return true;
    }
}


void vrpSubRouteNext::Serialize(edaBuffer &buf, bool pack)
{
    edaMoveGen::Serialize(buf,pack);
    if ( pack ){
        _problem->doSerialize( buf, pack );
    } else {
    if (_problem != NULL) delete _problem;
        _problem = (vrpProblem*)classGenerateFromBuffer(buf);
    }
}
    
