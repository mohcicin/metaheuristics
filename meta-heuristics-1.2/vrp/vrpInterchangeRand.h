/* 
 * File:   vrpInterchangeRand.h
 * Author: Tieu Minh
 *
 * Created on July 11, 2012, 4:07 PM
 */

#ifndef vrpInterchangeRand_H
#define	vrpInterchangeRand_H
#include <utility>
#include "../lib/eda.h"
#include "vrpConst.h"
#include "vrpProblem.h"
#include "vrpInterchangeMove.h"
#include "vrpSolution.h"
class vrpInterchangeRand: public edaMoveGen {
public:
    vrpInterchangeRand();
    vrpInterchangeRand(vrpProblem* problem, unsigned int lambda = 2);
    vrpInterchangeRand(const vrpInterchangeRand& orig);
    virtual ~vrpInterchangeRand();
    edaMoveGen *clone() const;
    virtual bool generate( edaMove *move, const edaSolution &sol );
    void Serialize( edaBuffer &buf, bool pack );
    setClassID(_USERCLASSID_ + _CLSID_VRP_INTERCHANGE_RAND_);
private:
    vrpProblem* _problem;
    unsigned int lambda;
    bool isFeasibleMove(vrpSolution* vrpSol, vrpInterchangeMove* move);
};

#endif	/* vrpInterchangeRand_H */

