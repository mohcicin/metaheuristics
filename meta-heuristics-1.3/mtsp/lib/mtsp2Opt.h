/* 
 * File:   mtsp2Opt.h
 * Author: Tieu Minh
 *
 * Created on March 19, 2014, 10:10 PM
 */

#ifndef TSPTW2OPT_H
#define	TSPTW2OPT_H

#include "mtspDefine.h"
#include "mtspNeighbour.h"

class mtsp2Opt : public mtspNeighbour {
public:    
    // Construction
    mtsp2Opt();
    mtsp2Opt(const mtspSolution& route);
    ~mtsp2Opt();
    
    // Method
    double evaluate();  
    mtsp2Opt* clone() const;
    void update(edaSolution& sol);
    void next();
    void rand();
    void init();
    void print(ostream& os) const;
    void serialize(edaBuffer& buf, bool pack);
    setClassID(_USERCLASSID_ + _CLSID_MTSP2OPT_);
    mtsp2Opt& operator =(const edaNeighbour& neighb);
    bool operator ==(const edaNeighbour& neighb) const;
    const char* className() const;


private:
    unsigned int _first;
    unsigned int _second;
    double _gain;
};

#endif	/* TSP2OPT_H */

