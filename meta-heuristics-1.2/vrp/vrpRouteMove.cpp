#include "vrpRouteMove.h"
#include "vrpSolution.h"

vrpRouteMove::vrpRouteMove()
	:edaMove(){
    INC_DIST = INC_WAIT_TIME = INC_MOVE_TIME = 0;
}
vrpRouteMove::vrpRouteMove(const vrpRouteMove &move):
	edaMove(move)
{
	ID_SUB_1 = move.ID_SUB_1;
	ID_SUB_2 = move.ID_SUB_2;
	NUM_OPT_1 = move.NUM_OPT_1;
	NUM_OPT_2 = move.NUM_OPT_2;
	POS_OPT_1 = move.POS_OPT_1;
	POS_OPT_2 = move.POS_OPT_2;
	INC_DIST = move.INC_DIST;
	INC_WAIT_TIME = move.INC_WAIT_TIME;
	INC_MOVE_TIME = move.INC_MOVE_TIME;
}

vrpRouteMove::~vrpRouteMove() {}

edaMove* vrpRouteMove::clone() const {
	return new vrpRouteMove(*this);
}

void vrpRouteMove::init(const edaSolution &sol) {
	POS_OPT_1 = 1;
	POS_OPT_2 = 0;
	ID_SUB_1 = 0;
	ID_SUB_2 = 1;
	NUM_OPT_1 = 0;
	NUM_OPT_2 = 1;
	INC_DIST = 0.0;
	INC_WAIT_TIME = 0.0;
	INC_MOVE_TIME = 0.0;	
};
	
double vrpRouteMove::incrEval(const edaSolution &sol) const {
	vrpRoute& vrpSol = (vrpRoute&)sol;
    double result = vrpSol.evaluate();
	if(POS_OPT_2 == 0) return result;
    vrpConst C = *vrpSol.getParameter(); 
	result -= C.THETA_1*INC_DIST + C.THETA_2*INC_MOVE_TIME + C.THETA_3*INC_WAIT_TIME;
	return result;
}
void vrpRouteMove::update( edaSolution &sol ) const {
  	if(POS_OPT_2 == 0) return;
    vrpRoute& vrpSol = (vrpRoute&) sol;	
	vrpSubRoute* sub_1 = vrpSol.at(ID_SUB_1);
	vrpSubRoute* sub_2 = vrpSol.at(ID_SUB_2);
    vector<unsigned int> list_1 = sub_1->removeStop(POS_OPT_1,NUM_OPT_1);
    vector<unsigned int> list_2 = sub_2->removeStop(POS_OPT_2,NUM_OPT_2);
    sub_1->insertStop(list_2, POS_OPT_1);
    sub_2->insertStop(list_1, POS_OPT_2);
    vrpSol.update();
}

void vrpRouteMove::Serialize( edaBuffer &buf, bool pack )
{
//    edaMove::Serialize(buf,pack);
    if (pack){
        buf.Pack( &ID_SUB_1, 1 );
        buf.Pack( &ID_SUB_2, 1 );
        buf.Pack( &NUM_OPT_1, 1 );
        buf.Pack( &NUM_OPT_2, 1 );
        buf.Pack( &POS_OPT_1, 1 );
        buf.Pack( &POS_OPT_2, 1 );
        buf.Pack( &INC_DIST, 1 );
        buf.Pack( &INC_WAIT_TIME, 1 );
        buf.Pack( &INC_MOVE_TIME, 1 );
    } 
    else {
        buf.UnPack( &ID_SUB_1, 1 );
        buf.UnPack( &ID_SUB_2, 1 );
        buf.UnPack( &NUM_OPT_1, 1 );
        buf.UnPack( &NUM_OPT_2, 1 );
        buf.UnPack( &POS_OPT_1, 1 );
        buf.UnPack( &POS_OPT_2, 1 );
        buf.UnPack( &INC_DIST, 1 );
        buf.UnPack( &INC_WAIT_TIME, 1 );
        buf.UnPack( &INC_MOVE_TIME, 1 );
    }
}

edaMove& vrpRouteMove::operator = (const edaMove &_move) {
	 this->POS_OPT_1 = ((vrpRouteMove&)_move).POS_OPT_1;
	 this->POS_OPT_2 = ((vrpRouteMove&)_move).POS_OPT_2;
	 this->ID_SUB_1 = ((vrpRouteMove&)_move).ID_SUB_1;
	 this->ID_SUB_2 = ((vrpRouteMove&)_move).ID_SUB_2;
	 this->NUM_OPT_1 = ((vrpRouteMove&)_move).NUM_OPT_1;
	 this->NUM_OPT_2 = ((vrpRouteMove&)_move).NUM_OPT_2; 
	 this->INC_DIST = ((vrpRouteMove&)_move).INC_DIST;
	 this->INC_MOVE_TIME = ((vrpRouteMove&)_move).INC_MOVE_TIME;
	 this->INC_WAIT_TIME = ((vrpRouteMove&)_move).INC_WAIT_TIME;
	 return (*this);
}

bool vrpRouteMove::operator == (const edaMove &_move) const {
    return this->POS_OPT_1 == ((vrpRouteMove&)_move).POS_OPT_1
        && this->POS_OPT_2 == ((vrpRouteMove&)_move).POS_OPT_2
        && this->ID_SUB_1 == ((vrpRouteMove&)_move).ID_SUB_1
        && this->ID_SUB_2 == ((vrpRouteMove&)_move).ID_SUB_2
        && this->NUM_OPT_1 == ((vrpRouteMove&)_move).NUM_OPT_1
        && this->NUM_OPT_2 == ((vrpRouteMove&)_move).NUM_OPT_2;
}

void vrpRouteMove::printOn(ostream &os) const {
    os << "Subroute [" << ID_SUB_1 << "," << ID_SUB_2
       << "] Operation [" << NUM_OPT_1 << ","
       << NUM_OPT_2 << "], Position [" << POS_OPT_1
       << "," << POS_OPT_2 <<"]";	
} 

	
