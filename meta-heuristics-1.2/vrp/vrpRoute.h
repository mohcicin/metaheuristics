/* 
 * File:   vrpRoute.h
 * Author: Administrator
 *
 * Created on June 7, 2012, 11:03 PM
 */

#ifndef VRPROUTE_H
#define	VRPROUTE_H
#include "../lib/eda.h"
#include "vrpSubRoute.h"
#include "vrpDefine.h"
#include "vrpConst.h"
class vrpRoute: public vector<vrpSubRoute*>, public edaSolution {
public:
    vrpRoute();
    vrpRoute(const vrpRoute& route);
    virtual ~vrpRoute();
    vrpRoute *clone() const;
    double evaluate() ;   
    void update();
    void init(); 
    double getTotalMoveDist() const;
    double getCost() const;
    double getTotalLoad() const;
    double getTotalWaitTime() const;
    double getTotalMoveTime() const;
    double getServiceTime() const;
    double getTotalUseTime() const;
    double getShapeMetric() const;
    vrpConst* getParameter() const;
    bool isRedundancy() const;
 
    void printOn(ostream &os) const;
    void debug(ostream &os) const;
    edaSolution& operator = (const edaSolution &sol);
    vrpRoute& operator = (const vrpRoute &route);
    bool operator == (const edaSolution &sol) const;
    
    void Serialize( edaBuffer &buf, bool pack );
    setClassID(_USERCLASSID_ + _CLSID_VRP_ROUTE_);
    
 
};

#endif	/* VRPROUTE_H */

