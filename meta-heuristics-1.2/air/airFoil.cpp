/* 
 * File:   ParametricAirfoil.cpp
 * Author: Tieu Minh
 * 
 * Created on April 22, 2013, 9:04 AM
 */

#include "airFoil.h"

#define rad        0.0174532925199433
#define rle_up     (0.001 * at(0)  + 0.000)
#define rle_lo     (0.001 * at(1)  + 0.000)
#define X_up       (0.01  * at(2)  + 0.00 )
#define Z_up       (0.001 * at(3)  - 0.010)
#define Z_XXup     (0.01  * at(4)  - 10.00) 
#define X_lo       (0.01  * at(5)  + 0.00 ) 
#define Z_lo       (0.001 * at(6)  - 0.300) 
#define Z_XXlo     (0.01  * at(7)  - 10.00) 
#define Z_TE       (0.001 * at(8)  - 0.100) 
#define deltaZ_TE  (0.001 * at(9)  - 0.100) 
#define alpha_TE   (0.01  * at(10) - 50.00) 
#define beta_TE    (0.01  * at(11) - 40.00) 


airFoil::airFoil()
  : vector<double>() {
    resize(12, NAN);
}

airFoil::airFoil(const airFoil& foil)
 : vector<double>(foil) {    
    memcpy(a, foil.a, 6*sizeof(double));
    memcpy(b, foil.b, 6*sizeof(double));
}

airFoil::airFoil(double *foil) {
    resize(12, NAN);
    at(0) =  round( 1000 *  foil[0]           );
    at(1) =  round( 1000 *  foil[1]           );
    at(2) =  round( 100  *  foil[2]           );
    at(3) =  round( 1000 * (foil[3]  + 0.010) );
    at(4) =  round( 100  * (foil[4]  + 10.00) );
    at(5) =  round( 100  *  foil[5]           );
    at(6) =  round( 1000 * (foil[6]  + 0.300) );
    at(7) =  round( 100  * (foil[7]  + 10.00) );
    at(8) =  round( 1000 * (foil[8]  + 0.100) );
    at(9) =  round( 1000 * (foil[9]  + 0.100) );
    at(10) = round( 100  * (foil[10]  + 50.00));
    at(11) = round( 100  * (foil[11] + 40.00) );
    update();
}

void airFoil::printOn(ostream &os) const {
    os << name();
//    os << detail();
 }

string airFoil::detail() const {    
    stringstream  stream("");     
    
    stream << "Leading edge upper radius (in meter): " 
       << rnd.round(rle_up, 3) 
       << endl;
    stream << "Leading edge lower radius (in meter): " 
       << rnd.round(rle_lo, 3) 
       << endl;
    stream << "X coordinate of upper crest: " 
       << rnd.round(X_up, 2) 
       << endl;
    stream << "Z coordinate of upper crest: " 
       << rnd.round(Z_up, 3) 
       << endl;
    stream << "Curvature of upper crest: " 
       << rnd.round(Z_XXup, 2) 
       << endl;
    stream << "X coordinate of lower crest: " 
       << rnd.round(X_lo, 2) 
       << endl;
    stream << "Z coordinate of lower crest: " 
       << rnd.round(Z_lo, 3) 
       << endl;
    stream << "Curvature of lower crest: " 
       << rnd.round(Z_XXlo, 2) 
       << endl;
    stream << "Trailing edge coordinate: " 
       << rnd.round(Z_TE, 3) 
       << endl;
    stream << "Trailing edge thickness (in meter): " 
       << rnd.round(deltaZ_TE, 3) 
       << endl;
    stream << "Trailing edge direction (in deg): " 
       << rnd.round(alpha_TE, 2)
       << endl;
    stream << "Trailing edge wedge angles (in deg): "
       << rnd.round(beta_TE, 2) 
       << endl;
    
    string data = "";
    stream >> data;
    return data;  
}

