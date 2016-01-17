/* 
 * File:   airSolver.cpp
 * Author: Tieu Minh
 * 
 * Created on April 23, 2013, 10:34 AM
 */

#include "Define.h"


#include "airSolver.h"

#define     R           286                    //Gas contant for air
#define     Cp          (Cv + R)                 //Constant pressure specifc heats 
#define     g           Cp/(Cv)                //Ratio of specific heats 
#define     a           sqrt(g*R*T)            //Speed of sound
#define     sqt(x)      x*x                    
#define     magUinf     sqrt(sqt(mach[0])+sqt(mach[1])+sqt(mach[2]))*a        

airSolver::airSolver() {
    strcpy(ras,"");
    mach[0] = mach[1] = mach[2];
    p = NAN;
    T = NAN;
    k = NAN;
    epsilon = NAN;
    mu = NAN;
    kappa = NAN;
    Cv = NAN;
    M = NAN;    
}

airSolver::airSolver(const airSolver& orig) {
    strcpy(ras, orig.ras);
    memcpy(mach, orig.mach,3*sizeof(double));

    p = orig.p;
    T = orig.T;
    k = orig.k;
    epsilon = orig.epsilon;
    mu = orig.mu;
    kappa = orig.kappa;
    Cv = orig.Cv;
    M = orig.M;    
}

airSolver::~airSolver() {}

airSolver* airSolver::clone() const {
    return new airSolver(*this);
}

airSolver::airSolver(const char* filename) {
    edaINIReader reader(filename); 
    
    string parser = reader.GetString("Model", "RASModel", "kEpsilon");
    strcpy(ras,parser.c_str());

    double* tmp = reader.GetDouble("Model","Mach Number",NAN,3);
    
    mach[0] = tmp[0]; mach[1] = tmp[1]; mach[2] = tmp[2]; 
    p = reader.GetDouble("Model", "Static Pressure", NAN);
    T = reader.GetDouble("Model", "Inlet Temperature", NAN);
    k = reader.GetDouble("Model", "Turbulent Kinetic Energy", NAN);  
    epsilon = reader.GetDouble("Model", "Turbulent Dissipation Rate", NAN);  
    mu = reader.GetDouble("Model", "Viscosity", NAN);  
    
    kappa = reader.GetDouble("Model", "Conductivity", NAN);  
    Cv = reader.GetDouble("Model", "Specific Heat at Constant Volume", NAN);  
    M = reader.GetDouble("Model", "Molecular Weight", NAN);  
    
    delete[] tmp;
}

void airSolver::createData() const {    

    moveData(createTurbulencePropertiesFile(),"constant");
    moveData(createRASPropertiesFile(),"constant");
    moveData(createThermophysicalPropertiesFile(),"constant");

    moveData(createVelocityInititalCondition(),"0");
    moveData(createPressureInititalCondition(),"0");
    moveData(createTemperatureInititalCondition(),"0");
    moveData(createKineticInititalCondition(),"0");
    moveData(createDissipationInititalCondition(),"0");    

    moveData(createFvSchemesFile(),"system");
    moveData(createFvSolutionFile(),"system");
    moveData(createForceCoeffsFile(), "system");

}

void airSolver::printOn(ostream& os) const {
    os << "[Model]" << endl;
    os << "RASModel : " << ras << endl;

    os << "Mach Number : [" << mach[0] << " " << mach[1] << " "
           << mach[2] << "]"   << endl;
    os << "Static Pressure : " << p << endl;
    os << "Inlet Temperature : " << T << endl;
    os << "Turbulent Kinetic Energy : " << k << endl;
    os << "Turbulent Dissipation Rate : " << epsilon << endl;
    os << "Viscosity : " << mu << endl;
    os << "Conductivity :" << kappa << endl;
    os << "Specific Heat at Constant Volume : " << Cv << endl;
    os << "Molecular Weight : " << M << endl;  
    os << endl;
}

