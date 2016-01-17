/* 
 * File:   vrpGroupConflict.cpp
 * Author: Administrator
 * 
 * Created on June 7, 2012, 4:52 PM
 */

#include "vrpGroupConflict.h"

vrpGroupConflict::vrpGroupConflict():_size(0), _matrix(NULL) {}

vrpGroupConflict::vrpGroupConflict(const vrpGroupConflict& group) {
    _size = group._size;
    _matrix = new bool [_size*_size];
    memcpy(_matrix, group._matrix, sizeof(bool) * _size * _size);
}

vrpGroupConflict::vrpGroupConflict(const unsigned int size) {
    _size = size;
    _matrix = new bool [_size*_size];
    fill(_matrix, _matrix + _size*_size, false);  
}

vrpGroupConflict* vrpGroupConflict::clone() const {
    return new vrpGroupConflict(*this);
}

vrpGroupConflict::~vrpGroupConflict() {
    easer();
}

void vrpGroupConflict::pushConflictGroup(unsigned int group_A,unsigned int group_B)  {
    _matrix[group_A * _size + group_B] = true;
    _matrix[group_B * _size + group_A ] = true;
}

bool vrpGroupConflict::isConflict(const unsigned int group, const vector<unsigned int>& groups) const {
    if(group == NON_GROUP) return false;
    for(unsigned int i = 0 ; i < groups.size() ; i++) 
        if(_matrix[groups[i]*_size + group ]) 
            return true;    
    return false;
}

bool vrpGroupConflict::isConflict(const vector<unsigned int>& groups) const {
    for(unsigned int i = 0 ; i < groups.size(); i++) 
        for(unsigned int j = i + 1; j < groups.size(); j++) 
            if(_matrix[groups[i]*_size + groups[j]] ) return true;    
    return false;
}
void vrpGroupConflict::prinOn(ostream& os) const {
    
}

void vrpGroupConflict::Serialize(edaBuffer &buf, bool pack)
{
    if ( pack ){       
        buf.Pack( &_size, 1 );
        buf.Pack( _matrix, _size * _size );

    } 
    else {
        easer();
        buf.UnPack( &_size, 1 );
        _matrix = new bool[_size * _size];
        buf.UnPack( _matrix, _size * _size );
    }
}


void vrpGroupConflict::easer() {
    if(_matrix != NULL) {
        delete [] _matrix;
        _matrix = NULL;
    }
}
