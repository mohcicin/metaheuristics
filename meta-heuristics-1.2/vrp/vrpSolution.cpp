/* 
 * File:   vrpSoluton.cpp
 * Author: Administrator
 * 
 * Created on June 7, 2012, 8:32 PM
 */

#include "vrpSolution.h"
#include <cstring>
#include <vector>
#include <sstream>
#include <iomanip>
vrpSolution::vrpSolution() {
    _problem = NULL;
    _status = NULL;
    _const = NULL;
}

vrpSolution::vrpSolution(vrpProblem *problem) {
    _const = new vrpConst();
    setProblem(problem->clone());
}
void vrpSolution::setParameter(vrpConst *_const) {
    this->_const = _const->clone();
}
void vrpSolution::setProblem(vrpProblem *problem) {
    _problem = problem;
    unsigned int _num_stop = _problem->getNumStops(); 
    _status = new bool[_num_stop];
    fill(_status,_status+_num_stop, UN_ROUTED);
    _total_cost = _total_dist = _total_move_time = _total_wait_time
            = _total_service_time = _total_use_time = _total_load
            = 0;
    _num_route =_num_sub_route = 0;
}

vrpSolution::vrpSolution(const vrpSolution& sol) {
    _problem = sol._problem->clone();
    _const = sol._const->clone();
    unsigned int _num_stop = _problem->getNumStops();
    for(unsigned int i = 0; i < sol.size(); i++) {
        vrpRoute* route = sol[i]->clone();
        for(unsigned int j = 0; j < route->size(); j++) {
          vrpSubRoute* sub = route->at(j);
          sub->setProblem(_problem);
          sub->setConst(_const);
        }
        push_back(route);
    }
    _total_cost = sol._total_cost;
    _total_dist = sol._total_dist;
    _total_move_time = sol._total_move_time;
    _total_wait_time = sol._total_wait_time;
    _total_service_time = sol._total_service_time;
    _total_use_time = sol._total_use_time;
    _total_load = sol._total_load;
    _num_route = sol._num_route;
    _num_sub_route = sol._num_sub_route;
    _status = new bool[_num_stop];
    memcpy(_status, sol._status, sizeof(bool)*_num_stop);
//    std::cout << sol.getCost() << std::endl;
//    std::cout << this->evaluate() << std::endl;
}
vrpSolution* vrpSolution::clone() const {
    return new vrpSolution(*this);
}

vrpSolution::~vrpSolution() { 
  easer();
}