void airSolver::Serialize( edaBuffer &buf, bool pack ) {
    if(pack) {
        buf.Pack(ras, 32);
        buf.Pack(mach, 3);
        buf.Pack(&p, 1);
        buf.Pack(&T, 1);
        buf.Pack(&k, 1);
        buf.Pack(&epsilon, 1);
        buf.Pack(&mu, 1);
        buf.Pack(&kappa, 1);
        buf.Pack(&Cv, 1);
        buf.Pack(&M, 1);   

    }
    else {
        buf.UnPack(ras, 32);
        buf.UnPack(mach, 3);
        buf.UnPack(&p, 1);
        buf.UnPack(&T, 1);
        buf.UnPack(&k, 1);
        buf.UnPack(&epsilon, 1);
        buf.UnPack(&mu, 1);
        buf.UnPack(&kappa, 1);
        buf.UnPack(&Cv, 1);
        buf.UnPack(&M, 1);  

    }
}

const char* airSolver::createTurbulencePropertiesFile() const {
    FILE *file = fopen("turbulenceProperties", "w");  
    fprints(file, "turbulenceProperties");
    fprintf(file, "simulationType  RASModel; \n");
    fprinte(file); 
    return "turbulenceProperties";
}

const char* airSolver::createRASPropertiesFile() const {
    FILE *file = fopen("RASProperties", "w");  
    fprints(file, "RASProperties");
    fprintf(file, "RASModel        %s; \n", ras);
    fprintf(file, "turbulence      on; \n");
    fprintf(file, "printCoeffs     on; \n"); 
    fprinte(file); 
    return "RASProperties";
}

const char* airSolver::createThermophysicalPropertiesFile() const {
    
    FILE *file = fopen("thermophysicalProperties", "w");  
    fprints(file, "thermophysicalProperties");
    fprintf(file, "thermoType      ePsiThermo<pureMixture<constTransport<specieThermo<eConstThermo<perfectGas>>>>>; \n");
    fprintf(file, "mixture              \n");
    fprintf(file, "{                    \n");
    
    fprintf(file, "\tspecie             \n");
    fprintf(file, "\t{                  \n");
    fprintf(file, "\t\tnMoles        %d;\n", 1);
    fprintf(file, "\t\tmolWeight     %e;\n", M);
    fprintf(file, "\t} \n");
    
    fprintf(file, "\tthermodynamics \n");
    fprintf(file, "\t{ \n");
    fprintf(file, "\t\tCv            %e;\n", Cv);
    fprintf(file, "\t\tHf            %e;\n", 2.544e+06);
    fprintf(file, "\t}                  \n");
    
    fprintf(file, "\ttransport \n");
    fprintf(file, "\t{ \n");
    fprintf(file, "\t\tmu            %e;\n", mu);
    fprintf(file, "\t\tPr            %e;\n", Cp*mu/kappa);
    fprintf(file, "\t}                  \n");
    fprintf(file, "}                    \n");
    fprinte(file);     
    return "thermophysicalProperties";

}

