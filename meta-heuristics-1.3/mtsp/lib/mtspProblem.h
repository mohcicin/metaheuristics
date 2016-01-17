/* 
 * File:   mtspProblem.h
 * Author: Tieu Minh
 *
 * Created on March 11, 2015, 8:31 PM
 */

#ifndef mtspProblem_H
#define	mtspProblem_H

#include "mtspDefine.h"


class mtspProblem: public edaProblem {
public:
    // Construction    
    mtspProblem();  
    mtspProblem(const char* problemFile, const char* configFile = "");
    ~mtspProblem();    
    
    // Method
    void load(const char* filename);  
    void config(const char* filename);   
    void easer();
    unsigned int size() const;   
    double speed() const;
    mtspProblem* clone() const;
    double x(unsigned int index) const;
    double y(unsigned int index) const;
    double distance(unsigned int from, unsigned int to) const;
    unsigned int time(unsigned int from, unsigned int to) const;
    double early(unsigned int index) const;
    double late(unsigned int index) const;    
    unsigned int waitPenalty() const;
    unsigned int latePenalty() const;
    void serialize(edaBuffer& buf, bool pack);   
    setClassID(_USERCLASSID_ + _CLSID_MTSPPROBLEM_);
    void print(ostream& os) const;
    const char* className() const;
    void checkError() const;

    
private:
    unsigned int _numVert;
    unsigned int _speed;
    unsigned int _waitPenalty;
    unsigned int _latePenalty;
    double** _distance;
    char _problemFile[256];
    char _configFile[256];
    double* _x;
    double* _y;
    unsigned int* _early;
    unsigned int* _late;
};

#endif	/* mtspProblem_H */