string airFoil::name() const {     
    stringstream  stream("");
        
    stream  << (unsigned int)at(0) / 10 
            << (unsigned int)at(0) % 10;
    
    stream  << (unsigned int)at(1) / 10 
            << (unsigned int)at(1) % 10;
    
    stream  << (unsigned int)at(2) / 10 
            << (unsigned int)at(2) % 10;
    
    stream  << (unsigned int)at(3) / 100 
            << ((unsigned int)at(3) % 100) / 10 
            << (unsigned int)at(3) % 10;
    
    stream  << (unsigned int)at(4) / 1000 
            << ((unsigned int)at(4) % 1000) / 100 
            << ((unsigned int)at(4) % 100) / 10
            << (unsigned int)at(4) % 10;
    
    stream  << (unsigned int)at(5) / 10 
            << (unsigned int)at(5) % 10;
    
    stream  << (unsigned int)at(6) / 100 
            << ((unsigned int)at(6) % 100) / 10 
            << (unsigned int)at(6) % 10;
    
    stream  << (unsigned int)at(7) / 1000 
            << ((unsigned int)at(7) % 1000) / 100 
            << ((unsigned int)at(7) % 100) / 10
            << (unsigned int)at(7) % 10;
    
    stream  << (unsigned int)at(8) / 100 
            << ((unsigned int)at(8) % 100) / 10 
            << (unsigned int)at(8) % 10;
    
    stream  << (unsigned int)at(9) / 100 
            << ((unsigned int)at(9) % 100) / 10 
            << (unsigned int)at(9) % 10;
    
    stream  << (unsigned int)at(10) / 1000 
            << ((unsigned int)at(10) % 1000) / 100 
            << ((unsigned int)at(10) % 100) / 10
            << (unsigned int)at(10) % 10;
        
    stream  << (unsigned int)at(11) / 1000 
            << ((unsigned int)at(11) % 1000) / 100 
            << ((unsigned int)at(11) % 100) / 10
            << (unsigned int)at(11) % 10;
    string data = "";
    stream >> data;
    return data;  
}

ostream& operator<< (ostream &os, const airFoil &foil) {
    foil.printOn(os);
    return os;
}

airFoil& airFoil::operator = (const airFoil &foil) {
    clear(); 
    vector<double>::operator=(foil);  
    memcpy(a, foil.a, 6*sizeof(double));
    memcpy(b, foil.b, 6*sizeof(double));
    return *this;
}

bool airFoil::operator == (const airFoil &foil) {
    return (vector<double>) 
      (*this) == (vector<double>) (*(&foil));
}

void airFoil::Serialize(edaBuffer &buf, bool pack) {
    if(pack) {        
        unsigned _size = size();
        buf.Pack(&_size, 1);
        for(unsigned int i = 0; i < _size; i++) {  
            double value = at(i);
            buf.Pack(&value);
        }
        buf.Pack(a, 6);
        buf.Pack(b, 6);
    }
    else {
        clear();
        unsigned int _size;
        buf.UnPack(&_size, 1);
        resize(_size);            
        for(unsigned int i = 0; i < _size; i++) { 
            double value;
            buf.UnPack(&value);
            at(i) = value;
        }
        buf.UnPack(a, 6);
        buf.UnPack(b, 6);
    }
}

bool airFoil::incrEval(unsigned int index, unsigned int sign) {
    if(sign == 0)
        at(index) += 1;
    else
        at(index) -= 1;
    update();
    return check();
}


bool airFoil::check() const {
    unsigned int  Ni = 400;
    double pi = 3.1415926535897932;
    
    double *beta = rnd.linspace(0, pi, Ni); 
    double zmax = -1, zmin = 1;
    double zup, zlo;
    for(unsigned int i = 0; i < Ni; i++) {
        double x = (0.5*(1-cos(beta[i])));
        zup = z_up(x);
        zlo = z_lo(x);
        if(zmax < zup)
            zmax = zup;
        if(zmin > zlo) 
            zmin = zlo;    
        //Kiem tra su giao nhau cua 2 mat
        if (x > 0 && x < 1 && zup < zlo ) {          
            delete[] beta;
            return false;
        }
    }
    delete[] beta;
    if(zmax > Z_up || zmin < Z_lo || zmax - zmin > 0.4 || abs(deltaZ_TE) > 0.00001 ) { 
      //Gioi han do day cua canh may bay
        return false;                   
    }
    return true;
}

unsigned int airFoil::size() const {
    return 12;
}

airFoil* airFoil::createFoil(double *Foil) {
    airFoil* foil;
    if(Foil == NULL) {   
        foil = new airFoil();
        do {
            for(unsigned int i = 1; i < foil->size(); i++) {
                foil->at(i) = rnd.uniform(0., (i+1)*10000.);
            }
            foil->at(0) = rnd.uniform(0., 99.);
            foil->at(1) = rnd.uniform(0., 99.);
            foil->at(9) = 100;  // Trailing edge thickness = 0
          
            foil->update();
        } while (!foil->check());
    }
    else {
        foil = new airFoil(Foil);
    }
    return foil;
}