const char* airSolver::createVelocityInititalCondition() const {

    FILE *file = fopen("U", "w");  
    
    fprints(file, "U","volVectorField");
    fprintf(file, "dimensions      [0 1 -1 0 0 0 0];    \n");
    fprintf(file, "internalField   uniform (%e %e %e);  \n", mach[0]*a, mach[1]*a, mach[2]*a);
    
    fprintf(file, "boundaryField                        \n");
    fprintf(file, "{                                    \n");  
    
    fprintf(file, "\tinlet                              \n");
    fprintf(file, "\t{                                  \n");  
    fprintf(file, "\t\ttype            inletOutlet;     \n");   
    fprintf(file, "\t\tinletValue      $internalField;  \n"); 
    fprintf(file, "\t}                                  \n"); 
    
    fprintf(file, "\toutlet                             \n");
    fprintf(file, "\t{                                  \n");  
    fprintf(file, "\t\ttype            inletOutlet;     \n");   
    fprintf(file, "\t\tinletValue      $internalField;  \n"); 
    fprintf(file, "\t}                                  \n"); 
    
    fprintf(file, "\ttopAndBottom                       \n");
    fprintf(file, "\t{                                  \n");  
    fprintf(file, "\t\ttype            inletOutlet;     \n");   
    fprintf(file, "\t\tinletValue      $internalField;  \n"); 
    fprintf(file, "\t}                                  \n"); 
    
    fprintf(file, "\tdefaultFaces                       \n");
    fprintf(file, "\t{                                  \n");  
    fprintf(file, "\t\ttype            empty;           \n");   
    fprintf(file, "\t}                                  \n"); 
    
    fprintf(file, "\tairfoil                            \n");
    fprintf(file, "\t{                                  \n");  
    fprintf(file, "\t\ttype            fixedValue;      \n");   
    fprintf(file, "\t\tvalue           uniform (0 0 0); \n"); 
    fprintf(file, "\t}                                  \n");     
    
    fprintf(file, "}                                    \n");  

    fprinte(file);   
    return "U";
}

const char* airSolver::createPressureInititalCondition() const {
    FILE *file = fopen("p", "w");  
    
    fprints(file, "p","volScalarField");
    fprintf(file, "dimensions      [1 -1 -2 0 0 0 0];   \n");
    fprintf(file, "internalField   uniform %e;          \n", p);
    
    fprintf(file, "boundaryField                        \n");
    fprintf(file, "{                                    \n");  
    
    fprintf(file, "\tinlet                              \n");
    fprintf(file, "\t{                                  \n");  
    fprintf(file, "\t\ttype            zeroGradient;    \n");   
    fprintf(file, "\t}                                  \n"); 
    
    fprintf(file, "\toutlet                             \n");
    fprintf(file, "\t{                                  \n");  
    fprintf(file, "\t\ttype            zeroGradient;    \n");   
    fprintf(file, "\t}                                  \n"); 
    
    fprintf(file, "\ttopAndBottom                       \n");
    fprintf(file, "\t{                                  \n");  
    fprintf(file, "\t\ttype            zeroGradient;    \n");   
    fprintf(file, "\t}                                  \n"); 
    
    fprintf(file, "\tdefaultFaces                       \n");
    fprintf(file, "\t{                                  \n");  
    fprintf(file, "\t\ttype            empty;           \n");   
    fprintf(file, "\t}                                  \n"); 
    
    fprintf(file, "\tairfoil                            \n");
    fprintf(file, "\t{                                  \n");  
    fprintf(file, "\t\ttype            zeroGradient;    \n");  
    fprintf(file, "\t}                                  \n");     
    
    fprintf(file, "}                                    \n");  

    fprinte(file);   
    return "p";    
    
} 

const char* airSolver::createTemperatureInititalCondition() const {
    
    FILE *file = fopen("T", "w");  
    
    fprints(file, "T","volScalarField");
    fprintf(file, "dimensions      [0 0 0 1 0 0 0];     \n");
    fprintf(file, "internalField   uniform %e;          \n", T);
    
    fprintf(file, "boundaryField                        \n");
    fprintf(file, "{                                    \n");  
    
    fprintf(file, "\tinlet                              \n");
    fprintf(file, "\t{                                  \n");  
    fprintf(file, "\t\ttype            inletOutlet;     \n");   
    fprintf(file, "\t\tinletValue      $internalField;  \n"); 
    fprintf(file, "\t}                                  \n"); 
    
    fprintf(file, "\toutlet                             \n");
    fprintf(file, "\t{                                  \n");  
    fprintf(file, "\t\ttype            inletOutlet;     \n");   
    fprintf(file, "\t\tinletValue      $internalField;  \n"); 
    fprintf(file, "\t}                                  \n"); 
    
    fprintf(file, "\ttopAndBottom                       \n");
    fprintf(file, "\t{                                  \n");  
    fprintf(file, "\t\ttype            inletOutlet;     \n");   
    fprintf(file, "\t\tinletValue      $internalField;  \n"); 
    fprintf(file, "\t}                                  \n"); 
    
    fprintf(file, "\tdefaultFaces                       \n");
    fprintf(file, "\t{                                  \n");  
    fprintf(file, "\t\ttype            empty;           \n");   
    fprintf(file, "\t}                                  \n"); 
    
    fprintf(file, "\tairfoil                            \n");
    fprintf(file, "\t{                                  \n");  
    fprintf(file, "\t\ttype            zeroGradient;    \n");  
    fprintf(file, "\t}                                  \n");     
    
    fprintf(file, "}                                    \n");  

    fprinte(file);   
    return "T";  
}  

