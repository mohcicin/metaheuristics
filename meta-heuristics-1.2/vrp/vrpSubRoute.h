/* 
 * File:   vrpSubRoute.h
 * Author: Tieu Minh
 *
 * Created on July 5, 2012, 1:23 PM
 */

#ifndef VRPSUBROUTE_H
#define	VRPSUBROUTE_H

#include <vector>
#include "../lib/eda.h"
#include "vrpDefine.h"
#include "vrpStop.h"
#include "vrpProblem.h"
#include "vrpConst.h"
class vrpSubRoute: public vector<unsigned int>, public edaSolution {
public:
  vrpSubRoute();
  vrpSubRoute(double total_res_dist, double start_time);
  vrpSubRoute(const vrpSubRoute& sub);
  vrpSubRoute *clone() const;
  virtual ~vrpSubRoute();

  void init() {}
  double evaluate() ;      
  void insertStop(unsigned int id, const unsigned int pos);   
  void insertStop(vector<unsigned int> list, const unsigned int pos);
//  void mergeSub(vrpSubRoute* sub);
  unsigned int removeStop(const unsigned int id);
  vector<unsigned int> removeStop(unsigned int pos, unsigned int count);
  bool canInsert(vrpStop* stop, const unsigned int pos) const; 
  void pushStop(vrpStop* stop);   
  void pushStop(unsigned int id); 
  void update();

  double getCost() const;
  double getTotalMoveDist() const;
  double getTotalWaitTime() const;
  double getTotalLoad() const;
  double getTotalMoveTime() const;
  double getTotalServicesTime() const;
  double getTotalUseTime() const;
  double getStartTime(unsigned int index) const;
  double getWaitTime(unsigned int index) const;
  double getAcomnLoad(unsigned int index) const;
  double getComingTime(unsigned int index) const;
  double getUseTime(unsigned int index) const;
  double getDistance(unsigned int index) const;
  double getRestDist() const;
  double getShapeMetric() const;
  double getShapeMetric(unsigned int index) const;
  double getCenterX() const;
  double getCenterY() const;
  double getDist(unsigned int from, unsigned int to) const;
  vrpConst* getParameter() const;
  vector<unsigned int> getGroup() const;
  
//  bool isRedundancy() const;
  bool isViolatation() const;
//  bool isLastSub() const;

  void setProblem(vrpProblem* problem);
  void setConst(vrpConst* _const);
  void setComingTime(double value);
  void setRestDist(double value);
  void printOn(ostream &os) const;
  void debug(ostream &os);

  edaSolution& operator = (const edaSolution &sol);  
  vrpSubRoute& operator = (const vrpSubRoute &subroute);    
  bool operator == (const edaSolution &sol) const;

  void Serialize( edaBuffer &buf, bool pack );
  setClassID(_USERCLASSID_ + _CLSID_VRP_SUBROUTE_);
    
private:
  vector<double> _start;
  vector<double> _waiting;
  vector<double> _loaded;  
  vector<double> _dist;  
  double _init_res_dist;
  double _total_service_time;
  double _total_move_dist;
  double _total_move_time;
  double _total_wait_time;  
  double _total_load; 
  double _coming_time;
  double _cost;
  double _x_center;
  double _y_center;
  vector<unsigned int> _group_list;	
  vrpProblem* _problem;
  vrpConst* _const;
  void addGroup(vrpStop* stop);
};

#endif	/* VRPSUBROUTE_H */

