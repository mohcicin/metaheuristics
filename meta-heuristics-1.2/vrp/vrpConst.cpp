/* 
 * File:   vrpConst.cpp
 * Author: Administrator
 * 
 * Created on June 8, 2012, 9:01 PM
 */

#include "vrpConst.h"

vrpConst::vrpConst(TYPE type) {    
    if(type == Default) {
        load("vrptest/config.txt");
    }
    else if(type == Random) {
        THETA_1 = rnd.uniform();
        THETA_2 = rnd.uniform();
        THETA_3 = rnd.uniform();
        BETA_1 =  rnd.uniform();
        BETA_2 =  rnd.uniform();
        BETA_3 =  rnd.uniform();
        ALPHA_1 = rnd.uniform();
        ALPHA_2 = rnd.uniform();
        LAMDA =   rnd.uniform();
        MU =      rnd.uniform();
        HAS_IMPROVE_ROUTE = true;
        HAS_IMPROVE_SUB = true;
        HAS_IMPROVE_LANDFILL = true;   
    } 
}
vrpConst::vrpConst(const char* filename) {
    load(filename);
}
vrpConst::vrpConst(const float* para, const unsigned int num) {
    if(num == 10) {
        THETA_1 = para[0];
        THETA_2 = para[1];
        THETA_3 = para[2];
        BETA_1 =  para[3];
        BETA_2 =  para[4];
        BETA_3 =  para[5];
        ALPHA_1 = para[6];
        ALPHA_2 = para[7];
        LAMDA =   para[8];
        MU =      para[9];
    }
}
vrpConst::vrpConst(const vrpConst& orig) {
    BETA_1 = orig.BETA_1;
    BETA_2 = orig.BETA_2;
    BETA_3 = orig.BETA_3;
    ALPHA_1 = orig.ALPHA_1;
    ALPHA_2 = orig.ALPHA_2;
    LAMDA = orig.LAMDA ;
    THETA_1 = orig.THETA_1;
    THETA_2 = orig.THETA_2;
    THETA_3 = orig.THETA_3;
    MU = orig.MU;
    HAS_IMPROVE_ROUTE = orig.HAS_IMPROVE_ROUTE;
    HAS_IMPROVE_SUB = orig.HAS_IMPROVE_SUB;
    HAS_IMPROVE_LANDFILL = orig.HAS_IMPROVE_LANDFILL;
}

vrpConst::~vrpConst() {}

vrpConst *vrpConst::clone() const {
    return new vrpConst(*this);
}

void vrpConst::load(const char *filename) {
	ifstream f(filename);
	char text[128];
	char value[128];
	if(f) {
		while(f >> text >> value) {
			if(strcmp(text,"COST_DIST_RATIO") == 0)			
				sscanf(value,"%lf",&THETA_1);			
			else if(strcmp(text,"COST_MOVE_TIME_RATIO") == 0)			
				sscanf(value,"%lf",&THETA_2 );			
			else if(strcmp(text,"COST_WAIT_TIME_RATIO") == 0)			
				sscanf(value,"%lf",&THETA_3);			
			else if(strcmp(text,"C1_ALPHA1") == 0)			
				sscanf(value,"%lf",&ALPHA_1 );			
			else if(strcmp(text,"C1_ALPHA2") == 0)			
				sscanf(value,"%lf",&ALPHA_2 );			
			else if(strcmp(text,"C2_ALPHA") == 0)			
				sscanf(value,"%lf",&LAMDA );
		        else if(strcmp(text,"C3_ALPHA") == 0)			
				sscanf(value,"%lf",&MU );
			else if(strcmp(text,"FIRST_STOP_BETA1") == 0)			
				sscanf(value,"%lf",&BETA_1 );
			else if(strcmp(text,"FIRST_STOP_BETA2") == 0)			
				sscanf(value,"%lf",&BETA_2 );
			else if(strcmp(text,"FIRST_STOP_BETA3") == 0)			
				sscanf(value,"%lf",&BETA_3 );			
			else if(strcmp(text,"HAS_IMPROVE_ROUTE") == 0)			
				sscanf(value,"%d",&HAS_IMPROVE_ROUTE );			
			else if(strcmp(text,"HAS_IMPROVE_SUB") == 0)			
				sscanf(value,"%d",&HAS_IMPROVE_SUB );			
			else if(strcmp(text,"HAS_IMPROVE_LANDFILL") == 0)			
				sscanf(value,"%d",&HAS_IMPROVE_LANDFILL );	
		}
		f.close();	
	}    
    else {
        //load default
        THETA_1 = 0.4;
        THETA_2 = 0.4;
        THETA_3 = 0.2;
        BETA_1 = -0.7;
        BETA_2 =  0.2;
        BETA_3 =  0.1;
        ALPHA_1 = 0.5;
        ALPHA_2 = 0.5;
        LAMDA = 0.01; 
        MU = 1.0;
    }
}


vrpConst& vrpConst::operator = (const vrpConst &_const) {
    BETA_1 = _const.BETA_1;
    BETA_2 = _const.BETA_2;
    BETA_3 = _const.BETA_3;
    ALPHA_1 = _const.ALPHA_1;
    ALPHA_2 = _const.ALPHA_2;
    LAMDA = _const.LAMDA ;
    THETA_1 = _const.THETA_1;
    THETA_2 = _const.THETA_2;
    THETA_3 = _const.THETA_3;
    MU = _const.MU;
    HAS_IMPROVE_ROUTE = _const.HAS_IMPROVE_ROUTE;
    HAS_IMPROVE_SUB = _const.HAS_IMPROVE_SUB;
    HAS_IMPROVE_LANDFILL = _const.HAS_IMPROVE_LANDFILL;
    return *this;
}

void vrpConst::Serialize(edaBuffer &buf, bool pack) {
    edaSerialize::Serialize(buf,pack);
    if ( pack ){ 
        buf.Pack( &BETA_1, 1 );
        buf.Pack( &BETA_2, 1 );
        buf.Pack( &BETA_3, 1 );
        buf.Pack( &ALPHA_1, 1 );
        buf.Pack( &ALPHA_2, 1 );
        buf.Pack( &LAMDA, 1 );
        buf.Pack( &THETA_1, 1 );
        buf.Pack( &THETA_2, 1 );
        buf.Pack( &THETA_2, 1 );
        buf.Pack( &MU, 1 );
        buf.Pack( &HAS_IMPROVE_ROUTE, 1 );
        buf.Pack( &HAS_IMPROVE_SUB, 1 );
        buf.Pack( &HAS_IMPROVE_LANDFILL, 1 );
    } 
    else {
        buf.UnPack( &BETA_1, 1 );
        buf.UnPack( &BETA_2, 1 );
        buf.UnPack( &BETA_3, 1 );
        buf.UnPack( &ALPHA_1, 1 );
        buf.UnPack( &ALPHA_2, 1 );
        buf.UnPack( &LAMDA, 1 );
        buf.UnPack( &THETA_1, 1 );
        buf.UnPack( &THETA_2, 1 );
        buf.UnPack( &THETA_2, 1 );
        buf.UnPack( &MU, 1 );
        buf.UnPack( &HAS_IMPROVE_ROUTE, 1 );
        buf.UnPack( &HAS_IMPROVE_SUB, 1 );
        buf.UnPack( &HAS_IMPROVE_LANDFILL, 1 );
    }
}
