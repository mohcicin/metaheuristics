/* 
 * File:   vrpStop.cpp
 * Author: Administrator
 * 
 * Created on June 7, 2012, 4:21 PM
 */

#include <strings.h>
#include "vrpStop.h"

vrpStop::vrpStop() {}

vrpStop::vrpStop(const vrpStop& stop) {
    ID = stop.ID;
    X = stop.X;
    Y = stop.Y;
    Load = stop.Load;
    EarlyTime = stop.EarlyTime;
    LateTime = stop.LateTime;
    ServiceTime = stop.ServiceTime;
    Type = stop.Type;
    Group = stop.Group;
}

vrpStop *vrpStop::clone() const {
    return new vrpStop(*this);
}

vrpStop::~vrpStop() {}

void vrpStop::printOn(ostream& os) const {
  os << (int)ID;
}
void vrpStop::debug(ostream& os) const {
  os << (int)ID << "\t";
  os << (int)X << "\t";
  os << (int)Y << "\t";
  os << (int)EarlyTime<< "\t";
  os << (int)LateTime << "\t";
  os << (int)ServiceTime << "\t";
  os << (int)Load << "\t";
  os << (int)Type << "\t";
  os << (int)Group << "\t";
  os << endl;
} 
void vrpStop::Serialize(edaBuffer &buf, bool pack) {
    edaSerialize::Serialize(buf,pack);
    if ( pack ){
        buf.Pack( &ID, 1 );
        buf.Pack( &X, 1 );
        buf.Pack( &Y, 1 );
        buf.Pack( &Load, 1 );
        buf.Pack( &EarlyTime, 1 );
        buf.Pack( &LateTime, 1 );
        buf.Pack( &ServiceTime, 1 );
        buf.Pack( &Type, 1 );
        buf.Pack( &Group, 1 );
    } 
    else {
        buf.UnPack( &ID, 1 );
        buf.UnPack( &X, 1 );
        buf.UnPack( &Y, 1 );
        buf.UnPack( &Load, 1 );
        buf.UnPack( &EarlyTime, 1 );
        buf.UnPack( &LateTime, 1 );
        buf.UnPack( &ServiceTime, 1 );
        buf.UnPack( &Type, 1 );
        buf.UnPack( &Group, 1 );
    }
}

vrpStop& vrpStop::operator = (const vrpStop &stop) {
    ID = stop.ID;
    EarlyTime = stop.EarlyTime;
    Group = stop.Group;
    LateTime = stop.LateTime;
    Load = stop.Load;
    ServiceTime = stop.ServiceTime;
    Type = stop.Type;
    X = stop.X;
    Y = stop.Y;
    return *this;
}

bool vrpStop::operator == (const vrpStop &stop) const {
    if(ID != stop.ID)
        return false;
    if(EarlyTime != stop.EarlyTime)
        return false;
    if(Group != stop.Group)
        return false;
    if(LateTime != stop.LateTime)
        return false;
    if(Load != stop.Load)
        return false;
    if(ServiceTime != stop.ServiceTime)
        return false;
    if(Type != stop.Type)
        return false;
    if(X != stop.X)
        return false;
    if(Y != stop.Y)
        return false;
    return true;
}
ostream& operator << (ostream &os, const vrpStop &stop) {
    stop.printOn(os);
    return os;
}
