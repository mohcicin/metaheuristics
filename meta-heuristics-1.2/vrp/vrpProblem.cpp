/* 
 * File:   vrpProblem.cpp
 * Author: Administrator
 * 
 * Created on June 7, 2012, 4:42 PM
 */

#include <algorithm>

#include "vrpProblem.h"

vrpProblem::vrpProblem()
  : _dist(NULL), _conflict_group(NULL), _list_stops (NULL) {}

vrpProblem::vrpProblem(const vrpProblem& problem) {
    this->_num_stops = problem._num_stops;
    this->_capacity_veh = problem._capacity_veh;
    this->_speed = problem._speed;
    this->_max_total_dist = problem._max_total_dist;
    this->_max_total_stop = problem._max_total_stop;
    this->_list_stops = new vrpStop[this->_num_stops ];
    memcpy(this->_list_stops, problem._list_stops, sizeof(vrpStop) * _num_stops);
    this->_dist = new double [_num_stops * _num_stops];
    memcpy(this->_dist, problem._dist, sizeof(double) * _num_stops * _num_stops);
    _conflict_group = problem._conflict_group->clone(); 
}
vrpProblem::vrpProblem(const char *filename)
  : _dist(NULL), _conflict_group(NULL), _list_stops (NULL) 
{
  load(filename);
}

vrpProblem::~vrpProblem() {
  easer();
}

vrpProblem* vrpProblem::clone() const {
    return new vrpProblem(*this);
}
void vrpProblem::load(const char* filename) {
  easer();  
  ifstream file(filename);
  cout << ">> Loading [" << filename << "]" << endl;
  double buffer;
  if (file) 
  {  
      file >> _num_stops;         //read the number of stops
      file >> _capacity_veh;      //read the capacity of vehicle
      file >> _speed;             //speed of vehicle     
      file >> _max_total_dist;    //get maximum total dist of a vehicle   
      _list_stops = new vrpStop[_num_stops];

      //read all property of stops    
      for (unsigned int i = 0; i < _num_stops; i++) {	
          file >> buffer;
          _list_stops[i].ID = (unsigned int)buffer;
          file >> buffer;
          _list_stops[i].X = buffer;
          file >> buffer;
          _list_stops[i].Y = buffer;
          file >> buffer;
          _list_stops[i].EarlyTime = getMinutes(buffer); 
          file >> buffer;
          _list_stops[i].LateTime = getMinutes(buffer); 
          file >> buffer;
          _list_stops[i].ServiceTime = buffer/60; 
          file >> buffer;
          _list_stops[i].Load = buffer;
          file >> buffer;
          _list_stops[i].Type = (unsigned int)buffer;	    
      }	    
      //get information about conflict stops
      unsigned int count_group;    
      file >> count_group; //number of the group customer
      for(unsigned int i = 0 ; i < _num_stops ; i++) {
          if(_list_stops[i].Type != REGULAR_STOP)        
              _list_stops[i].Group = NON_GROUP;        
          else        
              _list_stops[i].Group = _list_stops[i].ID % count_group;        
      }
      _conflict_group = new vrpGroupConflict(count_group);
      unsigned int group_A, group_B;
      while(file >> group_A >> group_B )    
          _conflict_group->pushConflictGroup(group_A, group_B); 
      file.close();
      computeDistances();    
  }
  else 
  {
      //file is not exist
      cerr << filename << " doesn't exist!" << endl;
      exit(1);
  }
}

unsigned int vrpProblem::getNumStops() const {
    return _num_stops;
}

vrpStop* vrpProblem::getStop(const unsigned int id) const {
	return &_list_stops[id];
/*  vrpStop* stop = &_list_stops[id];
  if(stop->ID == id)
    return stop;
  else {
    for(unsigned int i = 0; i < _num_stops; i++) {
      stop = &_list_stops[i];
      if(stop->ID == id)
        return stop;
    }
  }
  return NULL;
*/  
}

double vrpProblem::getMaxTotalDist() const {
    return _max_total_dist;
}

double vrpProblem::getMinutes(const double hour_minute) const {
	unsigned hour = (unsigned int) hour_minute / 100 ;
	unsigned minute = (unsigned int) hour_minute % 100;
	return (hour * 60) + minute;
}

double vrpProblem::getDist(const unsigned int id_1, const unsigned int id_2) const {
    return _dist[id_1 * _num_stops + id_2];
}

double vrpProblem::getTime(const unsigned int id_1, const unsigned int id_2) const {
    return getDist(id_1, id_2)/(_speed/60);
}

double vrpProblem::getMaxCapacity() const {
    return _capacity_veh;
}

bool vrpProblem::isConflict(const unsigned int group, const vector<unsigned int>& groups) const {
    return _conflict_group->isConflict(group,groups);
} 
bool vrpProblem::isConflict(const vector<unsigned int>& groups) const {
    return _conflict_group->isConflict(groups);
}
void vrpProblem::computeDistances() {
//	if (_dist) delete[] _dist;	
    _dist = new double[_num_stops * _num_stops];
    bzero(_dist, _num_stops * _num_stops * sizeof(double));
    double distX, distY;
	// Computations.
	for (unsigned int i = 0; i < _num_stops; i++) {
		for (unsigned int j = i + 1; j < _num_stops; j ++) {
			distX =  _list_stops[i].X - _list_stops[j].X;
			distY =  _list_stops[i].Y - _list_stops[j].Y;
			_dist[i*_num_stops + j] = _dist[j*_num_stops + i] = (abs(distX) + abs(distY)) * FEET_TO_MILES;			
		}
	}
}