const char* airSolver::createKineticInititalCondition() const {
    FILE *file = fopen("k", "w");  
    
    fprints(file, "k","volScalarField");
    fprintf(file, "dimensions      [0 2 -2 0 0 0 0];    \n");
    fprintf(file, "internalField   uniform %e;          \n", k);
    
    fprintf(file, "boundaryField                        \n");
    fprintf(file, "{                                    \n");  
    
    fprintf(file, "\tinlet                              \n");
    fprintf(file, "\t{                                  \n");  
    fprintf(file, "\t\ttype            inletOutlet;     \n");   
    fprintf(file, "\t\tinletValue      $internalField;  \n"); 
    fprintf(file, "\t}                                  \n"); 
    
    fprintf(file, "\toutlet                              \n");
    fprintf(file, "\t{                                  \n");  
    fprintf(file, "\t\ttype            inletOutlet;     \n");   
    fprintf(file, "\t\tinletValue      $internalField;  \n"); 
    fprintf(file, "\t}                                  \n"); 
    
    fprintf(file, "\ttopAndBottom                       \n");
    fprintf(file, "\t{                                  \n");  
    fprintf(file, "\t\ttype            inletOutlet;     \n");   
    fprintf(file, "\t\tinletValue      $internalField;  \n"); 
    fprintf(file, "\t}                                  \n"); 
    
    fprintf(file, "\tdefaultFaces                       \n");
    fprintf(file, "\t{                                  \n");  
    fprintf(file, "\t\ttype            empty;           \n");   
    fprintf(file, "\t}                                  \n"); 
    
    fprintf(file, "\tairfoil                            \n");
    fprintf(file, "\t{                                  \n");  
    fprintf(file, "\t\ttype            compressible::kqRWallFunction;\n");  
    fprintf(file, "\t\tvalue           $internalField;  \n");  
    fprintf(file, "\t}                                  \n");     
    
    fprintf(file, "}                                    \n");  

    fprinte(file);   
    return "k";  
} 

const char* airSolver::createDissipationInititalCondition() const {
    FILE *file = fopen("epsilon", "w");  
    
    fprints(file, "epsilon","volScalarField");
    fprintf(file, "dimensions      [0 2 -3 0 0 0 0];    \n");
    fprintf(file, "internalField   uniform %e;          \n", epsilon);
    
    fprintf(file, "boundaryField                        \n");
    fprintf(file, "{                                    \n");  
    
    fprintf(file, "\tinlet                              \n");
    fprintf(file, "\t{                                  \n");  
    fprintf(file, "\t\ttype            inletOutlet;     \n");   
    fprintf(file, "\t\tinletValue      $internalField;  \n"); 
    fprintf(file, "\t}                                  \n"); 
    
    fprintf(file, "\toutlet                              \n");
    fprintf(file, "\t{                                  \n");  
    fprintf(file, "\t\ttype            inletOutlet;     \n");   
    fprintf(file, "\t\tinletValue      $internalField;  \n"); 
    fprintf(file, "\t}                                  \n"); 
    
    fprintf(file, "\ttopAndBottom                       \n");
    fprintf(file, "\t{                                  \n");  
    fprintf(file, "\t\ttype            inletOutlet;     \n");   
    fprintf(file, "\t\tinletValue      $internalField;  \n"); 
    fprintf(file, "\t}                                  \n"); 
    
    fprintf(file, "\tdefaultFaces                       \n");
    fprintf(file, "\t{                                  \n");  
    fprintf(file, "\t\ttype            empty;           \n");   
    fprintf(file, "\t}                                  \n"); 
    
    fprintf(file, "\tairfoil                            \n");
    fprintf(file, "\t{                                  \n");  
    fprintf(file, "\t\ttype            compressible::epsilonWallFunction;\n");  
    fprintf(file, "\t\tvalue           $internalField;  \n"); 
    fprintf(file, "\t\tCmu             %e;              \n", 0.09); 
    fprintf(file, "\t\tkappa           %e;              \n", 0.41); 
    fprintf(file, "\t\tE               %e;              \n", 9.8);  
    fprintf(file, "\t}                                  \n");    
    fprintf(file, "}                                    \n");  

    fprinte(file);   
    return "epsilon";  
} 

