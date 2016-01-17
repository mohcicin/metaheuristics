/* 
 * File:   vrpSoluton.h
 * Author: Administrator
 *
 * Created on June 7, 2012, 8:32 PM
 */

#ifndef VRPSOLUTION_H
#define	VRPSOLUTION_H
#include "../lib/eda.h"
#include "vrpDefine.h"
#include "vrpProblem.h"
#include "vrpRoute.h"
#include "vrpConst.h"
class vrpSolution: public edaSolution, public vector<vrpRoute*> {
public:
    vrpSolution();
    vrpSolution(const vrpSolution& sol);
    vrpSolution(vrpProblem *problem);
    virtual ~vrpSolution();
    vrpSolution* clone() const;
    
    void init();
    double evaluate() ; 
    double getCost() const;
    vrpConst* getParameter() const;
    vector<unsigned int> getListRoute() const; 
    void setProblem(vrpProblem *problem);
    void setParameter(vrpConst *_const);
    vrpProblem* getProblem() const;
    double getTotalDist() const;
    double getTotalWaitTime() const;
    double getTotalMoveTime() const;
    double getShapeMetric() const; 
    void printOn(ostream &os) const;
    void debug(ostream &os) const;
    void writeCSVFile(const char* file_name) const;
    string detail() const;
    void update();
    edaSolution& operator = (const edaSolution &sol);
    vrpSolution& operator = (const vrpSolution &sol);
    bool operator == (const edaSolution &sol) const;
    void improveLandfill();
    void Serialize( edaBuffer &buf, bool pack );
    setClassID(_USERCLASSID_ + _CLSID_VRP_SOLUTION_);

private:
    vrpProblem *_problem; 
    vrpConst *_const;
    bool *_status;    
    
    double _total_cost,
           _total_dist, 
           _total_wait_time,
           _total_move_time,
           _total_service_time,
           _total_use_time,
           _total_load,
           _shape_metric;
    unsigned int _num_route,
                 _num_sub_route;

    vrpSubRoute* createSubRoute(vrpStop* ref, double rest_dist, double coming_time);   
    vrpStop* getBestFirstStop(vrpStop* ref, double coming_time) const;
    vrpStop* getRandomFirstStop(vrpStop* ref, double coming_time) const;
    vrpStop* getNextStop(vrpSubRoute& sub, unsigned int &pos) const;
    void easer();
};
#endif	/* VRPSOLUTON_H */

