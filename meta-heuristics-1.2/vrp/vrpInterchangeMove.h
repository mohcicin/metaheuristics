/* 
 * File:   vrpInterchangeMove.h
 * Author: Tieu Minh
 *
 * Created on July 3, 2012, 3:49 PM
 */

#ifndef VRPINTERCHANGEMOVE_H
#define	VRPINTERCHANGEMOVE_H
#include "../lib/eda.h"
#include "vrpSolution.h"
class vrpInterchangeMove: public edaMove {
public:
	vrpInterchangeMove();
	vrpInterchangeMove(const vrpInterchangeMove &move);
	~vrpInterchangeMove();
	
	edaMove* clone() const;
	void init(const edaSolution &sol);
	double incrEval(const edaSolution &sol) const;
	void update(edaSolution &sol) const;
	void Serialize( edaBuffer &buf, bool pack );
	edaMove& operator = (const edaMove &_move);
	bool operator == (const edaMove &_move) const;

	setClassID(_USERCLASSID_ + _CLSID_VRP_INTERCHANGE_MOVE_);
  void printOn(ostream& os) const;

//Properties  
  unsigned int ID_ROUTE_1;
  unsigned int ID_ROUTE_2;
  unsigned int ID_SUB_1;
  unsigned int ID_SUB_2;
  unsigned int NUM_OPT_1;
  unsigned int NUM_OPT_2;
  unsigned int POS_OPT_1;
  unsigned int POS_OPT_2;
  
  double INC_DIST;
  double INC_WAIT_TIME;
  double INC_MOVE_TIME;

};

#endif	/* VRPINTERCHANGEMOVE_H */

