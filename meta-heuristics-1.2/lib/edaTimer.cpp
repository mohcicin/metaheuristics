#include <unistd.h>
#include <iostream>
#include "edaTimer.h"

using namespace std;

edaTimer::edaTimer()
  :d_acc(0)
{}

void edaTimer::start( bool reset ){ 
  if ( reset )
    d_acc = 0.0;
  gettimeofday( &d_from, 0 ); 
}

double edaTimer::stop(){
  gettimeofday( &d_to, 0 );
  double d = duration();
  d_acc += d;
  return d;
}

double edaTimer::restart() {
  double d = stop();
  start(true);
  return d;
}

double edaTimer::elapse() const {
  return d_acc;
}
		
double edaTimer::duration() const {
  double _from = (double)d_from.tv_usec * 1e-6 + (double)d_from.tv_sec;
  double _to = (double)d_to.tv_usec * 1e-6 + (double)d_to.tv_sec;
  return _to - _from;
}
  
ostream &operator << ( ostream &os, const edaTimer &t ){
  os << t.elapse() << " sec(s)" << flush;
  return os;
}