void vrpSolution::init() {     
    vrpRoute *route; 
    vrpSubRoute *sub;
    double res_dist;
    vrpStop* ref;
    double coming_time;
    this->clear();
    vrpStop* _depot = _problem->getDepot();

INIT_ROUTE:
    route = new vrpRoute();
    ref = _depot;
    res_dist = _problem->getMaxTotalDist();
    coming_time = ref->EarlyTime;
    
INIT_SUB:  
    sub = createSubRoute(ref, res_dist, coming_time); 
    if(sub != NULL) {
        vrpStop* stop = NULL;
        unsigned int pos = 0;   
        while((stop = getNextStop(*sub,pos)) != NULL)  {        
            sub->insertStop(stop->ID, pos);
            _status[stop->ID] = ROUTED;            
        }  
        sub->removeStop(_depot->ID);   
        ref = _problem->getStop(sub->at(sub->size()-1));
        coming_time = sub->getComingTime(sub->size()-1);
        res_dist = sub->getRestDist();  
        route->push_back(sub);
        goto INIT_SUB;
    }
    else {
        if(route->size() > 0) {
            vrpSubRoute* last = route->at(route->size() -1);
            last->pushStop(_depot);        
            this->push_back(route);            
            goto INIT_ROUTE;
        }
        else {
            delete route;
            improveLandfill();
            update();
            return;
        }
    }
}
vector<unsigned int> vrpSolution::getListRoute() const {
    vector<unsigned int> result;
    for(unsigned int i = 0; i < size(); i++) {
        vrpRoute* route = at(i);
        for(unsigned int j = 0; j < route->size(); j++) {
            vrpSubRoute* sub = route->at(j);
            for(unsigned int k = 0; k < sub->size(); k++) {
                vrpStop* stop = _problem->getStop(sub->at(k));
                result.push_back(stop->ID);      
            }            
        }
    }
    return result;
}
vrpStop* vrpSolution::getBestFirstStop(vrpStop* ref, double coming_time) const {
    vrpStop* result = NULL;  
    double best = MAX_NUMBER;
    vrpConst& C = *_const;
    vector<vrpStop*> _regular_stop = _problem->getRegularStop();
    for(unsigned int i = 0 ; i < _regular_stop.size(); i++) {
        vrpStop* stop = _regular_stop[i];  
        if(_status[stop->ID] == UN_ROUTED) {
            double start = MAX(coming_time, ref->EarlyTime);
            double come = start + ref->ServiceTime
                                + _problem->getTime(ref->ID, stop->ID);
            if(come <= stop->LateTime) {   
                double late = stop->LateTime;
                double time = _problem->getTime(ref->ID, stop->ID);
                double dist = _problem->getDist(ref->ID, stop->ID); 
                double cost = C.BETA_1*time + C.BETA_2*late + C.BETA_3*dist;
                if(cost < best) {
                    best = cost;
                    result = stop;
                }
            }
        }
    }
    return result;
}
vrpStop* vrpSolution::getRandomFirstStop(vrpStop* ref, double coming_time) const {  
    vrpStop* result = NULL;  
    vector<unsigned int> list;
    vector<vrpStop*> _regular_stop = _problem->getRegularStop();
    for(unsigned int i = 0; i <_regular_stop.size(); i++)  {      
        if(_status[_regular_stop[i]->ID] == UN_ROUTED)
            list.push_back(i);
    }
    if(list.size() < 1) return result;
    unsigned int j = rnd.random( list.size() );
    unsigned int i = list[j];
    result = _regular_stop[i];
    return result;
}
vrpStop* vrpSolution::getNextStop(vrpSubRoute& sub, unsigned int &pos) const {
    vrpStop* next_stop = NULL;
    unsigned int size = sub.size();
    double max = MIN_NUMBER;
    vrpConst& C = *_const;
    vector<vrpStop*> _regular_stop = _problem->getRegularStop();
    vrpStop* _depot = _problem->getDepot();
    for(unsigned int i = 1 ; i < size - 1 ; i++) {
        for(unsigned int j = 0 ; j < _regular_stop.size() ; j++) {
            vrpStop* left = _problem->getStop(sub[i-1]);
            vrpStop* right = _problem->getStop(sub[i]);
            vrpStop* stop = _regular_stop[j];
            if(_status[stop->ID] == UN_ROUTED && sub.canInsert(stop,i)) {                
            	double C11 = _problem->getDist(left->ID, stop->ID)
                           + _problem->getDist(stop->ID, right->ID)
                           - _problem->getDist(left->ID, right->ID);
              double coming_stop  = sub.getStartTime(i-1) 
                                  + left->ServiceTime 
                                  + _problem->getTime(left->ID, stop->ID);
            	double start_stop = MAX(stop->EarlyTime, coming_stop);
              double coming_right  = start_stop 
                                   + stop->ServiceTime
                                   + _problem->getTime(stop->ID, right->ID);    
              double start_right = MAX(right->EarlyTime, coming_right);
              double C12 = start_right  - sub.getStartTime(i);
            	double C1 = C.ALPHA_1*C11 + C.ALPHA_2*C12;
            	double C2 = C.LAMDA*_problem->getDist(_depot->ID, stop->ID) - C1;
            	if(C2 > max) {
            		max  = C2;
            		next_stop = stop;
            		pos = i;            		
            	}
            }
        }
    }
    return next_stop;
}

vrpSubRoute* vrpSolution::createSubRoute(vrpStop* ref, double rest_dist, double coming_time){
    vrpStop* _depot = _problem->getDepot();  
    vrpStop* stop = getRandomFirstStop(ref, coming_time);   
    vector<vrpStop*> _landfill = _problem->getLandfill();
    if(stop != NULL) {
        vrpSubRoute *result = new vrpSubRoute(rest_dist, coming_time);
        result->setProblem(_problem);
        result->setConst(_const);
        result->insertStop(ref->ID ,0);
        result->insertStop(stop->ID ,1);
        _status[stop->ID] = ROUTED;
        result->insertStop(_depot->ID, 2);
        for(unsigned int i = 0; i < _landfill.size(); i++) {
            if(result->canInsert(_landfill[i] ,2)) {
                result->insertStop(_landfill[i]->ID ,2);
                return result;              
            }
        }
        _status[stop->ID] = UN_ROUTED;
        delete result;        
    }    
    return NULL; 
}