void vrpProblem::printOn(ostream& os) const {
    os << "Number stop: " << _num_stops << endl;
    os << "Max capacity for vehicle: " << _capacity_veh << endl;
    os << "Max distance vehicle can move: " << _max_total_dist << endl;
    os << "Speed of vehicle: " << _speed << endl;
    os << "ID\tX\tY\tEarly\tLate\tService\tLoad\tType\tGroup\n";
    for(unsigned int i=0; i <_num_stops;i++) {
        os << (int)_list_stops[i].ID << "\t";
        os << (int)_list_stops[i].X << "\t";
        os << (int)_list_stops[i].Y << "\t";
        os << (int)_list_stops[i].EarlyTime<< "\t";
        os << (int)_list_stops[i].LateTime << "\t";
        os << (int)_list_stops[i].ServiceTime<< "\t";
        os << (int)_list_stops[i].Load << "\t";
        os << (int)_list_stops[i].Type << "\t";
        os << (int)_list_stops[i].Group;
        os << endl;
    }
}
void vrpProblem::printTable(const char* file_name) {
    ofstream os(file_name,ios::trunc);
    os << "ID,X,Y,Early,Late,Service,Load,Type,Group\n";
    for(unsigned int i=0; i <_num_stops;i++) {
        os << (int)_list_stops[i].ID << ",";
        os << (int)_list_stops[i].X << ",";
        os << (int)_list_stops[i].Y << ",";
        os << (int)_list_stops[i].EarlyTime<< ",";
        os << (int)_list_stops[i].LateTime << ",";
        os << (int)_list_stops[i].ServiceTime<< ",";
        os << (int)_list_stops[i].Load << ",";
        os << (int)_list_stops[i].Type << ",";
        os << (int)_list_stops[i].Group <<"\n";
    }
    os.close();
}
void vrpProblem::Serialize(edaBuffer &buf, bool pack) {
  if ( pack )
  {
    _conflict_group->doSerialize(buf,pack);
    buf.Pack( &_num_stops, 1 );
    buf.Pack( &_speed, 1 );
    buf.Pack( &_capacity_veh, 1 );
    buf.Pack( &_max_total_dist, 1 );
    for (unsigned int i=0; i < _num_stops; i++)
      _list_stops[i].doSerialize(buf,pack);
            buf.Pack( _dist, _num_stops * _num_stops );
	} 
  else 
  {
    _conflict_group = (vrpGroupConflict*)classGenerateFromBuffer( buf );
    buf.UnPack( &_num_stops, 1 );
    buf.UnPack( &_speed, 1 );
    buf.UnPack( &_capacity_veh, 1 );
    buf.UnPack( &_max_total_dist, 1 );
    if (_list_stops == NULL) delete[] _list_stops;
    _list_stops = new vrpStop[_num_stops];
    vrpStop *stop;
    for (unsigned int i = 0; i < _num_stops; i++) {
        stop = (vrpStop*)classGenerateFromBuffer(buf);
        _list_stops[i]=*stop;
    }
    if (_dist == NULL) delete[] _dist;
    _dist = new double[_num_stops * _num_stops];
    buf.UnPack(_dist, _num_stops * _num_stops);
  }
}

vrpProblem& vrpProblem::operator = (const edaProblem &pro) 
{ 
  easer();    
  vrpProblem& problem = (vrpProblem&)pro;
  this->_num_stops = problem._num_stops;
  this->_capacity_veh = problem._capacity_veh;
  this->_speed = problem._speed;
  this->_max_total_dist = problem._max_total_dist;
  this->_max_total_stop = problem._max_total_stop;
  this->_list_stops = new vrpStop[this->_num_stops];
  memcpy(this->_list_stops, problem._list_stops, sizeof(vrpStop) * _num_stops);
  this->_dist = new double [_num_stops * _num_stops];
  memcpy(this->_dist, problem._dist, sizeof(double) * _num_stops * _num_stops);
  _conflict_group = problem._conflict_group->clone(); 
  return (*this);
}

void vrpProblem::easer() {
  if (_dist != NULL) 
  {
    delete[] _dist;
    _dist = NULL;
  }
  if(_conflict_group != NULL) 
  {
    delete _conflict_group;
    _conflict_group = NULL;
  }
  if(_list_stops != NULL) 
  {
    delete[] _list_stops;
    _list_stops = NULL;
  }
}
vector<vrpStop*> vrpProblem::getLandfill() const {
  vector<vrpStop*> _landfill;
  for(unsigned int i = 0; i < _num_stops; i++) {
    vrpStop* stop = &_list_stops[i];
    if (stop->Type == LANDFILL)
      _landfill.push_back(stop);
  }
  return _landfill;
}
vector<vrpStop*> vrpProblem::getRegularStop() const { 
  vector<vrpStop*> _regular_stop;
  for(unsigned int i = 0; i < _num_stops; i++) {
    vrpStop* stop = &_list_stops[i];
    if (stop->Type == REGULAR_STOP)
      _regular_stop.push_back(stop);
  }
  return _regular_stop;
}
vrpStop* vrpProblem::getDepot() const {
  for(unsigned int i = 0; i < _num_stops; i++) {
    vrpStop* stop = &_list_stops[i];
    if(stop->Type == DEPOT) return stop;
  }   
  return NULL;
}