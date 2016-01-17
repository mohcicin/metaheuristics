/* 
 * File:   mtspSolution.cpp
 * Author: Tieu Minh
 * 
 * Created on March 11, 2014, 10:10 PM
 */


#include "mtspSolution.h"
#include "mtspGenne.h"
#include <iterator>
#include <algorithm>

mtspSolution::mtspSolution() {
    _fitness = NAN;
    _graph = NULL;
    _route = NULL;
    _late = NULL;
    _come = NULL;
    _wait = NULL;
    _move = NULL;
    _size = 0;
}

mtspSolution::~mtspSolution() {
    easer();
}

void mtspSolution::set(const edaProblem& pro) {
    mtspProblem& graph = (mtspProblem&) pro;
    _graph = &graph;
}

double mtspSolution::evaluate() {
    checkError();
    if (eda::isNAN(_fitness)) {

        _fitness = 0;
        unsigned int _depot = depot();
        unsigned int waittime = 0;
        unsigned int latetime = 0;
        unsigned int movetime = 0;

        _come[_route[_depot]] = _graph->early(_route[_depot]);
        _move[_route[_depot]] = 0;
        for (unsigned int i = 0; i < _size; i++) {
            unsigned int here = (_depot + i) % _size;
            unsigned int next = (_depot + i + 1) % _size;
            _move[_route[here]] = _graph->time(_route[here], _route[next]);
            _come[_route[next]] = _come[_route[here]] + _wait[_route[here]]
                    + _move[_route[here]];
            int wait_here = _graph->early(_route[next]) - _come[_route[next]];
            int late_here = _come[_route[next]] - _graph->late(_route[next]);
            _wait[_route[next]] = wait_here > 0 ? wait_here : 0;
            _late[_route[next]] = late_here > 0 ? late_here : 0;

            latetime += _late[_route[next]];
            waittime += _wait[_route[next]];
            movetime += _move[_route[here]];
        }
        _fitness -= movetime;
        _fitness -=  latetime*_graph->latePenalty();
        _fitness -=  waittime*_graph->waitPenalty();
    }

    return _fitness;
}

void mtspSolution::update() {
    
    checkError();
    _fitness = 0;
    
    unsigned int _depot = depot();
    unsigned int waittime = 0;
    unsigned int latetime = 0;
    unsigned int movetime = 0;

    _come[_route[_depot]] = _graph->early(_route[_depot]);
    _move[_route[_depot]] = 0;
    for (unsigned int i = 0; i < _size; i++) {
        unsigned int here = (_depot + i) % _size;
        unsigned int next = (_depot + i + 1) % _size;
        _move[_route[here]] = _graph->time(_route[here], _route[next]);
        _come[_route[next]] = _come[_route[here]] + _wait[_route[here]]
                + _move[_route[here]];
        int wait_here = _graph->early(_route[next]) - _come[_route[next]];
        int late_here = _come[_route[next]] - _graph->late(_route[next]);
        _wait[_route[next]] = wait_here > 0 ? wait_here : 0;
        _late[_route[next]] = late_here > 0 ? late_here : 0;
        
        latetime += _late[_route[next]];
        waittime += _wait[_route[next]];
        movetime += _move[_route[here]];
    }
    _fitness -= movetime;
    _fitness -= latetime*_graph->latePenalty();
    _fitness -= waittime*_graph->waitPenalty();
}

void mtspSolution::init() {
    graphError();

    _size = _graph->size();
    _route = new unsigned int[_size];
    _come = new unsigned int[_size];
    _wait = new unsigned int[_size];
    _late = new unsigned int[_size];
    _move = new unsigned int[_size];
    for (unsigned int i = 0; i < _size; i++) {
        _route[i] = i;
        _come[i] = _wait[i] = _late[i] = _move[i] = 0;
    }
    // Swap cities
    for (unsigned int i = 0; i < _size; i++) {
        unsigned int j = eda::rnd.random(_size);
        eda::swap(_route[i], _route[j]);
    }

    // Set NAN vale for route length
    set(NAN);
}

mtspSolution* mtspSolution::clone() const {
    mtspSolution* sol = new mtspSolution();
    sol->_size = _graph->size();
    sol->_route = new unsigned int[_size];
    sol->_wait = new unsigned int[_size];
    sol->_come = new unsigned int[_size];
    sol->_late = new unsigned int[_size];
    sol->_move = new unsigned int[_size];
    for (unsigned int i = 0; i < _size; i++) {
        sol->_route[i] = _route[i];
        sol->_wait[i] = _wait[i];
        sol->_come[i] = _come[i];
        sol->_late[i] = _late[i];
        sol->_move[i] = _move[i];
    }
    sol->_graph = _graph;
    sol->_fitness = _fitness;
    return sol;
}
void mtspSolution::print(ostream& os) const {
    checkError();
    unsigned int _depot = depot();
    for (unsigned int i = 0; i < _size; i++) {
        os << _route[(_depot + i) % _size] << " ";
    }
}
void mtspSolution::info(ostream& os) const {
    checkError();

    unsigned int _depot = depot();

    os << "ID " << "\t" << "Come" << "\t" << "Wait" << "\t" << "Late"
           << "\t" << "Move" << "\t" << "EARLY" << "\t" << "LATE" << endl;
    os << _route[_depot] << "\t" << _graph->early(_route[_depot]) << "\t" << 0
            << "\t" << 0 << "\t" << _graph->time(_route[_depot], _route[(_depot + 1)%_size])
            << "\t" << _graph->early(_route[_depot])
            << "\t" << _graph->late(_route[_depot])  << endl;

    for (unsigned int i = 1; i <= _size; i++) {
        unsigned int here = (_depot + i) % _size;
        os << _route[here] 
                << "\t" << _come[_route[here]] 
                << "\t" << _wait[_route[here]]
                << "\t" << _late[_route[here]] 
                << "\t" << _move[_route[here]] 
                << "\t" << _graph->early(_route[here]) 
                << "\t" << _graph->late(_route[here])  << endl;
    }

    //    os << _route[0];
    //    for (unsigned int i = 1; i < _size; i++) {
    //        os << " " << _route[i];
    //    }
}

