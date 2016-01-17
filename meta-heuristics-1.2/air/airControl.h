/* 
 * File:   airControl.h
 * Author: Tieu Minh
 *
 * Created on April 27, 2013, 11:26 AM
 */

#ifndef AIRCONTROL_H
#define	AIRCONTROL_H

#include "Define.h"


class airControl : public edaSerialize{
public:
    airControl();
    airControl(const airControl& orig);    
    airControl(const char* filename);
    virtual ~airControl();
    airControl* clone() const;
    void createData() const; 
    void updateData() const; 
    unsigned int getNodes() const;
    double getWriteTime() const;
    double getEndTime() const;
    double getTimeStep() const;
    double getStartTime() const;
    void printOn(ostream& os) const;
    void Serialize( edaBuffer &buf, bool pack );  
    setClassID(_USERCLASSID_ + _CLSID_AIR_CONTROL_);
    
private:    
    unsigned int n_p;
    double writeTime; 
    double endTime;
    double timeStep;
    double startTime;    
    const char* createControlDictFile() const;
    const char* updateControlDictFile() const;
    const char* createDecomposeParDictFile() const;
    

};
ostream& operator<< (ostream &os, const airControl &control);
#endif	/* AIRCONTROL_H */