void vrpSolution::improveLandfill() {
    vector<vrpStop*> _landfill = _problem->getLandfill();
    for(unsigned int i = 0; i < size(); i++) {
        double old_dist, new_dist; 
        vrpStop* stop = NULL;
        vrpRoute *route = at(i);        
        unsigned int size = route->size();
        
        //For all subroute
        for(unsigned int j = 0; j < size - 1; j++) {
            vrpSubRoute &left = *route->at(j);
            vrpSubRoute &right = *route->at(j + 1);
            unsigned int last = left.size() - 1;
            if(left[last] != right[0]) {
                cout << "Building VRP Solution error" << endl;
                exit(1);
            }
            else {
                old_dist = _problem->getDist(left[last-1],left[last]) 
                         + _problem->getDist(right[0],right[1]);
                double tmp = old_dist;
                for(unsigned int k = 0; k < _landfill.size(); k++) {                       
                    if(_landfill[k]->ID != right[0]) {
                        new_dist = _problem->getDist(left[last-1], _landfill[k]->ID) 
                                 + _problem->getDist(_landfill[k]->ID, right[1]);
                        if(new_dist < tmp) {
                            tmp = new_dist;
                            stop = _landfill[k];
                        }
                    }                    
                }
                if(tmp != old_dist) {
                    left[last] = stop->ID;
                    left.update();
                    right[0] = stop->ID;
                    right.setComingTime(left.getComingTime(last));
                    right.update();
                }
            }
        }
        //For last subroute
        vrpSubRoute &sub = *route->at(size-1);
        unsigned int last = sub.size() - 2;
        old_dist = _problem->getDist(sub[last-1],sub[last])
                 + _problem->getDist(sub[last],sub[last+1]);
        double tmp = old_dist;
        for(unsigned int k = 0; k < _landfill.size(); k++) {     
            new_dist = _problem->getDist(sub[last-1],_landfill[k]->ID) 
                     + _problem->getDist(_landfill[k]->ID,sub[last+1]);
            if(new_dist < tmp) {
                tmp = new_dist;
                stop = _landfill[k];
            }                                
        }
        if(tmp != old_dist) {
            sub[last] = stop->ID;           
            sub.update();
        }
    }
}
vrpConst* vrpSolution::getParameter() const {
    return _const;
}
void vrpSolution::update() {
    for(unsigned int i = 0; i < size(); i++) {
        vrpRoute *route = at(i);
        route->update();        
        if( route->isRedundancy() ) 
        {
            erase(begin() + i);
            delete route;
            i--;
        }
    }
    _num_route = size();
    _num_sub_route = 0;
    _total_dist = _total_load 
                = _total_wait_time
                = _total_move_time 
                = _total_service_time
                = _total_use_time 
                = _total_cost 
                = _shape_metric
                = 0.0;

    for(unsigned int i = 0; i < _num_route; i++) {
        vrpRoute *route = at(i);
        _total_dist += route->getTotalMoveDist();
        _total_load += route->getTotalLoad();
        _total_wait_time += route->getTotalWaitTime();
        _total_move_time += route->getTotalMoveTime();
        _total_service_time += route->getServiceTime();
        _total_use_time += route->getTotalUseTime();     
        _num_sub_route += route->size();
        _total_cost += route->evaluate();
        _shape_metric += route->getShapeMetric();
    } 
}

double vrpSolution::evaluate() {
    return _total_cost;
}
 
void vrpSolution::printOn(ostream& os) const {
    for(unsigned int i = 0; i < size(); i++) {
        vrpRoute *route = at(i);
        route->printOn(os);
    }    
}

