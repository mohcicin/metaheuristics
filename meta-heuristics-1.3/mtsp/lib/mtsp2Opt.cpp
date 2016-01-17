/* 
 * File:   mtsp2Opt.cpp
 * Author: Tieu Minh
 * 
 * Created on March 19, 2014, 10:10 PM
 */

#include "mtsp2Opt.h"

mtsp2Opt::mtsp2Opt() : mtspNeighbour() 
{
}

mtsp2Opt::mtsp2Opt(const mtspSolution& route)
{
    mtspNeighbour::set(route);
}

mtsp2Opt::~mtsp2Opt() 
{
    easer();
}

void mtsp2Opt::init() 
{
    checkError();
    _first = 0;
    _second = _first + 2;
    _gain = NAN;
}

void mtsp2Opt::print(ostream& os) const 
{
    checkError();
    cout << "2-opt [" << _first << "; " << _second << "]";  
}

void mtsp2Opt::update(edaSolution& sol) 
{
    checkError();  
    
    mtspSolution& route = (mtspSolution&) sol;    
    route.checkError();
    
    if(route == *_route)
    {        
        for(unsigned int i = 1; i <= (_second + 1 - _first)/2; i++)
        {           
            eda::swap( route[_first + i], route[_second - i + 1] ); 
        }
        route.update();
    }
    else
    {
        throw edaException(this, "The input solution is not same the solution in the neighbor !");
    }
}

mtsp2Opt* mtsp2Opt::clone() const 
{
    mtsp2Opt* move = new mtsp2Opt();
    move->_first = _first;
    move->_second = _second;
    move->_gain = _gain;
    move->_route = _route;
    return move;
}

void mtsp2Opt::serialize(edaBuffer& buf, bool pack) {
    mtspNeighbour::serialize(buf, pack);
    if(pack)
    {
        buf.pack( &_first );
        buf.pack( &_second );
    }
    else
    {
        buf.unpack( &_first );
        buf.unpack( &_second );
    }
}

double mtsp2Opt::evaluate() 
{    
    checkError();
    if( eda::isNAN(_gain) ) 
    {        
        mtspSolution* newRoute = _route->clone();
        _gain = newRoute->evaluate();        
        update(*newRoute);
        _gain = newRoute->evaluate() - _gain;  
        delete newRoute;
    }
    return _gain;
}

void mtsp2Opt::next() 
{
    checkError();
    _gain = NAN;
    unsigned int size = _route->size();
    if ( (_first == size - 4) && (_second == _first + 3) )
    {
        _first = 0;
        _second = _first + 2;
    }
    else 
    {
        _second++;
        if (_second == size)
        {
          _first++;
          _second = _first + 2;
        }
    }  
}

void mtsp2Opt::rand() 
{
    checkError();
    _gain = NAN;
    unsigned int size = _route->size();
    _first = eda::rnd.random(0, size - 4);
    _second = eda::rnd.random(_first + 2, size - 1); 
}

mtsp2Opt& mtsp2Opt::operator =(const edaNeighbour& neighb) 
{
    const mtsp2Opt& opt = (mtsp2Opt&) neighb;
    _route = opt._route;
    _gain = opt._gain;
    _first = opt._first;
    _second = opt._second;
    return *this;
}

const char* mtsp2Opt::className() const 
{
    return "mtsp2Opt";
}

bool mtsp2Opt::operator ==(const edaNeighbour& neighb) const 
{
    const mtsp2Opt& opt = (mtsp2Opt&) neighb;
    return (_first == opt._first && _second == opt._second);
}
