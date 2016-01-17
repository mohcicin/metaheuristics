/* 
 * File:   vrpSubRoute.cpp
 * Author: Tieu Minh
 * 
 * Created on July 5, 2012, 1:23 PM
 */

#include "vrpSubRoute.h"

vrpSubRoute::vrpSubRoute() {
    _problem = NULL;
    _const = NULL;
}

vrpSubRoute::vrpSubRoute(double res_dist, double coming_time) {
    _init_res_dist = res_dist;
    _coming_time = coming_time;
    _problem = NULL;
    _const = NULL;
}

vrpSubRoute::vrpSubRoute(const vrpSubRoute& sub) 
  : vector<unsigned int>(sub) {
    _init_res_dist = sub._init_res_dist;
    _total_service_time = sub._total_service_time;
    _total_move_dist = sub._total_move_dist;
    _total_move_time = sub._total_move_time;
    _total_wait_time = sub._total_wait_time;  
    _total_load = sub._total_load;
    _coming_time = sub._coming_time;   
    _group_list = sub._group_list;	
    _problem = sub._problem;
    _const = sub._const;
    _cost = sub._cost;    
    _start = sub._start;
    _waiting = sub._waiting;
    _loaded = sub._loaded;  
    _dist =sub._dist;
    
}

vrpSubRoute::~vrpSubRoute() {
     this->clear();
    _problem = NULL;
    _const = NULL;    
    _start.clear();
    _waiting.clear();
    _loaded.clear();    
    _dist.clear();
    _group_list.clear();	
}

vrpSubRoute *vrpSubRoute::clone() const {
    return new vrpSubRoute(*this);
}

double vrpSubRoute::evaluate() {
    return _cost;
}

void vrpSubRoute::update() {    
    unsigned int _size = size();
    _group_list.clear();
    _total_move_dist = _total_move_time
                     = _total_wait_time
                     = _total_load
                     = 0;
    _loaded.resize(_size);
    _start.resize(_size);
    _waiting.resize(_size);
    _dist.resize(_size);
    _total_service_time =  _problem->getStop(front())->ServiceTime;   
    _start[0] = MAX(_coming_time, _problem->getStop(front())->EarlyTime);
    _loaded[0] = 0;
    _dist[0] = 0;
    _waiting[0] = _start[0] - _coming_time;
    _total_wait_time = _waiting[0]; 
    _x_center = _problem->getStop(at(0))->X;
    _y_center = _problem->getStop(at(0))->Y;
    for(unsigned int i = 1; i < _size; i++) {   
        _x_center += _problem->getStop(at(i))->X;
        _y_center += _problem->getStop(at(i))->Y;
        addGroup(_problem->getStop(at(i)));
        _loaded[i] = _problem->getStop(at(i))->Type == LANDFILL
                   ? 0 : _loaded[i-1] + _problem->getStop(at(i))->Load;
        double coming_time = getComingTime(i);
        if (coming_time < _problem->getStop(at(i))->EarlyTime) {
            _start[i] = _problem->getStop(at(i))->EarlyTime;
            _waiting[i] = _problem->getStop(at(i))->EarlyTime - coming_time;            
        } 
        else {			
            _start[i]  = coming_time;
            _waiting[i] = 0 ;
        }    

        _total_load += _problem->getStop(at(i))->Type == REGULAR_STOP ? _problem->getStop(at(i))->Load : 0;
        _total_move_dist = _dist[i] = _dist[i-1] + _problem->getDist(at(i-1),at(i));
        _total_move_time += _problem->getTime(at(i-1),at(i));
        _total_wait_time += _waiting[i]; 
        _total_service_time += _problem->getStop(at(i))->ServiceTime; 
    } 
    _x_center /= _size;
    _y_center /= _size;
    vrpConst& C = *_const;
    _cost = - C.THETA_1 * _total_move_dist
            - C.THETA_2 * _total_move_time
            - C.THETA_3 * _total_wait_time;
}    
void vrpSubRoute::insertStop(unsigned int id, const unsigned int pos) {     
    insert(begin() + pos, id);
    update();
}

void vrpSubRoute::insertStop(vector<unsigned int> list, const unsigned int pos) {
  insert(begin() + pos, list.begin(), list.end());
  update();
}  

//bool vrpSubRoute::isRedundancy() const {
//    if(_problem->getStop( at(1) )->Type != REGULAR_STOP) {
//        cout << "Sub: " << *this << endl;
//        return true;
//    }
//    return false;
//}

void vrpSubRoute::pushStop(vrpStop* stop) {
    insertStop(stop->ID, size());
}

