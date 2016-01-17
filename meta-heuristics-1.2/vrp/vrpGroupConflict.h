/* 
 * File:   vrpGroupConflict.h
 * Author: Administrator
 *
 * Created on June 7, 2012, 4:52 PM
 */

#ifndef VRPGROUPCONFLICT_H
#define	VRPGROUPCONFLICT_H
#include "../lib/eda.h"
#include "vrpDefine.h"

using namespace std;
class vrpGroupConflict: public edaSerialize  {
public:
    vrpGroupConflict();
    vrpGroupConflict(const vrpGroupConflict& group);
    vrpGroupConflict(const unsigned int size);
    vrpGroupConflict *clone() const;
    virtual ~vrpGroupConflict();
    
    void pushConflictGroup(unsigned int group_A,unsigned int group_B);
    bool isConflict(const unsigned int group, const vector<unsigned int>& groups) const;
    bool isConflict(const vector<unsigned int>& groups) const;
    void prinOn(ostream& os) const;
    
    void Serialize(edaBuffer &buf, bool pack);
    setClassID(_USERCLASSID_ + _CLSID_VRP_GROUP_CONFLICT_);
private:
    void easer();
    unsigned int _size;
    bool *_matrix;
};

#endif	/* VRPGROUPCONFLICT_H */