const char* airSolver::createForceCoeffsFile() const {    
    FILE *file = fopen("forceCoeffs", "w");  
    fprints(file, "forceCoeffs");
    fprintf(file, "forces                       \n");
    fprintf(file, "{                            \n");
    fprintf(file, "\ttype                       forceCoeffs;         \n");
    fprintf(file, "\tfunctionObjectLibs         ( \"libforces.so\" );\n");
    fprintf(file, "\toutputControl              timeStep;            \n");
    fprintf(file, "\toutputInterval             %d;                  \n", 1);
    fprintf(file, "\tpatches                    ( airfoil );         \n");     
    fprintf(file, "\tpName                      p;                   \n");
    fprintf(file, "\tUName                      U;                   \n");
    fprintf(file, "\tlog                        true;                \n");
    fprintf(file, "\trhoInf                     1;                   \n");
    fprintf(file, "\tCofR                       ( 0 0 0 );           \n");
    fprintf(file, "\tliftDir                    ( 0 0 1 );           \n");                      
    fprintf(file, "\tdragDir                    ( 1 0 0 );           \n");    
    fprintf(file, "\tpitchAxis                  ( 0 1 0 );           \n"); 
    fprintf(file, "\tmagUInf                    %e;                  \n", magUinf); 
    fprintf(file, "\tlRef                       1;                   \n"); 
    fprintf(file, "\tAref                       1;                   \n"); 
    fprintf(file, "}                                                 \n");
    fprinte(file);
    return "forceCoeffs";
}