double airFoil::z_up(double x) const {
    double result = 0;
    for(unsigned int i = 1; i <= 6; i++) {
        result += a[i-1]*pow(x, i - 1.0/2);
    }
    return result;
}
    
double airFoil::z_lo(double x) const {
    double result = 0;
    for(unsigned int i = 1; i <= 6; i++) {
        result += b[i-1]*pow(x, i - 1.0/2);
    }
    return result;
}
    
void airFoil::update() 
{
    unsigned int _rle_up = (unsigned int)at(0); 
    at(0) = _rle_up % 100;    
    unsigned int _rle_lo = (unsigned int)at(1); 
    at(1) = _rle_lo % 100;  
    unsigned int _X_up = (unsigned int)at(2); 
    at(2) = _X_up % 100;    
    unsigned int _Z_up = (unsigned int)at(3); 
    at(3) = _Z_up % 310;    
    unsigned int _Z_XXup = (unsigned int)at(4); 
    at(4) = _Z_XXup % 2000;    
    unsigned int _X_lo = (unsigned int)at(5); 
    at(5) = _X_lo % 100;    
    unsigned int _Z_lo = (unsigned int)at(6); 
    at(6) = _Z_lo % 310;    
    unsigned int _Z_XXlo = (unsigned int)at(7); 
    at(7) = _Z_XXlo % 2000;   
    unsigned int _Z_TE = (unsigned int)at(8);
    at(8) = _Z_TE % 200;    
    unsigned int _deltaZ_TE = (unsigned int)at(9);
    at(9) = _deltaZ_TE % 200;        
    unsigned int _alpha_TE = (unsigned int)at(10);
    at(10) = _alpha_TE % 10000;
    unsigned int _beta_TE = (unsigned int)at(11);
    at(11) = _beta_TE % 8000;   
    
    double alpha_TE_ = alpha_TE * rad;
    double beta_TE_ = beta_TE * rad;    
    a[0] = sqrt(2.0)*sqrt(rle_up);
    a[1] = (1.0/pow(X_up-1.0, 2.0)*(Z_up*3.5E1+pow(X_up, 9.0/2.0)*tan(alpha_TE_-beta_TE_*(1.0/2.0))*8.0-pow(X_up, 1.1E1/2.0)*tan(alpha_TE_-beta_TE_*(1.0/2.0))*8.0-X_up*Z_up*1.1E2-pow(X_up, 9.0/2.0)*Z_TE*4.4E1+pow(X_up, 1.1E1/2.0)*Z_TE*2.0E1+(X_up*X_up)*Z_XXup*4.0-(X_up*X_up*X_up)*Z_XXup*8.0+(X_up*X_up*X_up*X_up)*Z_XXup*4.0+(X_up*X_up)*Z_up*9.9E1-pow(X_up, 9.0/2.0)*deltaZ_TE*2.2E1+pow(X_up, 1.1E1/2.0)*deltaZ_TE*1.0E1-sqrt(2.0)*sqrt(X_up)*sqrt(rle_up)*2.4E1+sqrt(2.0)*pow(X_up, 3.0/2.0)*sqrt(rle_up)*8.0E1-sqrt(2.0)*pow(X_up, 5.0/2.0)*sqrt(rle_up)*8.0E1+sqrt(2.0)*pow(X_up, 9.0/2.0)*sqrt(rle_up)*4.0E1-sqrt(2.0)*pow(X_up, 1.1E1/2.0)*sqrt(rle_up)*1.6E1)*(1.0/8.0))/(pow(X_up, 3.0/2.0)-pow(X_up, 5.0/2.0)*2.0+pow(X_up, 7.0/2.0));
    a[2] = (1.0/sqrt(X_up)*(Z_up*2.1E1+pow(X_up, 9.0/2.0)*tan(alpha_TE_-beta_TE_*(1.0/2.0))*1.2E1-pow(X_up, 1.1E1/2.0)*tan(alpha_TE_-beta_TE_*(1.0/2.0))*8.0-pow(X_up, 1.3E1/2.0)*tan(alpha_TE_-beta_TE_*(1.0/2.0))*4.0-X_up*Z_up*3.9E1-pow(X_up, 9.0/2.0)*Z_TE*6.6E1+pow(X_up, 1.1E1/2.0)*Z_TE*1.2E1+pow(X_up, 1.3E1/2.0)*Z_TE*6.0+(X_up*X_up)*Z_XXup*4.0-(X_up*X_up*X_up)*Z_XXup*4.0-(X_up*X_up*X_up*X_up)*Z_XXup*4.0+(X_up*X_up*X_up*X_up*X_up)*Z_XXup*4.0-(X_up*X_up)*Z_up*3.3E1+(X_up*X_up*X_up)*Z_up*9.9E1-pow(X_up, 9.0/2.0)*deltaZ_TE*3.3E1+pow(X_up, 1.1E1/2.0)*deltaZ_TE*6.0+pow(X_up, 1.3E1/2.0)*deltaZ_TE*3.0-sqrt(2.0)*sqrt(X_up)*sqrt(rle_up)*1.2E1+sqrt(2.0)*pow(X_up, 3.0/2.0)*sqrt(rle_up)*2.4E1+sqrt(2.0)*pow(X_up, 5.0/2.0)*sqrt(rle_up)*2.0E1-sqrt(2.0)*pow(X_up, 7.0/2.0)*sqrt(rle_up)*8.0E1+sqrt(2.0)*pow(X_up, 9.0/2.0)*sqrt(rle_up)*6.0E1-sqrt(2.0)*pow(X_up, 1.1E1/2.0)*sqrt(rle_up)*8.0-sqrt(2.0)*pow(X_up, 1.3E1/2.0)*sqrt(rle_up)*4.0)*(1.0/4.0))/((sqrt(X_up)-pow(X_up, 3.0/2.0))*(X_up-1.0)*(pow(X_up, 3.0/2.0)-pow(X_up, 5.0/2.0)*2.0+pow(X_up, 7.0/2.0)));
    a[3] = (1.0/pow(sqrt(X_up)-pow(X_up, 3.0/2.0), 2.0)*(Z_up*1.5E1+pow(X_up, 9.0/2.0)*tan(alpha_TE_-beta_TE_*(1.0/2.0))*2.4E1-pow(X_up, 1.3E1/2.0)*tan(alpha_TE_-beta_TE_*(1.0/2.0))*2.4E1+X_up*Z_up*3.0E1-pow(X_up, 9.0/2.0)*Z_TE*1.32E2-pow(X_up, 1.1E1/2.0)*Z_TE*4.8E1+pow(X_up, 1.3E1/2.0)*Z_TE*3.6E1+(X_up*X_up)*Z_XXup*4.0+(X_up*X_up*X_up)*Z_XXup*8.0-(X_up*X_up*X_up*X_up)*Z_XXup*2.4E1+(X_up*X_up*X_up*X_up*X_up)*Z_XXup*8.0+(X_up*X_up*X_up*X_up*X_up*X_up)*Z_XXup*4.0-(X_up*X_up)*Z_up*1.98E2+(X_up*X_up*X_up)*Z_up*1.98E2+(X_up*X_up*X_up*X_up)*Z_up*9.9E1-pow(X_up, 9.0/2.0)*deltaZ_TE*6.6E1-pow(X_up, 1.1E1/2.0)*deltaZ_TE*2.4E1+pow(X_up, 1.3E1/2.0)*deltaZ_TE*1.8E1-sqrt(2.0)*sqrt(X_up)*sqrt(rle_up)*8.0-sqrt(2.0)*pow(X_up, 3.0/2.0)*sqrt(rle_up)*1.6E1+sqrt(2.0)*pow(X_up, 5.0/2.0)*sqrt(rle_up)*1.2E2-sqrt(2.0)*pow(X_up, 7.0/2.0)*sqrt(rle_up)*1.6E2+sqrt(2.0)*pow(X_up, 9.0/2.0)*sqrt(rle_up)*4.0E1+sqrt(2.0)*pow(X_up, 1.1E1/2.0)*sqrt(rle_up)*4.8E1-sqrt(2.0)*pow(X_up, 1.3E1/2.0)*sqrt(rle_up)*2.4E1)*(1.0/8.0))/(X_up*(pow(X_up, 3.0/2.0)-pow(X_up, 5.0/2.0)*2.0+pow(X_up, 7.0/2.0)));
    a[4] = (1.0/pow(X_up, 3.0/2.0)*(Z_up*-1.5E1-pow(X_up, 7.0/2.0)*tan(alpha_TE_-beta_TE_*(1.0/2.0))*4.0-pow(X_up, 9.0/2.0)*tan(alpha_TE_-beta_TE_*(1.0/2.0))*8.0+pow(X_up, 1.1E1/2.0)*tan(alpha_TE_-beta_TE_*(1.0/2.0))*1.2E1+X_up*Z_up*3.3E1+pow(X_up, 7.0/2.0)*Z_TE*2.2E1+pow(X_up, 9.0/2.0)*Z_TE*4.4E1-pow(X_up, 1.1E1/2.0)*Z_TE*1.8E1-(X_up*X_up)*Z_XXup*4.0+(X_up*X_up*X_up)*Z_XXup*4.0+(X_up*X_up*X_up*X_up)*Z_XXup*4.0-(X_up*X_up*X_up*X_up*X_up)*Z_XXup*4.0+(X_up*X_up)*Z_up*1.1E1-(X_up*X_up*X_up)*Z_up*7.7E1+pow(X_up, 7.0/2.0)*deltaZ_TE*1.1E1+pow(X_up, 9.0/2.0)*deltaZ_TE*2.2E1-pow(X_up, 1.1E1/2.0)*deltaZ_TE*9.0+sqrt(2.0)*sqrt(X_up)*sqrt(rle_up)*8.0-sqrt(2.0)*pow(X_up, 3.0/2.0)*sqrt(rle_up)*2.0E1+sqrt(2.0)*pow(X_up, 7.0/2.0)*sqrt(rle_up)*4.0E1-sqrt(2.0)*pow(X_up, 9.0/2.0)*sqrt(rle_up)*4.0E1+sqrt(2.0)*pow(X_up, 1.1E1/2.0)*sqrt(rle_up)*1.2E1)*(-1.0/4.0))/((sqrt(X_up)-pow(X_up, 3.0/2.0))*(X_up-1.0)*(pow(X_up, 3.0/2.0)-pow(X_up, 5.0/2.0)*2.0+pow(X_up, 7.0/2.0)));
    a[5] = (Z_up*(1.5E1/8.0)+pow(X_up, 7.0/2.0)*tan(alpha_TE_-beta_TE_*(1.0/2.0))-pow(X_up, 9.0/2.0)*tan(alpha_TE_-beta_TE_*(1.0/2.0))-X_up*Z_up*(2.7E1/4.0)-pow(X_up, 7.0/2.0)*Z_TE*(9.0/2.0)+pow(X_up, 9.0/2.0)*Z_TE*(3.0/2.0)+(X_up*X_up)*Z_XXup*(1.0/2.0)-(X_up*X_up*X_up)*Z_XXup+(X_up*X_up*X_up*X_up)*Z_XXup*(1.0/2.0)+(X_up*X_up)*Z_up*(6.3E1/8.0)-pow(X_up, 7.0/2.0)*deltaZ_TE*(9.0/4.0)+pow(X_up, 9.0/2.0)*deltaZ_TE*(3.0/4.0)-sqrt(2.0)*sqrt(X_up)*sqrt(rle_up)+sqrt(2.0)*pow(X_up, 3.0/2.0)*sqrt(rle_up)*4.0-sqrt(2.0)*pow(X_up, 5.0/2.0)*sqrt(rle_up)*6.0+sqrt(2.0)*pow(X_up, 7.0/2.0)*sqrt(rle_up)*4.0-sqrt(2.0)*pow(X_up, 9.0/2.0)*sqrt(rle_up))/(pow(X_up, 7.0/2.0)-pow(X_up, 9.0/2.0)*4.0+pow(X_up, 1.1E1/2.0)*6.0-pow(X_up, 1.3E1/2.0)*4.0+pow(X_up, 1.5E1/2.0));

    b[0] = -sqrt(2.0)*sqrt(rle_lo);
    b[1] = (1.0/pow(X_lo-1.0, 2.0)*(Z_lo*3.5E1+pow(X_lo, 9.0/2.0)*tan(alpha_TE_+beta_TE_*(1.0/2.0))*8.0-pow(X_lo, 1.1E1/2.0)*tan(alpha_TE_+beta_TE_*(1.0/2.0))*8.0-X_lo*Z_lo*1.1E2-pow(X_lo, 9.0/2.0)*Z_TE*4.4E1+pow(X_lo, 1.1E1/2.0)*Z_TE*2.0E1+(X_lo*X_lo)*Z_XXlo*4.0-(X_lo*X_lo*X_lo)*Z_XXlo*8.0+(X_lo*X_lo*X_lo*X_lo)*Z_XXlo*4.0+(X_lo*X_lo)*Z_lo*9.9E1+pow(X_lo, 9.0/2.0)*deltaZ_TE*2.2E1-pow(X_lo, 1.1E1/2.0)*deltaZ_TE*1.0E1+sqrt(2.0)*sqrt(X_lo)*sqrt(rle_lo)*2.4E1-sqrt(2.0)*pow(X_lo, 3.0/2.0)*sqrt(rle_lo)*8.0E1+sqrt(2.0)*pow(X_lo, 5.0/2.0)*sqrt(rle_lo)*8.0E1-sqrt(2.0)*pow(X_lo, 9.0/2.0)*sqrt(rle_lo)*4.0E1+sqrt(2.0)*pow(X_lo, 1.1E1/2.0)*sqrt(rle_lo)*1.6E1)*(1.0/8.0))/(pow(X_lo, 3.0/2.0)-pow(X_lo, 5.0/2.0)*2.0+pow(X_lo, 7.0/2.0));
    b[2] = (1.0/sqrt(X_lo)*(Z_lo*2.1E1+pow(X_lo, 9.0/2.0)*tan(alpha_TE_+beta_TE_*(1.0/2.0))*1.2E1-pow(X_lo, 1.1E1/2.0)*tan(alpha_TE_+beta_TE_*(1.0/2.0))*8.0-pow(X_lo, 1.3E1/2.0)*tan(alpha_TE_+beta_TE_*(1.0/2.0))*4.0-X_lo*Z_lo*3.9E1-pow(X_lo, 9.0/2.0)*Z_TE*6.6E1+pow(X_lo, 1.1E1/2.0)*Z_TE*1.2E1+pow(X_lo, 1.3E1/2.0)*Z_TE*6.0+(X_lo*X_lo)*Z_XXlo*4.0-(X_lo*X_lo*X_lo)*Z_XXlo*4.0-(X_lo*X_lo*X_lo*X_lo)*Z_XXlo*4.0+(X_lo*X_lo*X_lo*X_lo*X_lo)*Z_XXlo*4.0-(X_lo*X_lo)*Z_lo*3.3E1+(X_lo*X_lo*X_lo)*Z_lo*9.9E1+pow(X_lo, 9.0/2.0)*deltaZ_TE*3.3E1-pow(X_lo, 1.1E1/2.0)*deltaZ_TE*6.0-pow(X_lo, 1.3E1/2.0)*deltaZ_TE*3.0+sqrt(2.0)*sqrt(X_lo)*sqrt(rle_lo)*1.2E1-sqrt(2.0)*pow(X_lo, 3.0/2.0)*sqrt(rle_lo)*2.4E1-sqrt(2.0)*pow(X_lo, 5.0/2.0)*sqrt(rle_lo)*2.0E1+sqrt(2.0)*pow(X_lo, 7.0/2.0)*sqrt(rle_lo)*8.0E1-sqrt(2.0)*pow(X_lo, 9.0/2.0)*sqrt(rle_lo)*6.0E1+sqrt(2.0)*pow(X_lo, 1.1E1/2.0)*sqrt(rle_lo)*8.0+sqrt(2.0)*pow(X_lo, 1.3E1/2.0)*sqrt(rle_lo)*4.0)*(1.0/4.0))/((sqrt(X_lo)-pow(X_lo, 3.0/2.0))*(X_lo-1.0)*(pow(X_lo, 3.0/2.0)-pow(X_lo, 5.0/2.0)*2.0+pow(X_lo, 7.0/2.0)));
    b[3] = (1.0/pow(sqrt(X_lo)-pow(X_lo, 3.0/2.0), 2.0)*(Z_lo*1.5E1+pow(X_lo, 9.0/2.0)*tan(alpha_TE_+beta_TE_*(1.0/2.0))*2.4E1-pow(X_lo, 1.3E1/2.0)*tan(alpha_TE_+beta_TE_*(1.0/2.0))*2.4E1+X_lo*Z_lo*3.0E1-pow(X_lo, 9.0/2.0)*Z_TE*1.32E2-pow(X_lo, 1.1E1/2.0)*Z_TE*4.8E1+pow(X_lo, 1.3E1/2.0)*Z_TE*3.6E1+(X_lo*X_lo)*Z_XXlo*4.0+(X_lo*X_lo*X_lo)*Z_XXlo*8.0-(X_lo*X_lo*X_lo*X_lo)*Z_XXlo*2.4E1+(X_lo*X_lo*X_lo*X_lo*X_lo)*Z_XXlo*8.0+(X_lo*X_lo*X_lo*X_lo*X_lo*X_lo)*Z_XXlo*4.0-(X_lo*X_lo)*Z_lo*1.98E2+(X_lo*X_lo*X_lo)*Z_lo*1.98E2+(X_lo*X_lo*X_lo*X_lo)*Z_lo*9.9E1+pow(X_lo, 9.0/2.0)*deltaZ_TE*6.6E1+pow(X_lo, 1.1E1/2.0)*deltaZ_TE*2.4E1-pow(X_lo, 1.3E1/2.0)*deltaZ_TE*1.8E1+sqrt(2.0)*sqrt(X_lo)*sqrt(rle_lo)*8.0+sqrt(2.0)*pow(X_lo, 3.0/2.0)*sqrt(rle_lo)*1.6E1-sqrt(2.0)*pow(X_lo, 5.0/2.0)*sqrt(rle_lo)*1.2E2+sqrt(2.0)*pow(X_lo, 7.0/2.0)*sqrt(rle_lo)*1.6E2-sqrt(2.0)*pow(X_lo, 9.0/2.0)*sqrt(rle_lo)*4.0E1-sqrt(2.0)*pow(X_lo, 1.1E1/2.0)*sqrt(rle_lo)*4.8E1+sqrt(2.0)*pow(X_lo, 1.3E1/2.0)*sqrt(rle_lo)*2.4E1)*(1.0/8.0))/(X_lo*(pow(X_lo, 3.0/2.0)-pow(X_lo, 5.0/2.0)*2.0+pow(X_lo, 7.0/2.0)));
    b[4] = (1.0/pow(X_lo, 3.0/2.0)*(Z_lo*1.5E1+pow(X_lo, 7.0/2.0)*tan(alpha_TE_+beta_TE_*(1.0/2.0))*4.0+pow(X_lo, 9.0/2.0)*tan(alpha_TE_+beta_TE_*(1.0/2.0))*8.0-pow(X_lo, 1.1E1/2.0)*tan(alpha_TE_+beta_TE_*(1.0/2.0))*1.2E1-X_lo*Z_lo*3.3E1-pow(X_lo, 7.0/2.0)*Z_TE*2.2E1-pow(X_lo, 9.0/2.0)*Z_TE*4.4E1+pow(X_lo, 1.1E1/2.0)*Z_TE*1.8E1+(X_lo*X_lo)*Z_XXlo*4.0-(X_lo*X_lo*X_lo)*Z_XXlo*4.0-(X_lo*X_lo*X_lo*X_lo)*Z_XXlo*4.0+(X_lo*X_lo*X_lo*X_lo*X_lo)*Z_XXlo*4.0-(X_lo*X_lo)*Z_lo*1.1E1+(X_lo*X_lo*X_lo)*Z_lo*7.7E1+pow(X_lo, 7.0/2.0)*deltaZ_TE*1.1E1+pow(X_lo, 9.0/2.0)*deltaZ_TE*2.2E1-pow(X_lo, 1.1E1/2.0)*deltaZ_TE*9.0+sqrt(2.0)*sqrt(X_lo)*sqrt(rle_lo)*8.0-sqrt(2.0)*pow(X_lo, 3.0/2.0)*sqrt(rle_lo)*2.0E1+sqrt(2.0)*pow(X_lo, 7.0/2.0)*sqrt(rle_lo)*4.0E1-sqrt(2.0)*pow(X_lo, 9.0/2.0)*sqrt(rle_lo)*4.0E1+sqrt(2.0)*pow(X_lo, 1.1E1/2.0)*sqrt(rle_lo)*1.2E1)*(1.0/4.0))/((sqrt(X_lo)-pow(X_lo, 3.0/2.0))*(X_lo-1.0)*(pow(X_lo, 3.0/2.0)-pow(X_lo, 5.0/2.0)*2.0+pow(X_lo, 7.0/2.0)));
    b[5] = (Z_lo*(1.5E1/8.0)+pow(X_lo, 7.0/2.0)*tan(alpha_TE_+beta_TE_*(1.0/2.0))-pow(X_lo, 9.0/2.0)*tan(alpha_TE_+beta_TE_*(1.0/2.0))-X_lo*Z_lo*(2.7E1/4.0)-pow(X_lo, 7.0/2.0)*Z_TE*(9.0/2.0)+pow(X_lo, 9.0/2.0)*Z_TE*(3.0/2.0)+(X_lo*X_lo)*Z_XXlo*(1.0/2.0)-(X_lo*X_lo*X_lo)*Z_XXlo+(X_lo*X_lo*X_lo*X_lo)*Z_XXlo*(1.0/2.0)+(X_lo*X_lo)*Z_lo*(6.3E1/8.0)+pow(X_lo, 7.0/2.0)*deltaZ_TE*(9.0/4.0)-pow(X_lo, 9.0/2.0)*deltaZ_TE*(3.0/4.0)+sqrt(2.0)*sqrt(X_lo)*sqrt(rle_lo)-sqrt(2.0)*pow(X_lo, 3.0/2.0)*sqrt(rle_lo)*4.0+sqrt(2.0)*pow(X_lo, 5.0/2.0)*sqrt(rle_lo)*6.0-sqrt(2.0)*pow(X_lo, 7.0/2.0)*sqrt(rle_lo)*4.0+sqrt(2.0)*pow(X_lo, 9.0/2.0)*sqrt(rle_lo))/(pow(X_lo, 7.0/2.0)-pow(X_lo, 9.0/2.0)*4.0+pow(X_lo, 1.1E1/2.0)*6.0-pow(X_lo, 1.3E1/2.0)*4.0+pow(X_lo, 1.5E1/2.0));

}

