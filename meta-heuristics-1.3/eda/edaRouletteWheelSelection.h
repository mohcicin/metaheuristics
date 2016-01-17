/* 
 * File:   edaWeightSelection.h
 * Author: Tieu Minh
 *
 * Created on April 22, 2014, 3:51 PM
 */

#ifndef EDAROULETTESELECTION_H
#define	EDAROULETTESELECTION_H

#include "edaNaturalSelection.h"


class edaRouletteWheelSelection : public edaNaturalSelection 
{
public:

    edaRouletteWheelSelection(double rate = 0.5) : _weight(NULL)
    {
        set(rate);
    }
    
    virtual ~edaRouletteWheelSelection()
    {        
        easer();
    }
    
    virtual void set(double rate)
    {
        if(rate > 1 || rate < 0)
            throw edaException(this, "The rate value must be set in [0, 1] !");
        _rate = rate;        
    }
      
    
    void init(const edaPopulation& pop) 
    {
        easer();
        unsigned int size = pop.size();
        _weight = new double[size];
        double sum = 0;  
        for(unsigned int i = 0; i < size; ++i)
        {     
            sum += pop[i]->evaluate();        
        }    
        _weight[0] = pop[0]->evaluate() / sum;
        for(unsigned int i = 1; i < size; ++i) 
        { 
            _weight[i] = _weight[i-1] + pop[0]->evaluate()/sum;    
        }
    }
    
    virtual bool update(edaPopulation& pop)
    {
        pop.sort();    
        init( pop );        
        checkError();
        
        unsigned int size = pop.size();
        unsigned int num = (unsigned int)(_rate*size);

        edaSolution **trash = new edaSolution*[num];
        for(unsigned int i = 0; i < num; i++) 
            trash[num - i - 1] = pop.popBack();
        

        for(unsigned int i = 0; i < num; i++) 
        {
            double prob = eda::rnd.uniform();   
            unsigned int index = 0;
            while(_weight[index] < prob) index++;
            edaSolution* sol = index < size - num ? pop[index] : trash[index - size + num] ;
            pop.add(*sol); 
        }
        easerArrayObject(trash, num);     
        return num < size;
    }

    virtual void serialize(edaBuffer& buf, bool pack)
    {
        if(pack)
        {
            buf.pack(&_rate);
        }
        else
        {
            easer();
            buf.unpack(&_rate);            
        }
    }

    virtual edaRouletteWheelSelection* clone() const
    {
        edaRouletteWheelSelection* slect = new edaRouletteWheelSelection();
        slect->_rate = _rate;
        slect->_weight = NULL;
        return slect;
        
    }
    
    virtual void easer() 
    {
        easerArray(_weight);
    }
    
    setClassID(_SYSCLASSID_ + _CLSID_EDAROULETTESELECTION_);
    

    virtual const char* className() const
    {
        return "edaWeightSelection";
    }    

    virtual void checkError() const 
    {
        if(eda::isNAN(_rate))
            throw edaException(this, "The rate is not set !");
        if(_rate > 1 || _rate < 0)
            throw edaException(this, "The rate value must be set in [0, 1] !");
    }
    
protected:
    double* _weight;
    double _rate;
    
   
};

#endif	/* EDAWEIGHTSELECTION_H */

