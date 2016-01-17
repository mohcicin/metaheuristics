/* 
 * File:   vrpStop.h
 * Author: Administrator
 *
 * Created on June 7, 2012, 4:21 PM
 */

#ifndef VRPSTOP_H
#define	VRPSTOP_H
#include "../lib/edaSerialize.h"
#include "vrpDefine.h"
#include <iostream>
using namespace std;

class vrpStop : public edaSerialize {
public:
  vrpStop();
  vrpStop(const vrpStop& stop);
  vrpStop *clone() const;
  virtual ~vrpStop();

  void printOn(ostream& os) const;
  void debug(ostream& os) const;

  vrpStop& operator =(const vrpStop &stop);
  bool operator ==(const vrpStop &stop) const;

  void Serialize(edaBuffer &buf, bool pack);
  setClassID(_USERCLASSID_ + _CLSID_VRP_STOP_);

public:
  unsigned int ID; //index in original stop
  double X; // X coordinate
  double Y; // Y coordinate
  double Load; // amount waste at stop
  double EarlyTime; // early time window
  double LateTime; // late time window
  double ServiceTime; //time for unload and load waste 
  unsigned int Type; //type of stop ( regular_stop , landfill, depot)
  unsigned int Group; //group of regular stop
};
ostream& operator<<(ostream &os, const vrpStop &stop);
#endif	/* VRPSTOP_H */