const char* airSolver::createFvSchemesFile() const {
    
    FILE *file = fopen("fvSchemes", "w"); 
    fprints(file, "fvSchemes");
    
    fprintf(file, "ddtSchemes                       \n");
    fprintf(file, "{                                \n");
    fprintf(file, "\tdefault         Euler;         \n");
    fprintf(file, "}                                \n");   
    
    fprintf(file, "gradSchemes                          \n");
    fprintf(file, "{                                    \n");
    fprintf(file, "\tdefault         Gauss linear;      \n");
    fprintf(file, "}                                    \n");  

    fprintf(file, "divSchemes                                               \n");
    fprintf(file, "{                                                        \n");
    fprintf(file, "\tdefault                        none;                   \n");
    fprintf(file, "\tdiv(phi,U)                     Gauss limitedLinearV 1; \n");
    fprintf(file, "\tdiv(phi,k)                     Gauss upwind;           \n");    
    fprintf(file, "\tdiv(phi,epsilon)               Gauss upwind;           \n");  
    fprintf(file, "\tdiv(phi,R)                     Gauss upwind;           \n"); 
    fprintf(file, "\tdiv(R)                         Gauss linear;           \n");  
    fprintf(file, "\tdiv(phid,p)                    Gauss limitedLinear 1;  \n");    
    fprintf(file, "\tdiv(phi,K)                     Gauss limitedLinear 1;  \n"); 
    fprintf(file, "\tdiv(phi,e)                     Gauss limitedLinear 1;  \n");
    fprintf(file, "\tdiv((muEff*dev2(T(grad(U)))))  Gauss linear;           \n");        
    fprintf(file, "}                                                        \n");  

    fprintf(file, "laplacianSchemes                                          \n");
    fprintf(file, "{                                                         \n");
    fprintf(file, "\tdefault                        none;                    \n");       
    fprintf(file, "\tlaplacian(muEff,U)             Gauss linear limited 0.5;\n");
    fprintf(file, "\tlaplacian(DkEff,k)             Gauss linear limited 0.5;\n");
    fprintf(file, "\tlaplacian(DREff,R)             Gauss linear limited 0.5;\n");                                               
    fprintf(file, "\tlaplacian(DepsilonEff,epsilon) Gauss linear limited 0.5;\n");  
    fprintf(file, "\tlaplacian((rho*(1|A(U))),p)    Gauss linear limited 0.5;\n");  
    fprintf(file, "\tlaplacian(alphaEff,e)          Gauss linear limited 0.5;\n");  
    fprintf(file, "}                                                         \n");  
    
    fprintf(file, "interpolationSchemes                 \n");
    fprintf(file, "{                                    \n");
    fprintf(file, "\tdefault               linear;      \n");
    fprintf(file, "}                                    \n"); 

    fprintf(file, "snGradSchemes                        \n");
    fprintf(file, "{                                    \n");
    fprintf(file, "\tdefault               corrected;   \n");
    fprintf(file, "}                                    \n"); 

    fprintf(file, "fluxRequired                         \n");
    fprintf(file, "{                                    \n");
    fprintf(file, "\tdefault               no;          \n");
    fprintf(file, "\tp;                                 \n");
    fprintf(file, "}                                    \n"); 

    fprinte(file);
    return "fvSchemes";
}

const char* airSolver::createFvSolutionFile() const {
    FILE *file = fopen("fvSolution", "w"); 
    fprints(file, "fvSolution");
    
    fprintf(file, "solvers                      \n");
    fprintf(file, "{                            \n"); 
    
    fprintf(file, "\tp                          \n");   
    fprintf(file, "\t{                          \n"); 
    fprintf(file, "\t\tsolver           PBiCG;  \n");
    fprintf(file, "\t\tpreconditioner   DILU;   \n");        
    fprintf(file, "\t\ttolerance        1e-12;  \n");         
    fprintf(file, "\t\trelTol           0;      \n");  
    fprintf(file, "\t}                          \n");
    
    fprintf(file, "\trho                        \n");   
    fprintf(file, "\t{                          \n"); 
    fprintf(file, "\t\tsolver           PCG;    \n");
    fprintf(file, "\t\tpreconditioner   DIC;    \n");        
    fprintf(file, "\t\ttolerance        1e-08;  \n");         
    fprintf(file, "\t\trelTol           0;      \n");  
    fprintf(file, "\t}                          \n");
    
    fprintf(file, "\t\"(U|e|k|epsilon|R)\"      \n");   
    fprintf(file, "\t{                          \n"); 
    fprintf(file, "\t\t$p;                      \n");        
    fprintf(file, "\t\ttolerance        1e-08;  \n");         
    fprintf(file, "\t\trelTol           0;      \n");  
    fprintf(file, "\t}                          \n");    
    fprintf(file, "}                            \n"); 
       
    fprintf(file, "PISO                         \n");   
    fprintf(file, "{                            \n"); 
    fprintf(file, "\tnCorrectors        2;      \n");    
    fprintf(file, "\tnNonOrthogonalCorrectors 2;\n"); 
    fprintf(file, "}                            \n");   
    
    fprinte(file);
    return "fvSolution";
}

ostream& operator<< (ostream &os, const airSolver &sol) {
    sol.printOn(os);
    return os;
}