void vrpSubRoute::pushStop(unsigned int id) {
    insertStop(id, size());
}
unsigned int vrpSubRoute::removeStop(const unsigned int id) { 
    unsigned int pos = 0;
    //find postion of stop
    for(unsigned int i = 1; i < size(); i++) {
        if(at(i) == id) {
            pos = i;
            break;
        }
    }
    //remove stop
    if(pos != 0) {
        erase(begin() + pos); 
        update();
        return id;
    }
    return -1;
} 
vector<unsigned int>  vrpSubRoute::removeStop(unsigned int pos, unsigned int count) {
  vector<unsigned int>  list;
	if ( begin() + pos + count < end()) {    
        list.insert(list.begin(), begin() + pos, begin() + pos + count);
        erase(begin() + pos, begin() + pos + count);
    }
	else{	
        list.insert(list.begin(), begin() + pos, end());
		erase(begin() + pos, end());
    }
    update();
    return list;
}
bool vrpSubRoute::canInsert(vrpStop* stop, const unsigned int pos) const {
    //Check position
    if(pos <= 0 || pos > size()) return false;
    
    //Check conflict
    if(_problem->isConflict(stop->Group, _group_list)) return false;
   
    //Check total load    
    if(stop->Type== REGULAR_STOP &&
            _total_load + stop->Load > _problem->getMaxCapacity()) return false;
    
    //Check windows time and total dist 
    vrpStop* left = NULL;
    vrpStop* right = NULL;
    double start =  _start[0];   
    double total_dist = 0;
    double coming_time = 0;
   
    for(unsigned int i = 0 ; i < size(); i++) {
        //Get Left and Right Stop in Subroute 
        if(i < pos - 1) {
            left = _problem->getStop( at(i) );
            right =_problem->getStop( at(i+1) );
        }
        else if(i == pos - 1) {
            left = _problem->getStop( at(i) );
            right = stop;
        }   
        else if(i == pos) {
            left = stop;
            right= _problem->getStop( at(i) );
        }   
        else {
            left = _problem->getStop( at(i-1) );
            right = _problem->getStop( at(i) );
        }

        //Check total dist
        total_dist += _problem->getDist(left->ID, right->ID);
        if(total_dist > _init_res_dist)
            return false;

        //Check windows time
        coming_time = start + left->ServiceTime + _problem->getTime(left->ID, right->ID);		
        if (coming_time < right->EarlyTime ) {
            start = right->EarlyTime;
            if( i >= pos) 
                break;			
        }
        else {
            if(coming_time > right->LateTime )		
                return false;			
            else 
                start = coming_time;			
        }
    }  
    return true;  
} 
bool vrpSubRoute::isViolatation() const { 
    //Check conflict
    if(_problem->isConflict( _group_list)) 
        return true;
    
    //Check total load    
    if(_total_load > _problem->getMaxCapacity()) 
        return true;
    
    //Check total dist 
    if(_total_move_dist > _problem->getMaxTotalDist()) 
        return true;
    
    //Check windows time   
    for(unsigned int i = 0 ; i < size(); i++) 
        if(_start[i] > _problem->getStop(at(i))->LateTime)
            return true;
    
    //Check first stop
    if(_problem->getStop(at(1))->Type != REGULAR_STOP)
        return true;
    
    //Check last stop
    if(_problem->getStop(at(size()-1))->Type == REGULAR_STOP)
        return true;
    
    return false;  
}
double vrpSubRoute::getRestDist() const {
    return _init_res_dist - _total_move_dist;
}
double vrpSubRoute::getWaitTime(unsigned int index) const {
    return _waiting[index];
}
double vrpSubRoute::getStartTime(unsigned int index) const {
    return _start[index];
}
double vrpSubRoute::getAcomnLoad(unsigned int index) const {
    return _loaded[index];
}
double vrpSubRoute::getUseTime(unsigned int index) const {
    return _start[index] + _problem->getStop(at(index))->ServiceTime;
} 
double vrpSubRoute::getComingTime(unsigned int index) const {
    if(index == 0)
        return _coming_time;
    return _start[index - 1] + _problem->getStop(at(index - 1))->ServiceTime
                + _problem->getTime(at(index - 1), at(index));
}
double vrpSubRoute::getTotalMoveDist() const {
    return _total_move_dist;
}

double vrpSubRoute::getTotalWaitTime() const {
    return _total_wait_time;
}

double vrpSubRoute::getTotalLoad() const {
    return _total_load;
}

double vrpSubRoute::getTotalMoveTime() const {
    return _total_move_time;
}

double vrpSubRoute::getTotalServicesTime() const {
    return _total_service_time;
}
double vrpSubRoute::getDistance(unsigned int index) const {
    return _dist[index];
}
double vrpSubRoute::getTotalUseTime() const {
    return _total_move_time + 
           _total_service_time + 
           _total_wait_time;
}

