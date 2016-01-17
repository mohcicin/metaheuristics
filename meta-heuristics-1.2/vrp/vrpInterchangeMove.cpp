/* 
 * File:   vrpInterchangeMove.cpp
 * Author: Tieu Minh
 * 
 * Created on July 3, 2012, 3:49 PM
 */

#include "vrpInterchangeMove.h"

vrpInterchangeMove::vrpInterchangeMove()
	:edaMove() {
    INC_DIST = INC_WAIT_TIME = INC_MOVE_TIME = 0;
}
vrpInterchangeMove::vrpInterchangeMove(const vrpInterchangeMove &move):
	edaMove(move)
{
  ID_ROUTE_1 = move.ID_ROUTE_1;
  ID_ROUTE_2 = move.ID_ROUTE_2;
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

vrpInterchangeMove::~vrpInterchangeMove() {}

edaMove* vrpInterchangeMove::clone() const {
	return new vrpInterchangeMove(*this);
}

void vrpInterchangeMove::init(const edaSolution &sol) {
  POS_OPT_1 = 1;
  POS_OPT_2 = 0;
  ID_SUB_1 = 0;
  ID_SUB_2 = 0;
  ID_ROUTE_1 = 0;
  ID_ROUTE_2 = 1;
  NUM_OPT_1 = 0;
  NUM_OPT_2 = 1;
  INC_DIST = 0.0;
  INC_WAIT_TIME = 0.0;
  INC_MOVE_TIME = 0.0;
};
	
double vrpInterchangeMove::incrEval(const edaSolution &sol) const {   
  vrpSolution& vrpSol = (vrpSolution&)sol;
  double result = vrpSol.evaluate();
  if(POS_OPT_2 == 0) return result;
  vrpConst& C = *vrpSol.getParameter(); 
  result -= C.THETA_1*INC_DIST + C.THETA_2*INC_MOVE_TIME + C.THETA_3*INC_WAIT_TIME;
  return result;
}

void vrpInterchangeMove::update( edaSolution &sol ) const {
  if(POS_OPT_2 == 0) return;
  vrpSolution& vrpSol = (vrpSolution&) sol;
  vrpRoute* route_1 = vrpSol[ID_ROUTE_1];
	vrpRoute* route_2 = vrpSol[ID_ROUTE_2];
	vrpSubRoute* sub_1 = route_1->at(ID_SUB_1);
	vrpSubRoute* sub_2 = route_2->at(ID_SUB_2);
  vector<unsigned int> list_1 = sub_1->removeStop(POS_OPT_1, NUM_OPT_1);
  vector<unsigned int> list_2 = sub_2->removeStop(POS_OPT_2, NUM_OPT_2);
  sub_1->insertStop(list_2, POS_OPT_1);
  sub_2->insertStop(list_1, POS_OPT_2);	
  vrpSol.update();
}

void vrpInterchangeMove::Serialize( edaBuffer &buf, bool pack )
{
    if (pack){
        buf.Pack( &ID_ROUTE_1, 1 );
        buf.Pack( &ID_ROUTE_2, 1 );
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
        buf.UnPack( &ID_ROUTE_1, 1 );
        buf.UnPack( &ID_ROUTE_2, 1 );
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

edaMove& vrpInterchangeMove::operator = (const edaMove &_move) {	
    this->POS_OPT_1 = ((vrpInterchangeMove&)_move).POS_OPT_1;
    this->POS_OPT_2 = ((vrpInterchangeMove&)_move).POS_OPT_2;
    this->ID_ROUTE_1 = ((vrpInterchangeMove&)_move).ID_ROUTE_1;
    this->ID_ROUTE_2 = ((vrpInterchangeMove&)_move).ID_ROUTE_2;
    this->ID_SUB_1 = ((vrpInterchangeMove&)_move).ID_SUB_1;
    this->ID_SUB_2 = ((vrpInterchangeMove&)_move).ID_SUB_2;
    this->NUM_OPT_1 = ((vrpInterchangeMove&)_move).NUM_OPT_1;
    this->NUM_OPT_2 = ((vrpInterchangeMove&)_move).NUM_OPT_2; 
    this->INC_DIST = ((vrpInterchangeMove&)_move).INC_DIST;
    this->INC_MOVE_TIME = ((vrpInterchangeMove&)_move).INC_MOVE_TIME;
    this->INC_WAIT_TIME = ((vrpInterchangeMove&)_move).INC_WAIT_TIME;
    return (*this);
}

bool vrpInterchangeMove::operator == (const edaMove &_move) const
{
    return this->POS_OPT_1 == ((vrpInterchangeMove&)_move).POS_OPT_1
        && this->POS_OPT_2 == ((vrpInterchangeMove&)_move).POS_OPT_2
        && this->ID_SUB_1 == ((vrpInterchangeMove&)_move).ID_SUB_1
        && this->ID_SUB_2 == ((vrpInterchangeMove&)_move).ID_SUB_2
        && this->ID_ROUTE_1 == ((vrpInterchangeMove&)_move).ID_ROUTE_1
        && this->ID_ROUTE_2 == ((vrpInterchangeMove&)_move).ID_ROUTE_2
        && this->NUM_OPT_1 == ((vrpInterchangeMove&)_move).NUM_OPT_1
        && this->NUM_OPT_2 == ((vrpInterchangeMove&)_move).NUM_OPT_2;
}

void vrpInterchangeMove::printOn(ostream& os) const{
    os << "Route [" << ID_ROUTE_1 << "," << ID_ROUTE_2
    << "] Subroute [" << ID_SUB_1 << "," << ID_SUB_2
    << "] Operation [" << NUM_OPT_1 << ","
    << NUM_OPT_2 << "] Position [" << POS_OPT_1
    << "," << POS_OPT_2 <<"]";      
}
 


