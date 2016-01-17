/* 
 * File:   ParametricAirfoil.h
 * Author: Tieu Minh
 *
 * Created on April 22, 2013, 9:04 AM
 */

#ifndef AIRFOIL_H
#define	AIRFOIL_H

#include "Define.h"

class airFoil: public edaSerialize, public vector<double> {
    
public:
    airFoil();
    airFoil(const airFoil& foil);
    airFoil(double foil[]);
    airFoil(const char* foilname);
    virtual ~airFoil();
    airFoil* clone() const;
    void update();
    bool incrEval(unsigned int index, unsigned int sign);
    double z_up(double x) const;
    double z_lo(double x) const;  
    double norm(unsigned int index) const;
    void denorm(unsigned int index, const double &value);
    unsigned int size() const;
    bool check() const;
    airFoil& operator = (const airFoil &foil);
    bool operator == (const airFoil &foil);
    void printOn(ostream& os) const;
    string detail() const;
    string name() const;
    void Serialize(edaBuffer &buf, bool pack);
    static airFoil* createFoil(double* foil = NULL);
    setClassID(_USERCLASSID_ + _CLSID_AIR_FOIL_);
    
private:
    double a[6], b[6]; 
};
ostream& operator<< (ostream &os, const airFoil &par);
#endif	/* PARAMETRICAIRFOIL_H */