vector<unsigned int> vrpSubRoute::getGroup() const {
    return _group_list;
}
vrpConst* vrpSubRoute::getParameter() const {
    return _const;
}
double vrpSubRoute::getDist(unsigned int from, unsigned int to) const {
    return _dist[to] - _dist[from];
}
void vrpSubRoute::setProblem(vrpProblem *problem) {
    _problem = problem;
}
void vrpSubRoute::setComingTime(double value) {
    _coming_time = value;
}
void vrpSubRoute::setRestDist(double value) {
    _init_res_dist = value;
}

double vrpSubRoute::getShapeMetric() const {
    double result = 0;
    for(unsigned int i = 0; i < size(); i++) {  
        result += abs(_problem->getStop(at(i))->X - _x_center) 
                + abs(_problem->getStop(at(i))->Y - _y_center);
    }    
    result *=  FEET_TO_MILES;
    return result;
}
double vrpSubRoute::getShapeMetric(unsigned int index) const {
    double result = 0;
    result += abs(_problem->getStop(at(index))->X - _x_center);
    result += abs(_problem->getStop(at(index))->Y - _y_center);
    result *= FEET_TO_MILES; 
    return result;
}
double vrpSubRoute::getCenterX() const {
    return _x_center;
}
double vrpSubRoute::getCenterY() const {
    return _y_center;
}
void vrpSubRoute::printOn(ostream& os) const {
    for(unsigned int i = 0; i < size(); i++) {       
        os << *_problem->getStop(at(i)) << " ";    
    }
}
void vrpSubRoute::debug(ostream &os) {
    os << "---------------------------------------------"
            "---------------------------------------------\n";
    os << "Total move dist: "<< _total_move_dist << endl;
    os << "Total move time: "<< _total_move_time << endl;
    os << "Total wait time: "<< _total_wait_time << endl;
    os << "Total service time: "<< _total_service_time << endl;
    os << "Total load: "<< _total_load << endl;
    os << "Total use time: "<< getTotalUseTime() << endl;
    os << "Cost: "<< _cost << endl;
    os << "Group: ";
    vector<unsigned int> groups = _group_list;
    for(unsigned int i = 0; i < groups.size(); i++)
        os << groups[i] <<" ";
    os << endl;
    
    os << "Size of route: " << size() << endl;    
    if(size() > 0) {
        os << "ID\tX\tY\tEarly\tLate\tStart\tService\tWait\tAcomn\tLoad\tGroup\tType\n";
        for(unsigned int i = 0; i < size(); i++) {
            vrpStop* stop = _problem->getStop(at(i));
            os << stop->ID << "\t";
            os << (int)stop->X << "\t";
            os << (int)stop->Y << "\t";
            os << (int)stop->EarlyTime << "\t";
            os << (int)stop->LateTime << "\t";
            os << (int)_start[i] << "\t";
            os << (int)stop->ServiceTime << "\t";
            os << (int)_waiting[i] << "\t";
            os << (int)_loaded[i] << "\t";
            os << (int)stop->Load << "\t";
            os << stop->Group << "\t";
            os << stop->Type << "\t\n";
        }      
    } 
}
void vrpSubRoute::setConst(vrpConst* _const) {
    this->_const = _const;
}
edaSolution& vrpSubRoute::operator = (const edaSolution &sol) {
    vrpSubRoute &mySubRoute = (vrpSubRoute&) sol;    
    return operator = (mySubRoute);
}
vrpSubRoute& vrpSubRoute::operator = (const vrpSubRoute &sub) {
    vector<unsigned int>::operator =(sub);
    _init_res_dist = sub._init_res_dist;
    _total_service_time = sub._total_service_time;
    _total_move_dist = sub._total_move_dist;
    _total_move_time = sub._total_move_time;
    _total_wait_time = sub._total_wait_time;  
    _total_load = sub._total_load;
    _coming_time = sub._coming_time;   
    _group_list = sub._group_list;	
    _problem = sub._problem;
    _const = sub._const;
    _cost = sub._cost;    
    _start = sub._start;
    _waiting = sub._waiting;
    _loaded = sub._loaded;  
    _dist =sub._dist;
  return *(this);
}
bool vrpSubRoute::operator == (const edaSolution &sol) const{
    vrpSubRoute &mySubRoute = (vrpSubRoute&) sol;
    unsigned int size = mySubRoute.size();
    if(size != this->size())
        return false;
    for(unsigned int i = 0; i < size; i++)
        if(this->at(i) != mySubRoute[i])
            return false;
    return true;
}