airFoil* airFoil::clone() const {
    return new airFoil (*this);
}

double airFoil::norm(unsigned int index) const {
    if (index == 0)
        return at(0)/100;    
    else if (index == 1)
        return at(1)/100;  
    else if (index == 2)
        return at(2)/100;  
    else if (index == 3)
        return at(3)/ 310;    
    else if (index == 4)
        return at(4)/ 2000;    
    else if (index == 5)
        return at(5)/ 100;    
    else if (index == 6)
        return at(6)/ 310;    
    else if (index == 7)
        return at(7)/ 2000;   
    else if (index == 8)
        return at(8)/ 200;    
    else if (index == 9)
        return at(9)/ 200;        
    else if (index == 10)
        return at(10)/ 10000;
    else if (index == 11)
        return at(11)/ 8000;    
    return NAN;   
}
    
void airFoil::denorm(unsigned int index, const double &value) {
    if (index == 0)
        at(0) = value * 100; 
    else if (index == 1)
        at(1) = value * 100;  
    else if (index == 2)
        at(2) = value * 100;  
    else if (index == 3)
        at(3) = value * 310;    
    else if (index == 4)
        at(4) = value * 2000;    
    else if (index == 5)
        at(5) = value * 100;    
    else if (index == 6)
        at(6) = value * 310;    
    else if (index == 7)
        at(7) = value * 2000;   
    else if (index == 8)
        at(8) = value * 200;    
    else if (index == 9)
        at(9) = value * 200;        
    else if (index == 10)
        at(10) = value * 10000;
    else if (index == 11)
        at(11) = value * 8000;   
    update();
}

