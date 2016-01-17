/* 
 * File:   mtspSolution.h
 * Author: Tieu Minh
 *
 * Created on March 11, 2014, 10:10 PM
 */

#ifndef TSPTWSOLUTION_H
#define	TSPTWSOLUTION_H


#include "mtspDefine.h"
#include "mtspProblem.h"


class mtspSolution: public edaSolution {
public:
    //Construction
    mtspSolution();
    mtspSolution(const edaProblem& pro);
    ~mtspSolution();
    
    //Method        
    void set(const edaProblem& pro);
    void set(const double fitness);
    void update();
    const mtspProblem& pro() const;
    unsigned int& at(unsigned int index);
    const unsigned int at(unsigned int index) const;
    unsigned int size() const;
    unsigned int depot() const;
    void easer();
    mtspSolution* clone() const;
    void print(ostream& os) const;  
    void info(ostream& os) const;
    void init();   
    double evaluate();
    void decode(const edaChromosome& chro);
    edaChromosome* encode() const;
    mtspSolution& operator =(const edaSolution& Sol);
    bool operator == (const edaSolution& sol) const;
    unsigned int& operator [] (unsigned int index);
    const unsigned int operator [] (unsigned int index) const;
    void serialize(edaBuffer& buf, bool pack);
    setClassID(_USERCLASSID_ + _CLSID_MTSPSOLUTION_);
    void save(const char* filename);  
    const char* className() const;
    void checkError() const;
    
private:
    void graphError() const;
    void initError() const;
    const mtspProblem* _graph;
    double _fitness;
    unsigned int _size;
    unsigned int* _route;
    unsigned int* _come;
    unsigned int* _move;
    unsigned int* _wait;
    unsigned int* _late;
//    unsigned int* _id;
};

#endif	/* TSPSOLUTION_H */