void vrpSubRoute::addGroup(vrpStop* stop) {
    if(stop->Group == NON_GROUP) return;
    for(unsigned int i = 0 ; i < _group_list.size() ; i++)    
        if(_group_list.at(i) == stop->Group) return;       
    _group_list.push_back(stop->Group);  
}

void vrpSubRoute::Serialize(edaBuffer &buf, bool pack ){
    if(pack) {
        unsigned int size = this->size();
        buf.Pack(&size, 1 );
        
        for (unsigned int i = 0; i < size; i++) {
            unsigned int value = at(i);
            buf.Pack(&value, 1);
        }

        for (unsigned int i = 0; i < size; i++) {
            double value = _start[i];
            buf.Pack(&value, 1);
        }        
        
        for (unsigned int i = 0; i < size; i++) {
            double value = _waiting[i];
            buf.Pack(&value, 1);
        }        
        for (unsigned int i = 0; i < size; i++) {
            double value = _loaded[i];
            buf.Pack(&value, 1);
        }
        for (unsigned int i = 0; i < size; i++) {
            double value = _dist[i];
            buf.Pack(&value, 1);
        }
        
        unsigned int groupSize = _group_list.size();
        buf.Pack(&groupSize, 1);
        for (unsigned int i = 0; i < groupSize; i++) {
            unsigned int value = _group_list[i];
            buf.Pack(&value, 1);
        }
        
        buf.Pack(&_init_res_dist, 1);
        buf.Pack(&_total_service_time, 1);
        buf.Pack(&_total_move_dist, 1);
        buf.Pack(&_total_move_time, 1);
        buf.Pack(&_total_wait_time, 1);
        buf.Pack(&_total_load, 1);
        buf.Pack(&_coming_time, 1);
        buf.Pack(&_cost, 1);
        buf.Pack(&_x_center,1);
        buf.Pack(&_y_center,1);
//        _problem->doSerialize(buf, pack);
//        _const->doSerialize(buf, pack);   
    }
    else {
      
        this->clear();
        
        unsigned int size;
        buf.UnPack(&size, 1 );
        
        for (unsigned int i = 0; i < size; i++) {
            unsigned int value;
            buf.UnPack( &value, 1 );
            this->push_back(value);
        }
        
        _start.clear();   
        for (unsigned int i = 0; i < size; i++) {
            double value;
            buf.UnPack( &value, 1 );
            _start.push_back(value);
        }
        
        _waiting.clear();
        for (unsigned int i = 0; i < size; i++) {
            double value;
            buf.UnPack( &value, 1 );
            _waiting.push_back(value);
        }
        
        _loaded.clear();
        for (unsigned int i = 0; i < size; i++) {
            double value;
            buf.UnPack( &value, 1 );
            _loaded.push_back(value);
        }
                
        _dist.clear();
        for (unsigned int i = 0; i < size; i++) {
            double value;
            buf.UnPack( &value, 1 );
            _dist.push_back(value);
        }
                        
        _group_list.clear();        
        unsigned int groupSize;
        buf.UnPack(&groupSize, 1);
        
        for (unsigned int i = 0; i < groupSize; i++) {
            unsigned int value;
            buf.UnPack( &value, 1 );
            _group_list.push_back(value);
        }
        
        buf.UnPack(&_init_res_dist, 1);
        buf.UnPack(&_total_service_time, 1);
        buf.UnPack(&_total_move_dist, 1);
        buf.UnPack(&_total_move_time, 1);
        buf.UnPack(&_total_wait_time, 1);
        buf.UnPack(&_total_load, 1);
        buf.UnPack(&_coming_time, 1);
        buf.UnPack(&_cost, 1);
        buf.UnPack(&_x_center,1);
        buf.UnPack(&_y_center,1);
        
    }


}

//void vrpSubRoute::mergeSub(vrpSubRoute* sub) {
//    vector<unsigned int> list;
//    unsigned int subSize = sub->size();
//    
//    for(unsigned int i = 0; i < subSize; i++) {
//        unsigned int id = sub->at(i);
//        if(_problem->getStop(id)->Type == REGULAR_STOP)
//        list.push_back(id);
//    } 
//    
//
//    if( isLastSub() ) 
//    {
//        insert(begin() + size() - 3, list.begin(), list.end());
//    }
//    else  
//    {
//        insert(begin() + size() - 2, list.begin(), list.end());
//        if( sub->isLastSub() ) push_back( sub->at(subSize - 1) );               
//    }
//    update();    
//}
//
//bool vrpSubRoute::isLastSub() const {
//    return _problem->getStop(at(size() - 1))->Type == DEPOT;
//}

double vrpSubRoute::getCost() const {
    return _cost;
}