airFoil:: ~airFoil() {
    this->clear();
}

airFoil::airFoil(const char* foilname) {
    resize(12, NAN);
    at(0) =  a2i(foilname[0])*10 + a2i(foilname[1]);
    at(1) =  a2i(foilname[2])*10 + a2i(foilname[3]);
    at(2) =  a2i(foilname[4])*10 + a2i(foilname[5]);
    at(3) =  a2i(foilname[6])*100 + a2i(foilname[7])*10 + a2i(foilname[8]);
    at(4) =  a2i(foilname[9])*1000 + a2i(foilname[10])*100 
            + a2i(foilname[11])*10 + a2i(foilname[12]);
    at(5) =  a2i(foilname[13])*10 + a2i(foilname[14]);
    at(6) =  a2i(foilname[15])*100 + a2i(foilname[16])*10 + a2i(foilname[17]);
    at(7) =  a2i(foilname[18])*1000 + a2i(foilname[19])*100 
            + a2i(foilname[20])*10 + a2i(foilname[21]);
    at(8) =  a2i(foilname[22])*100 + a2i(foilname[23])*10 + a2i(foilname[24]);
    at(9) =  a2i(foilname[25])*100 + a2i(foilname[26])*10 + a2i(foilname[27]);
    at(10) = a2i(foilname[28])*1000 + a2i(foilname[29])*100 
            + a2i(foilname[30])*10 + a2i(foilname[31]);
    at(11) = a2i(foilname[32])*1000 + a2i(foilname[33])*100 
            + a2i(foilname[34])*10 + a2i(foilname[35]);  
    update();
}
