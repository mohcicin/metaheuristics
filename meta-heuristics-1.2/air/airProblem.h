/* 
 * File:   airProblem.h
 * Author: Tieu Minh
 *
 * Created on April 30, 2013, 9:36 AM
 */

#ifndef AIRPROBLEM_H
#define	AIRPROBLEM_H

#include "airControl.h"
#include "airMesh.h"
#include "airSolver.h"


class airProblem: public edaProblem {
public:
    airProblem();
    airProblem(const airProblem& orig);
    airProblem(const char* filename);
    airProblem *clone() const;
    virtual ~airProblem();
    airFoil* createFoil(double* foil = NULL) const;
    airProblem& operator = (const edaProblem &pro);
    double run(const airFoil& foil);
    void Serialize(edaBuffer &buf, bool pack);
    setClassID(_USERCLASSID_ + _CLSID_AIR_PROBLEM_);
    
private:
    void earse();
    double readForceCoeffsFile(const airFoil& foil);
    void createData(const airFoil& foil);
    airControl *control;
    airSolver* solver;
    airMesh* mesh;

};

#endif	/* AIRPROBLEM_H */

