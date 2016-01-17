/* 
 * File:   airControl.cpp
 * Author: Tieu Minh
 * 
 * Created on April 27, 2013, 11:26 AM
 */

#include "airControl.h"

airControl::airControl() {
    startTime = 0;
    writeTime = NAN;
    endTime = NAN;
    timeStep = NAN;     
    n_p = 1;
}

airControl::airControl(const airControl& orig) {      
    writeTime = orig.writeTime;
    endTime = orig.endTime;
    timeStep = orig.timeStep;      
    startTime = orig.startTime;
    n_p = orig.n_p;
}

airControl::~airControl() {
}

airControl::airControl(const char* filename) {    
    
    edaINIReader reader(filename);        
    
    timeStep = reader.GetDouble("Control","Time Step", NAN);
    
    writeTime = reader.GetDouble("Control","Writing Time", NAN);
    
    endTime = reader.GetDouble("Control","End Time", NAN); 
    
    startTime = reader.GetDouble("Control","Starting Time", NAN); 
    
    n_p = reader.GetInteger("Control","Num Processors", 1);

}

void airControl::printOn(ostream& os) const {        
    os << "[Control]" << endl;
    os << "Start Time: " << startTime << endl;
    os << "Time Step: " << timeStep << endl;
    os << "Writing Time: " << writeTime << endl;
    os << "End Time: " << endTime << endl;
    os << "Num Processors: " << n_p << endl;
    os << endl;
}

void airControl::Serialize( edaBuffer &buf, bool pack ) {
    if(pack) {
        buf.Pack(&n_p, 1);        
        buf.Pack(&writeTime, 1);
        buf.Pack(&endTime, 1);
        buf.Pack(&timeStep, 1);
        buf.Pack(&startTime, 1);
    }
    else {
        buf.UnPack(&n_p, 1);         
        buf.UnPack(&writeTime, 1);
        buf.UnPack(&endTime, 1);
        buf.UnPack(&timeStep, 1);
        buf.UnPack(&startTime, 1); 
    }
}

void airControl::createData() const {    
    moveData(createControlDictFile(),"system");
}

void airControl::updateData() const {    
    moveData(updateControlDictFile(),"system");
    moveData(createDecomposeParDictFile(),"system");
}

airControl* airControl::clone() const {    
    return new airControl(*this);
}

const char* airControl::createDecomposeParDictFile() const {
    FILE *file = fopen("decomposeParDict", "w");   
    fprints(file, "decomposeParDict");
    fprintf(file, "numberOfSubdomains       %d;          \n",n_p);
    fprintf(file, "method                   scotch;      \n"); 
    fprintf(file, "scotchCoeffs {}                       \n"); 
    fprintf(file, "distributed              no;          \n"); 
    fprintf(file, "roots                    ( );         \n"); 
    fprinte(file);
    return "decomposeParDict";
}

const char* airControl::createControlDictFile() const {
    FILE *file = fopen("controlDict", "w"); 
    fprints(file, "controlDict");
    fprintf(file, "application       sonicFoam ;  \n");
    fprintf(file, "startFrom         latestTime;  \n");
    fprintf(file, "startTime         %e;          \n", startTime);
    fprintf(file, "stopAt            endTime;     \n");
    fprintf(file, "endTime           %e;          \n", 0.0001);
    fprintf(file, "deltaT            %e;          \n", timeStep);
    fprintf(file, "writeControl      runTime;     \n");
    fprintf(file, "writeInterval     %e;          \n", 0.0001);
    fprintf(file, "purgeWrite        0;           \n");
    fprintf(file, "writeFormat       ascii;       \n");
    fprintf(file, "writePrecision    6;           \n");
    fprintf(file, "writeCompression  off;         \n");
    fprintf(file, "timeFormat        general;     \n");
    fprintf(file, "timePrecision     6;           \n");
    fprintf(file, "runTimeModifiable true;        \n");
    fprintf(file, "functions         { #include \"forceCoeffs\" } \n");
    fprinte(file);
    return "controlDict";    
}

const char* airControl::updateControlDictFile() const {
    FILE *file = fopen("controlDict", "w"); 
    fprints(file, "controlDict");
    fprintf(file, "application       sonicFoam ;  \n");
    fprintf(file, "startFrom         latestTime;  \n");
    fprintf(file, "startTime         %e;          \n", startTime);
    fprintf(file, "stopAt            endTime;     \n");
    fprintf(file, "endTime           %e;          \n", endTime);
    fprintf(file, "deltaT            %e;          \n", timeStep);
    fprintf(file, "writeControl      runTime;     \n");
    fprintf(file, "writeInterval     %e;          \n", writeTime);
    fprintf(file, "purgeWrite        0;           \n");
    fprintf(file, "writeFormat       ascii;       \n");
    fprintf(file, "writePrecision    6;           \n");
    fprintf(file, "writeCompression  off;         \n");
    fprintf(file, "timeFormat        general;     \n");
    fprintf(file, "timePrecision     6;           \n");
    fprintf(file, "runTimeModifiable true;        \n");
    fprintf(file, "functions         { #include \"forceCoeffs\" } \n");
    fprinte(file);
    return "controlDict";    
}

ostream& operator<< (ostream &os, const airControl &control) {
    control.printOn(os);
    return os;
}

unsigned int airControl::getNodes() const {
    return n_p;
}

double airControl::getWriteTime() const {
    return writeTime;
}

double airControl::getEndTime() const {
    return endTime;
}

double airControl::getTimeStep() const {
    return timeStep;
}

double airControl::getStartTime() const {
    return startTime;
}

