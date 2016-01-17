/* 
 * File:   airProblem.cpp
 * Author: Tieu Minh
 * 
 * Created on April 30, 2013, 9:36 AM
 */

#include "airProblem.h"
#include "airMesh.h"
#include "airSolver.h"
#include <dirent.h>
#include <ctime>

airProblem::airProblem()
{
    mesh = NULL;
    solver = NULL;
    control = NULL;    
}

airProblem::airProblem(const airProblem& orig)
{
    mesh = orig.mesh->clone();
    solver = orig.solver->clone();
    control = orig.control->clone();
}

airProblem::airProblem(const char* filename) 
{   
    cout << ">> Loading [" << filename << "]" << endl;    
    control = new airControl(filename);        
    mesh = new airMesh(filename);      
    solver = new airSolver(filename);

}

airProblem::~airProblem() 
{
    earse();
}

void airProblem::Serialize(edaBuffer &buf, bool pack) {
    if(pack) {
        mesh->doSerialize(buf, pack);
        solver->doSerialize(buf, pack);
        control->doSerialize(buf, pack);
    }
    else {
        earse();
        mesh = (airMesh*) classGenerateFromBuffer(buf); 
        solver = (airSolver*) classGenerateFromBuffer(buf);
        control = (airControl*) classGenerateFromBuffer(buf);
    }
}

airProblem *airProblem::clone() const {
    return new airProblem(*this);
}

airFoil* airProblem::createFoil(double* foil) const {
    return airFoil::createFoil(foil);
}

double airProblem::run(const airFoil& foil) {
    DIR* dir = opendir(foil.name().data());
    if(! dir) createData(foil);
    double result = readForceCoeffsFile(foil);
//    double result = sin(foil.at(0) + foil.at(8) - foil.at(7)* foil.at(3));
    closedir(dir);
    return result;
}

airProblem& airProblem::operator = (const edaProblem &pro)
{
    earse();
    airProblem airPro = (const airProblem &)pro;
    mesh = airPro.mesh->clone();
    solver = airPro.solver->clone();
    control = airPro.control->clone();
    return *this;
}

void airProblem::earse() {
    if(mesh != NULL) {
        delete mesh;
        mesh = NULL;
    }
    if(solver != NULL) {
        delete solver;
        solver = NULL;
    }
    if(control != NULL) {
        delete control;
        control = NULL;
    }
}


double airProblem::readForceCoeffsFile(const airFoil& foil) {
    double result = MIN_VALUE;
    double time, Cd, Cl, Cm;
    string line;
    changeFolder(foil.name().data());    
    ifstream file("forces/0.0001/forceCoeffs.dat");
    if (file) {          
        getline(file, line);     
        while(file >> time >> Cd >> Cl >> Cm);            
        file.close();
    }
    if(time == control->getEndTime()) {
        result = Cl/Cd;  
    }
    changeFolder("..");  
    return result;
}

void airProblem::createData(const airFoil& foil) {
    
    cout << "Create Airfoil: " << foil.name() << endl;
    
    //Create folders
    createFolder(foil.name().data());
    changeFolder(foil.name().data());

    createFolder("0");
    createFolder("constant");
    createFolder("constant/polyMesh");    
    createFolder("system"); 
    catchCase(foil.detail().data());
 

    mesh->createData(foil);
    control->createData();
    solver->createData();
    
    runCase("blockMesh");
    runCase("checkMesh");
    
    if( findValue("checkMesh.log", "Mesh OK.") && foil.check() ) {        
        testCase("sonicFoam");
    } 
    
    if( findValue("testCase.log", "End")) {    
        control->updateData();        
        cout << "CFD Analysis..." << endl;
        runCase("sonicFoam",control->getNodes());
    }    
    changeFolder("..");
}