edaSolution& vrpSolution::operator = (const edaSolution &sol) {
    vrpSolution &mySol = (vrpSolution&) sol;    
    return operator = (mySol);
}
vrpSolution& vrpSolution::operator = (const vrpSolution &sol) {
    this->easer();
   _problem = sol._problem->clone();
    _const = sol._const->clone();
    unsigned int _num_stop = _problem->getNumStops();
    for(unsigned int i = 0; i < sol.size(); i++) {
        vrpRoute* route = sol[i]->clone();
        for(unsigned int j =0; j < route->size(); j++) {
          vrpSubRoute* sub = route->at(j);
          sub->setProblem(_problem);
          sub->setConst(_const);
        }
        push_back(route);
    }
    _total_cost = sol._total_cost;
    _total_dist = sol._total_dist;
    _total_move_time = sol._total_move_time;
    _total_wait_time = sol._total_wait_time;
    _total_service_time = sol._total_service_time;
    _total_use_time = sol._total_use_time;
    _total_load = sol._total_load;
    _num_route = sol._num_route;
    _num_sub_route = sol._num_sub_route;
    _status = new bool[_num_stop];
    memcpy(_status, sol._status, sizeof(bool)*_num_stop);
    return *this;
}
bool vrpSolution::operator == (const edaSolution &sol) const{
    vrpSolution &mySol = (vrpSolution&) sol;
    unsigned int _size = mySol.size();
    if(_size != size())
        return false;
    for(unsigned int i = 0; i < _size; i++)
        if(*(at(i)) != *(mySol[i]))
            return false;
    return true;
}

void vrpSolution::Serialize(edaBuffer &buf, bool pack ){
  if( pack ) {
        _problem->doSerialize(buf, pack);
        _const->doSerialize(buf, pack);  
        
        unsigned int size  = this->size();
        buf.Pack( &size, 1 );
        for (unsigned int i = 0; i < size; i++) {
            vrpRoute* route = this->at(i);
            route->doSerialize( buf,pack);
        }
   
        buf.Pack( _status, _problem->getNumStops() );
        buf.Pack( &_total_cost, 1 );
        buf.Pack( &_total_dist, 1 );
        buf.Pack( &_total_wait_time, 1 );
        buf.Pack( &_total_move_time, 1 );
        buf.Pack( &_total_service_time, 1 );
        buf.Pack( &_total_use_time, 1 );
        buf.Pack( &_total_load, 1 );
        buf.Pack( &_num_route, 1 );
        buf.Pack( &_num_sub_route, 1 );
           
    }
    else {
        easer();
        _problem = (vrpProblem*)classGenerateFromBuffer(buf);
        _const = (vrpConst*)classGenerateFromBuffer(buf);
        
        unsigned int size;
        buf.UnPack( &size, 1 );       
        for (unsigned int i = 0; i < size; i++) {
            vrpRoute* route = (vrpRoute*)classGenerateFromBuffer( buf );
            for(unsigned int j = 0; j < route->size() ; j++){
              vrpSubRoute* sub = route->at(j);
              sub->setProblem(_problem);
              sub->setConst(_const);
            }              
            this->push_back(route);
        }
        
        _status = new bool[_problem->getNumStops()];
        buf.UnPack( _status, _problem->getNumStops() );
        buf.UnPack( &_total_cost, 1 );
        buf.UnPack( &_total_dist, 1 );
        buf.UnPack( &_total_wait_time, 1 );
        buf.UnPack( &_total_move_time, 1 );
        buf.UnPack( &_total_service_time, 1 );
        buf.UnPack( &_total_use_time, 1 );
        buf.UnPack( &_total_load, 1 );
        buf.UnPack( &_num_route, 1 );
        buf.UnPack( &_num_sub_route, 1 );        
    }   
}
void vrpSolution::debug(ostream &os) const{
    for(unsigned int i = 0 ; i < size() ; i++) {
        os << "Route " << i << ":" << endl;
        at(i)->debug(os);
        os <<"---------------------------------------------"
                "---------------------------------------------\n";
    }
}
void vrpSolution::writeCSVFile(const char* file_name) const{      
    ofstream os(file_name,ios::trunc);
    os << "ID,X,Y,Dist,Early,Late,Wait,Start,Service,Time,Load,Acomn,cX,cY,Metric,Group,Type,Sub,Route\n";
    for(unsigned int i = 0 ; i < size() ; i++) {
        vrpRoute* route = at(i);
        double dist = 0;
        for(unsigned int j = 0 ; j < route->size() ; j++) {
            vrpSubRoute* sub = route->at(j);
            dist += j > 0 ? route->at(j-1)->getTotalMoveDist() : 0;
            for(unsigned int k = 0 ; k < sub->size() ; k++) {
                vrpStop* stop = _problem->getStop(sub->at(k));
                os << stop->ID << ",";
                os << (int)stop->X << ",";
                os << (int)stop->Y << ",";
                os << dist + sub->getDistance(k) << ",";
                os << stop->EarlyTime << ",";
                os << stop->LateTime << ",";
                os << sub->getWaitTime(k) << ",";
                os << sub->getStartTime(k) << ",";
                os << stop->ServiceTime << ",";
                os << sub->getUseTime(k) << ",";
                os << stop->Load << ",";
                os << sub->getAcomnLoad(k) << ",";    
                os << (int)sub->getCenterX() << ",";
                os << (int)sub->getCenterY() << ",";
                os << sub->getShapeMetric(k) << ",";
                os << stop->Group << ",";
                os << stop->Type << ",";
                os << j << ",";
                os << i << endl;

            }
        } 
    }
    os.close();
}
double vrpSolution:: getTotalDist() const {
    return _total_dist;
}
 double vrpSolution::getTotalWaitTime() const {
    return _total_wait_time;
}
double vrpSolution::getTotalMoveTime() const {
    return _total_move_time;     
} 
 
