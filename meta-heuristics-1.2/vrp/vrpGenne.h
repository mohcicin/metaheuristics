
#ifndef WRPGENNE_H
#define	WRPGENNE_H
#include "../lib/eda.h"
#include "vrpStop.h"

class vrpGenne: public edaGenne {
public:
    vrpGenne();
    vrpGenne(vrpStop *stop);
    vrpGenne(const unsigned int stop_id);
    vrpGenne(const vrpGenne& orig);
    unsigned int getValue() const;
    vrpGenne *clone() const;
    virtual ~vrpGenne();
    void swap(edaGenne *genne);
    vrpGenne& operator = (const edaGenne &genne);
    vrpGenne& operator = (const char *code);
    bool operator == (const edaGenne &genne) const;
    void printOn(ostream &os) const;
    void Serialize(edaBuffer& buf, bool pack);
    setClassID(_USERCLASSID_ + _CLSID_VRP_GENNE_);
private:
    unsigned int _value;
};
#endif	/* VRPGENNE_H */