void mtspSolution::set(const double fitness) {
    _fitness = fitness;
}

void mtspSolution::easer() {
    _fitness = NAN;
    _graph = NULL;
    _size = 0;
    if (_route != NULL) {
        delete[] _route;
    }
    if (_wait != NULL) {
        delete[] _wait;
    }
    if (_late != NULL) {
        delete[] _late;
    }
    if (_come != NULL) {
        delete[] _come;
    }
    if (_move != NULL) {
        delete[] _move;
    }
}

const unsigned int mtspSolution::at(unsigned int index) const {
    return _route[index];
}

unsigned int& mtspSolution::at(unsigned int index) {
    return _route[index];
}

unsigned int mtspSolution::size() const {
    return _size;
}

const mtspProblem& mtspSolution::pro() const {
    graphError();

    return *_graph;
}

unsigned int& mtspSolution::operator[](unsigned int index) {
    return at(index);
}

const unsigned int mtspSolution::operator[](unsigned int index) const {
    return at(index);
}

mtspSolution& mtspSolution::operator=(const edaSolution& sol) {
    easer();
    const mtspSolution& route = (mtspSolution&) sol;
    _fitness = route._fitness;
    _graph = route._graph;
    _size = route._size;
    _route = new unsigned int[_size];
    _come = new unsigned int[_size];
    _wait = new unsigned int[_size];
    _late = new unsigned int[_size];
    _move = new unsigned int[_size];
    for (unsigned int i = 0; i < _size; i++) {
        _route[i] = route._route[i];
        _come[i] = route._come[i];
        _wait[i] = route._wait[i];
        _late[i] = route._late[i];
        _move[i] = route._move[i];
    }
    return *this;
}

mtspSolution::mtspSolution(const edaProblem& pro) {
    mtspSolution();
    set(pro);
}

void mtspSolution::save(const char* filename) {
    //    checkError();
    //    
    //    ofstream file;
    //    file.open(filename);
    //    
    //    unsigned int size = this->size();
    //    for(unsigned int i = 0; i < size; i++)
    //        file << _graph->x(at(i)) << " ";
    //    file << endl;
    //    
    //    for(unsigned int i = 0; i < size; i++)
    //        file << _graph->y(at(i)) << " ";
    //    file.close();
}

unsigned int mtspSolution::depot() const {
    for (unsigned int i = 0; i < _size; i++) {
        if (_route[i] == 0)
            return i;
    }
    throw edaException(this, "There is no depot in the route !");
}

void mtspSolution::serialize(edaBuffer& buf, bool pack) {
    if (pack) {
        buf.pack(&_size);
        buf.pack(_come, _size);
        buf.pack(_wait, _size);
        buf.pack(_late, _size);
        buf.pack(_route, _size);
        buf.pack(_move, _size);
        buf.pack(&_fitness);

    } else {
        easer();
        buf.unpack(&_size);
        _come = new unsigned int[_size];
        _wait = new unsigned int[_size];
        _late = new unsigned int[_size];
        _route = new unsigned int[_size];
        _move = new unsigned int[_size];
        buf.unpack(_come, _size);
        buf.unpack(_wait, _size);
        buf.unpack(_late, _size);
        buf.unpack(_route, _size);
        buf.unpack(_move, _size);
        buf.unpack(&_fitness);
    }
}


bool mtspSolution::operator==(const edaSolution& sol) const {
    const mtspSolution& route = (mtspSolution&) sol;
    if (route.size() != _size) {
        return false;
    }
    for (unsigned int i = 0; i < _size; i++) {
        if (route._route[i] != _route[i]) {
            return false;
        }
    }
    return true;
}

const char* mtspSolution::className() const {
    return "mtspSolution";
}

void mtspSolution::checkError() const {
    graphError();

    initError();
}

void mtspSolution::graphError() const {
    if (_graph == NULL)
        throw edaException(this, "Not set graph !");
    _graph->checkError();
}

void mtspSolution::initError() const {
    if (_size == 0)
        throw edaException(this, "Not initial the route !");
    if (_size != _graph->size())
        throw edaException(this, "The route not satisfy the graph !");
}

void mtspSolution::decode(const edaChromosome& chro) {
    unsigned int size = chro.length();
    for (unsigned int i = 0; i < size; i++) {
        mtspGenne* genne = (mtspGenne*) chro.at(i);
        at(i) = *genne;
    }
    _fitness = NAN;
}

edaChromosome* mtspSolution::encode() const {
    edaChromosome* chro = new edaChromosome();
    unsigned int size = this->size();
    for (unsigned int i = 0; i < size; i++) {
        mtspGenne genne = at(i);
        chro->add(genne);
    }
    return chro;
}

