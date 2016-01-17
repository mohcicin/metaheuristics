/* 
 * File:   vrpConst.h
 * Author: Administrator
 *
 * Created on June 8, 2012, 9:01 PM
 */

#ifndef VRPCONST_H
#define	VRPCONST_H
#include "../lib/eda.h"
#include "vrpDefine.h"
#include "vrpProblem.h"
class vrpConst: public edaSerialize {
public:
    enum TYPE { Default = 0, Random = 1};
    vrpConst(const TYPE type = Default);
    vrpConst(const float* filename, const unsigned int num);
    vrpConst(const char* filename);
    vrpConst(const vrpConst& orig);
    virtual ~vrpConst();
    vrpConst *clone() const;
    void load(const char *filename ="");    
    
    vrpConst& operator = (const vrpConst &_const);
    
    
    void Serialize(edaBuffer &buf, bool pack);
	setClassID(_USERCLASSID_ + _CLSID_VRP_CONST_);    

    double BETA_1, BETA_2, BETA_3;
    double ALPHA_1, ALPHA_2;
    double LAMDA;
    double THETA_1, THETA_2, THETA_3;
    double MU;
    double PAR_1, PAR_2;
    int HAS_IMPROVE_ROUTE, HAS_IMPROVE_SUB,
         HAS_IMPROVE_LANDFILL;
    

};

#endif	/* VRPCONST_H */