double vrpSolution::getShapeMetric() const {
    return _shape_metric;
}
string vrpSolution::detail() const {
    stringstream  _stream("");
    _stream << left << setw(6) << "ID"
                    << setw(14) << "X"
                    << setw(14) << "Y"
                    << setw(10) << "Dist"
                    << setw(8) << "Early"
                    << setw(8) << "Late"
                    << setw(8) << "Wait"
                    << setw(8) << "Start"
                    << setw(8) << "Service"
                    << setw(8) << "Time"
                    << setw(8) << "Load"
                    << setw(8) << "Acomn"
                    << setw(6) << "Group"
                    << setw(6) << "Type"
                    << setw(6) << "Sub"
                    << setw(6) << "Route" << endl;
    for(unsigned int i = 0 ; i < size() ; i++) {
        vrpRoute* route = at(i);
        double dist = 0;
        for(unsigned int j = 0 ; j < route->size() ; j++) {
            vrpSubRoute* sub = route->at(j);
            dist += j > 0 ? route->at(j-1)->getTotalMoveDist() : 0;
            for(unsigned int k = 0 ; k < sub->size() ; k++) {
                vrpStop* stop = _problem->getStop(sub->at(k));                
                _stream << left << setw(6) << stop->ID
                   << setw(14) << stop->X
                   << setw(14) << stop->Y
                   << setw(10) << dist + sub->getDistance(k)
                   << setw(8) << stop->EarlyTime
                   << setw(8) << stop->LateTime
                   << setw(8) << sub->getWaitTime(k)
                   << setw(8) << sub->getStartTime(k)
                   << setw(8) << stop->ServiceTime
                   << setw(8) << sub->getUseTime(k)
                   << setw(8) << stop->Load
                   << setw(8) << sub->getAcomnLoad(k)
                   << setw(6) << stop->Group
                   << setw(6) << stop->Type
                   << setw(6) << j
                   << setw(6) << i << endl;
            }
        } 
    }
    string data = "";
    _stream >> data;
    return data;
}

double vrpSolution::getCost() const {
  return _total_cost;
}

void vrpSolution::easer() {
  if(_problem != NULL) {
    delete _problem;
    _problem = NULL;
  }
  if(_const != NULL) {
    delete _const;
    _const = NULL;
  }
  for(unsigned int i = 0; i < size(); i++) {
    vrpRoute* route = at(i);
    if(route != NULL) delete route;
  }    
  delete[] _status;  
  _status = NULL;
  this->clear(); 
}
vrpProblem* vrpSolution::getProblem() const {
  return _problem;
}
