/* 
 * File:   mtspProblem.cpp
 * Author: Tieu Minh
 * 
 * Created on March 11, 2015, 8:31 PM
 */

#include "mtspProblem.h"
#include <fstream>

mtspProblem::mtspProblem() {
    _numVert = 0;
    _speed = 0;
    _waitPenalty = 0;
    _latePenalty = 0;
    _distance = NULL;
    _early = _late = NULL;
    _x = _y = NULL;
    strcpy(_problemFile, "");
    strcpy(_configFile, "");
}

mtspProblem::mtspProblem(const char* problemFile, const char* configFile) {
    _distance = NULL;
    _early = _late = NULL;
    _x = _y = NULL;
    config(configFile);
    load(problemFile);
}

mtspProblem::~mtspProblem() {
    easer();
}

unsigned int mtspProblem::size() const {
    return _numVert;
}

double mtspProblem::speed() const {
    return _speed;
}

double mtspProblem::distance(unsigned int from, unsigned int to) const {
    return _distance[from][to];
}

unsigned int mtspProblem::time(unsigned int from, unsigned int to) const {
    double speed = _speed * 1000 / 60;
    return ceil(_distance[from][to] / speed);
    
}

void mtspProblem::easer() {
    strcpy(_problemFile, "");

    if (_distance != NULL) {
        for (unsigned int i = 0; i < _numVert; i++) {
            if (_distance[i] != NULL) {
                delete[] _distance[i];
                _distance[i] = NULL;
            }
        }
        delete[] _distance;
    }
    if (_early != NULL) {
        delete[] _early;
    }
    if (_late != NULL) {
        delete[] _late;
    }
    if (_x != NULL) {
        delete[] _x;
    }
    if (_y != NULL) {
        delete[] _y;
    }
    _x = _y = NULL;
    _late = _early = NULL;
    _distance = NULL;
    _numVert = 0;
    _waitPenalty = 0;
    _latePenalty = 0;
    _speed = 0;
}

double mtspProblem::x(unsigned int index) const {
    return _x[index];
}

double mtspProblem::y(unsigned int index) const {
    return _y[index];
}

double mtspProblem::early(unsigned int index) const {
    return _early[index] / 100 * 60 + _early[index] % 100;
}

double mtspProblem::late(unsigned int index) const {

    return _late[index] / 100 * 60 + _late[index] % 100;
}

void mtspProblem::config(const char* filename) {
    // Get file name
    strcpy(_configFile, filename);

    // Read file
    if (strcmp(_configFile, "") == 0) {
        _waitPenalty = 0;
        _latePenalty = 20;
    } else {
        ifstream file(filename);
        if (file) {
            char text[256];
            char value[256];
            while (file >> text >> value) {
                if (strcmp(text, "WAIT_PENALTY_RATIO") == 0)
                    sscanf(value, "%d", &_waitPenalty);
                else if (strcmp(text, "LATE_PENALTY_RATIO") == 0)
                    sscanf(value, "%d", &_latePenalty);
            }
            file.close();
        }
    }
}

void mtspProblem::load(const char* filename) {

    // Get file name
    strcpy(_problemFile, filename);

    // Read file
    ifstream file(_problemFile);
    if (file) {

        file >> _numVert;
        file >> _speed;

        _distance = new double*[_numVert];
        _x = new double[_numVert];
        _y = new double[_numVert];
        _early = new unsigned int[_numVert];
        _late = new unsigned int[_numVert];
        for (unsigned int i = 0; i < _numVert; i++) {
            _distance[i] = new double[_numVert];
            file >> _x[i] >> _y[i] >> _early[i] >> _late[i];
        }
        for (unsigned int i = 0; i < _numVert; i++) {
            for (unsigned int j = 0; j < _numVert; j++) {
                file >> _distance[i][j];
            }
        }
        file.close();
    } else {
        string error = "The file name '";
        error += filename;
        error += "' is not existing !";
        throw edaException(this, error);
    }
}

mtspProblem* mtspProblem::clone() const {
    mtspProblem* result = new mtspProblem();

    strcpy(result->_problemFile, _problemFile);

    result->_numVert = _numVert;
    result->_speed = _speed;
    result->_waitPenalty = _waitPenalty;
    result->_latePenalty = _latePenalty;
    result->_distance = new double*[_numVert];
    for (unsigned int i = 0; i < _numVert; i++) {
        result->_distance[i] = new double[_numVert];
        memcpy(result->_distance[i], _distance[i], _numVert * sizeof (double));
    }

    result->_x = new double[_numVert];
    memcpy(result->_x, _x, sizeof (double) * _numVert);

    result->_y = new double[_numVert];
    memcpy(result->_y, _y, sizeof (double) * _numVert);

    result->_late = new unsigned int[_numVert];
    memcpy(result->_late, _late, sizeof (unsigned int) * _numVert);

    result->_early = new unsigned int[_numVert];
    memcpy(result->_early, _early, sizeof (unsigned int) * _numVert);

    return result;
}

void mtspProblem::print(ostream& os) const {
    checkError();
    os << ">> File [" << _problemFile << "]" << endl;
    os << ">> Speed = " << _speed << " (km/h)" << endl;
    os << ">> Wait penalty = " << _waitPenalty << endl;
    os << ">> Late penalty = " << _latePenalty << endl;
    os << "ID " << "\t" << "X " << "\t" << "Y "
            << "\t" << "Early" << "\t" << "Late" << endl;

    for (unsigned int i = 0; i < _numVert; i++) {
        os << i << "\t" << _x[i] << "\t" << _y[i]
                << "\t" << early(i) << "\t" << late(i) << endl;
    }
}

void mtspProblem::serialize(edaBuffer& buf, bool pack) {
    if (pack) {
        buf.pack(&_numVert);
        for (unsigned int i = 0; i < _numVert; i++) {
            buf.pack(_distance[i], _numVert);
        }
        buf.pack(_problemFile, 256);
        buf.pack(&_speed);
        buf.pack(&_waitPenalty);
        buf.pack(&_latePenalty);
        buf.pack(_x, _numVert);
        buf.pack(_y, _numVert);
        buf.pack(_late, _numVert);
        buf.pack(_early, _numVert);
    } else {
        easer();
        buf.unpack(&_numVert);
        _distance = new double*[_numVert];
        for (unsigned int i = 0; i < _numVert; i++) {
            _distance[i] = new double[_numVert];
            buf.unpack(_distance[i], _numVert);
        }
        buf.unpack(_problemFile, 256);
        buf.unpack(&_speed);
        buf.unpack(&_waitPenalty);
        buf.unpack(&_latePenalty);
        _x = new double[_numVert];
        buf.unpack(_x, _numVert);
        _y = new double[_numVert];
        buf.unpack(_y, _numVert);
        _late = new unsigned int[_numVert];
        buf.unpack(_late, _numVert);
        _early = new unsigned int[_numVert];
        buf.unpack(_early, _numVert);
    }
}

const char* mtspProblem::className() const {
    return "mtspProblem";
}

void mtspProblem::checkError() const {
    if (strcmp(_problemFile, "") == 0)
        throw edaException(this, "Not load input problem file !");
    if (_numVert == 0)
        throw edaException(this, "The input problem doesn't have the stops !");
}

unsigned int mtspProblem::waitPenalty() const {
    return _waitPenalty;
}

unsigned int mtspProblem::latePenalty() const {
    return _latePenalty;
}