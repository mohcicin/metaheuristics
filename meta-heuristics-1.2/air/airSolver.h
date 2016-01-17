/* 
 * File:   sonicFoam.h
 * Author: Tieu Minh
 *
 * Created on April 23, 2013, 10:34 AM
 */

#ifndef SONICFOAM_H
#define	SONICFOAM_H

#include "Define.h"

class airSolver: public edaSerialize {
public:
    airSolver();
    airSolver(const airSolver& orig);    
    airSolver(const char* filename);
    virtual ~airSolver();
    airSolver* clone() const;
    void createData() const;
    void printOn(ostream& os) const;
    void Serialize( edaBuffer &buf, bool pack );  
    setClassID(_USERCLASSID_ + _CLSID_AIR_SOLVER_);
    
private:
    
    const char* createTurbulencePropertiesFile() const;
    const char* createRASPropertiesFile() const;    
    const char* createThermophysicalPropertiesFile() const;  
    
    const char* createVelocityInititalCondition() const;  
    const char* createPressureInititalCondition() const;  
    const char* createKineticInititalCondition() const;  
    const char* createDissipationInititalCondition() const;  
    const char* createTemperatureInititalCondition() const;  
    const char* createEddyViscosityInititalCondition() const; 
    
    const char* createForceCoeffsFile() const;   
    const char* createFvSchemesFile() const;
    const char* createFvSolutionFile() const;


    char ras[32];
    double mach[3];
    double p;
    double T;
    double k;
    double epsilon;
    double mu;
    double kappa;
    double Cv;
    double M;
    
  
};
ostream& operator<< (ostream &os, const airSolver &solver);
#endif	/* SONICFOAM_H */

