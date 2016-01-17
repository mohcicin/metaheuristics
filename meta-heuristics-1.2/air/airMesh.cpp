/* 
 * File:   PAR"Mesh"Mesh.cpp
 * Author: Tieu Minh
 * 
 * Created on March 6, 2013, 7:11 PM
 */

#include "airMesh.h"

#define pi         3.1415926535897932
#define rad        0.0174532925199433

airMesh::airMesh() 
{
    c = NAN;                    
    alpha = NAN;              
    scale = NAN;         
    
    H = NAN;                
    W = NAN;                 
    D = NAN;                    

    Ni = -1;             
    Nx = -1;             
    ND = -1;             
    NT = -1;            
    NW = -1;            

    ExpT = NAN;                  
    ExpD = NAN;                 
    ExpArc = NAN;               
}

airMesh::airMesh(const airMesh& mesh) 
{
  c = mesh.c;                
  alpha = mesh.alpha;     
  scale = mesh.scale;     
  
  H = mesh.H;             
  W = mesh.W;             
  D = mesh.D;             

  Ni = mesh.Ni;           
  Nx = mesh.Nx;           
  ND = mesh.ND;             
  NT = mesh.NT;            
  NW = mesh.NW;               

  ExpT = mesh.ExpT;           
  ExpD = mesh.ExpD;           
  ExpArc = mesh.ExpArc; 
}

airMesh::~airMesh() {}

airMesh* airMesh::clone() const {
  return new airMesh(*this);
}

airMesh::airMesh(const char* filename) 
{    
    edaINIReader* reader = new edaINIReader(filename); 

    c = reader->GetDouble("Mesh","Geometric chord length", NAN);
    alpha = reader->GetDouble("Mesh","Angle of attack", NAN);
    scale = reader->GetDouble("Mesh","Scaling factor", NAN);
    
    H = reader->GetDouble("Mesh","Half height of channel", NAN);
    W = reader->GetDouble("Mesh","Half depth of foil", NAN);
    D = reader->GetDouble("Mesh","Length of downstream Section", NAN);
    
    Ni = reader->GetInteger("Mesh","Number of interpolation points along the foil", -1);
    Nx = reader->GetInteger("Mesh","Number of mesh cells along the foil", -1);
    ND = reader->GetInteger("Mesh","Number of cells in the downstream direction", -1);
    NT = reader->GetInteger("Mesh","Number of cells the transverse direction", -1);
    NW = reader->GetInteger("Mesh","Number of cells in the y direction", -1);
    
    ExpT = reader->GetInteger("Mesh","Expansion rate in transverse direction", -1);
    ExpD = reader->GetInteger("Mesh","Expansion rate in the downstream direction", -1);
    ExpArc = reader->GetInteger("Mesh","Expansion rate along the inlet arc", -1);
    
    delete reader;
}

void airMesh::createData(const airFoil &parc) const 
{     
    const char* meshFile =  createBlockMeshFile(parc);
    moveData(meshFile,"constant/polyMesh");    
}

void airMesh::Serialize( edaBuffer &buf, bool pack ) {
  if(pack) {
    buf.Pack(&c, 1);
    buf.Pack(&alpha, 1);
    buf.Pack(&scale, 1);
    buf.Pack(&H, 1);
    buf.Pack(&D, 1);
    buf.Pack(&W, 1);
    buf.Pack(&Ni, 1);
    buf.Pack(&Nx, 1);
    buf.Pack(&ND, 1);
    buf.Pack(&NT, 1);
    buf.Pack(&NW, 1);
    buf.Pack(&ExpT, 1);
    buf.Pack(&ExpD, 1);
    buf.Pack(&ExpArc, 1);     
  }
  else {
    buf.UnPack(&c, 1);
    buf.UnPack(&alpha, 1);
    buf.UnPack(&scale, 1);
    buf.UnPack(&H, 1);
    buf.UnPack(&D, 1);
    buf.UnPack(&W, 1);
    buf.UnPack(&Ni, 1);
    buf.UnPack(&Nx, 1);
    buf.UnPack(&ND, 1);
    buf.UnPack(&NT, 1);
    buf.UnPack(&NW, 1);
    buf.UnPack(&ExpT, 1);
    buf.UnPack(&ExpD, 1);
    buf.UnPack(&ExpArc, 1);     
  }
}

void airMesh::printOn(ostream& os) const {
  os << "[Foil geometry]" << endl;
  os << "Geometric chord length (in meter): " << c << endl;  
  os << "Angle of attack (in deg): " << alpha << endl;  
  os << endl;
  
  os << "[Mesh dimension]" << endl;
  os << "Scaling factor: " << scale << endl;
  os << "Half height of channel (in meter): " << H << endl;
  os << "Half depth of foil (y-direction) (in meter): " << W << endl;        
  os << "Length of downstream Section (in meter): " << D << endl; 
  os << endl;
  
  os << "[Mesh resolution]" << endl;
  os << "Number of interpolation points along the foil: " << Ni << endl;
  os << "Number of mesh cells along the foil: " << Nx << endl;
  os << "Number of cells in the downstream direction: " << ND << endl;
  os << "Number of cells the transverse direction: " << NT << endl;
  os << "Number of cells in the y-direction (along the foil axis): " << NW << endl;
  os << endl;
  
  os << "[Expansion rates]" << endl;
  os << "Expansion rate in transverse direction: " << ExpT << endl;
  os << "Expansion rate in the downstream direction: " << ExpD << endl;
  os << "Expansion rate along the inlet arc: " << ExpArc << endl;
  os << endl;
}

ostream& operator<< (ostream &os, const airMesh &mesh) {
    mesh.printOn(os);
    return os;
}

const char* airMesh::createBlockMeshFile(const airFoil& par) const {
    // Create a vector with x-coordinates, camber and thickness
    double *beta = rnd.linspace(0, pi, Ni);
    
    double *x = new double[Ni];   
    for(unsigned int i = 0; i < Ni; i++) {
        x[i] = c*(0.5*(1-cos(beta[i])));
    }
    
    //Calculate coordinates of upper surface and lower surface         
    double* Xu = new double[Ni];
    double* Zu = new double[Ni];
    double* Xl = new double[Ni];
    double* Zl = new double[Ni];
    for(unsigned int i = 0; i < Ni; i++) {    
        Xu[i] = Xl[i] = x[i]*c;
        Zu[i] = par.z_up(x[i])*c;
        Zl[i] = par.z_lo(x[i])*c;  
    }
    
    //Rotate foil to reach specified angle of attack
    double* XuA = new double[Ni];
    double* ZuA = new double[Ni];
    double* XlA = new double[Ni];
    double* ZlA = new double[Ni];
    double alpha = this->alpha*rad;
    for(unsigned int i = 0; i < Ni; i++) {   
        XuA[i] = cos(alpha)*Xu[i]+ sin(alpha)*Zu[i];
        ZuA[i] = -sin(alpha)*Xu[i]+ cos(alpha)*Zu[i];
        XlA[i] = cos(alpha)*Xl[i]+ sin(alpha)*Zl[i];
        ZlA[i] = -sin(alpha)*Xl[i]+ cos(alpha)*Zl[i];
    } 
    
    // Find index i of max. camber
    int C_max_idx = -1;
    double C_max_val = 0;
    for(unsigned int i = 0; i < Ni; i++) {   
        if(C_max_val < Zu[i]) {
            C_max_idx = i;
            C_max_val = Zu[i];            
        }            
    }
    
    //Move point of mesh "nose"
    double NoseX = (-H+XuA[C_max_idx])*cos(alpha);
    double NoseZ = -(-H+XuA[C_max_idx])*sin(alpha);

    //Calculate the location of the vertices on the positive y-axis and put them in a matrix
    double vertices[24][3];    
    vertices[0][0] = NoseX;
    vertices[0][2] = NoseZ;
    vertices[1][0] = XuA[C_max_idx];
    vertices[1][2] = H;
    vertices[2][0] = XuA[Ni-1];
    vertices[2][2] = H;
    vertices[3][0] = D;
    vertices[3][2] = H;
    vertices[4][0] = 0;
    vertices[4][2] = 0;
    vertices[5][0] = XuA[C_max_idx];
    vertices[5][2] = ZuA[C_max_idx];
    vertices[6][0] = XlA[C_max_idx];
    vertices[6][2] = ZlA[C_max_idx];
    vertices[7][0] = XuA[Ni-1];
    vertices[7][2] = ZuA[Ni-1];
    vertices[8][0] = D;
    vertices[8][2] = ZuA[Ni-1];
    vertices[9][0] = XlA[C_max_idx];
    vertices[9][2] = -H;
    vertices[10][0] = XuA[Ni-1];
    vertices[10][2] = -H;
    vertices[11][0] = D;
    vertices[11][2] = -H;
    for(unsigned int i = 0; i < 12; i++) {        
        vertices[i][1] = W;
        vertices[i+12][0] = vertices[i][0];
        vertices[i+12][1] = -W;
        vertices[i+12][2] = vertices[i][2];
    }
    
    //Edge 4-5 and 16-17
    double pts1[C_max_idx - 1][3]; 
    double pts5[C_max_idx - 1][3]; 
    for(int i = 0; i < C_max_idx - 1; i++) {
        pts1[i][0] = XuA[i+1];
        pts1[i][1] = W;
        pts1[i][2] = ZuA[i+1];
        pts5[i][0] = pts1[i][0];
        pts5[i][1] = -W;
        pts5[i][2] = ZuA[i+1];                 

    }

   //Edge 5-7 and 17-19
    double pts2[Ni - C_max_idx - 2][3];
    double pts6[Ni - C_max_idx - 2][3];
    for(unsigned int i = 0; i < Ni - C_max_idx - 2; i++) {   
        pts2[i][0] = XuA[C_max_idx + i + 1];
        pts2[i][1] = W;
        pts2[i][2] = ZuA[C_max_idx + i + 1];
        pts6[i][0] = pts2[i][0];
        pts6[i][1] = -pts2[i][1];
        pts6[i][2] = pts2[i][2];        
    }

    //Edge 4-6 and 16-18
    double pts3[C_max_idx - 1][3];
    double pts7[C_max_idx - 1][3];
    for(int i = 0; i < C_max_idx - 1; i++) {
        pts3[i][0] = XlA[i+1]; 
        pts3[i][1] = W;
        pts3[i][2] = ZlA[i+1]; 
        pts7[i][0] = pts3[i][0];
        pts7[i][1] = -pts3[i][1];
        pts7[i][2] = pts3[i][2];        
    }

    //Edge 6-7 and 18-19
    double pts4[Ni - C_max_idx - 2][3];
    double pts8[Ni - C_max_idx - 2][3];
    for(unsigned int i = 0; i < Ni - C_max_idx - 2; i++) {
        pts4[i][0] = XlA[C_max_idx + i + 1];
        pts4[i][1] = W;
        pts4[i][2] = ZlA[C_max_idx + i + 1];
        pts8[i][0] = pts4[i][0];
        pts8[i][1] = -W;
        pts8[i][2] = pts4[i][2];                
    }    
   
    //Edge 0-1 and 12-13
    double pts9[3];
    double pts11[3]; 
    pts9[0] = -H*cos(pi/4)+XuA[C_max_idx];
    pts9[1] = W;
    pts9[2] = H*sin(pi/4);
    pts11[0] = pts9[0];
    pts11[1] = -W;
    pts11[2] = pts9[2];
    
    //Edge 0-9 and 12-21 
    double pts10[3];
    double pts12[3];
    pts10[0] = -H*cos(pi/4)+XuA[C_max_idx];
    pts10[1] = W;
    pts10[2] = -H*sin(pi/4);
    pts12[0] = pts10[0];
    pts12[1] = -W;
    pts12[2] = pts10[2];
    
    //Calculate number of mesh points along 4-5 and 4-6
    int Nleading = (int)(x[C_max_idx]/c*Nx);
    
    //Calculate number of mesh points along 5-7 and 6-7
    int Ntrailing = Nx-Nleading;
    
    //Open file
    FILE *mesh = fopen("blockMeshDict", "w");    
    
    //Write file
    fprints(mesh,"blockMeshDict");
    fprintf(mesh, "convertToMeters %f; \n", scale);
    fprintf(mesh, "\n");
    fprintf(mesh, "vertices \n");       
    fprintf(mesh, "( \n");
    for(unsigned int i = 0; i < 24; i++) 
        fprintf(mesh, "    (%f %f %f)\n", vertices[i][0], vertices[i][1], vertices[i][2]);
    fprintf(mesh, "); \n");
    fprintf(mesh, "\n");
    fprintf(mesh, "blocks \n");
    fprintf(mesh, "( \n");
    fprintf(mesh, "    hex (4 5 1 0 16 17 13 12)     (%d %d %d) edgeGrading (1 %f %f 1 %f %f %f %f 1 1 1 1) \n", Nleading, NT, NW, 1/ExpArc, 1/ExpArc, ExpT, ExpT, ExpT, ExpT);
    fprintf(mesh, "    hex (5 7 2 1 17 19 14 13)     (%d %d %d) simpleGrading (1 %f 1) \n", Ntrailing, NT, NW, ExpT);
    fprintf(mesh, "    hex (7 8 3 2 19 20 15 14)     (%d %d %d) simpleGrading (%f %f 1) \n", ND, NT, NW, ExpD, ExpT);
    fprintf(mesh, "    hex (16 18 21 12 4 6 9 0)     (%i %i %i) edgeGrading (1 %f %f 1 %f %f %f %f 1 1 1 1) \n", Nleading, NT, NW, 1/ExpArc, 1/ExpArc, ExpT, ExpT, ExpT, ExpT);
    fprintf(mesh, "    hex (18 19 22 21 6 7 10 9)    (%i %i %i) simpleGrading (1 %f 1) \n", Ntrailing, NT, NW, ExpT);
    fprintf(mesh, "    hex (19 20 23 22 7 8 11 10)   (%i %i %i) simpleGrading (%f %f 1) \n", ND, NT, NW, ExpD, ExpT);

    fprintf(mesh, "); \n");
    fprintf(mesh, "\n");
    fprintf(mesh, "edges \n");
    fprintf(mesh, "( \n");

    fprintf(mesh, "    spline 4 5 \n");
    fprintf(mesh, "        ( \n");
    for(int i = 0; i < C_max_idx - 1; i++) 
        fprintf(mesh, "            (%f %f %f) \n", pts1[i][0], pts1[i][1], pts1[i][2]);
    fprintf(mesh, "        ) \n");

    fprintf(mesh, "    spline 5 7 \n");
    fprintf(mesh, "        ( \n");
    for(unsigned int i = 0; i < Ni - C_max_idx - 2; i++) 
        fprintf(mesh, "            (%f %f %f)\n", pts2[i][0], pts2[i][1], pts2[i][2]);
    fprintf(mesh, "        ) \n");

    fprintf(mesh, "    spline 4 6 \n");
    fprintf(mesh, "        ( \n");
    for(int i = 0; i < C_max_idx - 1; i++) 
        fprintf(mesh, "            (%f %f %f)\n", pts3[i][0], pts3[i][1], pts3[i][2]);
    fprintf(mesh, "        ) \n");

    fprintf(mesh, "    spline 6 7 \n");
    fprintf(mesh, "        ( \n");
    for(unsigned int i = 0; i < Ni - C_max_idx - 2; i++) 
        fprintf(mesh, "            (%f %f %f)\n", pts4[i][0], pts4[i][1], pts4[i][2] );
    fprintf(mesh, "        ) \n");

    fprintf(mesh, "    spline 16 17 \n");
    fprintf(mesh, "        ( \n");
    for(int i = 0; i < C_max_idx - 1; i++) 
        fprintf(mesh, "            (%f %f %f)\n", pts5[i][0], pts5[i][1], pts5[i][2]);
    fprintf(mesh, "        ) \n");

    fprintf(mesh, "    spline 17 19 \n");
    fprintf(mesh, "        ( \n");
    for(unsigned int i = 0; i < Ni - C_max_idx - 2; i++) 
        fprintf(mesh, "            (%f %f %f)\n", pts6[i][0], pts6[i][1], pts6[i][2]);
    fprintf(mesh, "        ) \n");

    fprintf(mesh, "    spline 16 18 \n");
    fprintf(mesh, "        ( \n");
    for(int i = 0; i < C_max_idx - 1; i++) 
        fprintf(mesh, "            (%f %f %f)\n", pts7[i][0], pts7[i][1], pts7[i][2]);
    fprintf(mesh, "        ) \n");

    fprintf(mesh, "    spline 18 19 \n");
    fprintf(mesh, "        ( \n");
    for(unsigned int i = 0; i < Ni - C_max_idx - 2; i++) 
        fprintf(mesh, "            (%f %f %f)\n",  pts8[i][0], pts8[i][1], pts8[i][2]);
    fprintf(mesh, "        ) \n");

    fprintf(mesh, "    arc 0 1 (%f %f %f) \n", pts9[0], pts9[1], pts9[2]);
    fprintf(mesh, "    arc 0 9 (%f %f %f) \n",  pts10[0], pts10[1], pts10[2]);
    fprintf(mesh, "    arc 12 13 (%f %f %f) \n", pts11[0], pts11[1], pts11[2]);
    fprintf(mesh, "    arc 12 21 (%f %f %f) \n", pts12[0], pts12[1], pts12[2]);

    fprintf(mesh, "); \n");
    fprintf(mesh, "\n");
    fprintf(mesh, "boundary \n");
    fprintf(mesh, "( \n");

    fprintf(mesh, "    inlet \n");
    fprintf(mesh, "    { \n");
    fprintf(mesh, "        type patch; \n");
    fprintf(mesh, "        faces \n");
    fprintf(mesh, "        ( \n");
    fprintf(mesh, "            (1 0 12 13) \n");
    fprintf(mesh, "            (0 9 21 12) \n");
    fprintf(mesh, "        ); \n");
    fprintf(mesh, "    } \n");
    fprintf(mesh, "\n");

    fprintf(mesh, "    outlet \n");
    fprintf(mesh, "    { \n");
    fprintf(mesh, "        type patch; \n");
    fprintf(mesh, "        faces \n");
    fprintf(mesh, "        ( \n");
    fprintf(mesh, "            (11 8 20 23) \n");
    fprintf(mesh, "            (8 3 15 20) \n");
    fprintf(mesh, "        ); \n");
    fprintf(mesh, "    } \n");
    fprintf(mesh, "\n");

    fprintf(mesh, "    topAndBottom \n");
    fprintf(mesh, "    { \n");
    fprintf(mesh, "        type patch; \n");
    fprintf(mesh, "        faces \n");
    fprintf(mesh, "        ( \n");
    fprintf(mesh, "            (3 2 14 15) \n");
    fprintf(mesh, "            (2 1 13 14) \n");
    fprintf(mesh, "            (9 10 22 21) \n");
    fprintf(mesh, "            (10 11 23 22) \n");
    fprintf(mesh, "        ); \n");
    fprintf(mesh, "    } \n");
    fprintf(mesh, "\n");

    fprintf(mesh, "    airfoil \n");
    fprintf(mesh, "    { \n");
    fprintf(mesh, "        type wall; \n");
    fprintf(mesh, "        faces \n");
    fprintf(mesh, "        ( \n");
    fprintf(mesh, "            (5 4 16 17) \n");
    fprintf(mesh, "            (7 5 17 19) \n");
    fprintf(mesh, "            (4 6 18 16) \n");
    fprintf(mesh, "            (6 7 19 18) \n");
    fprintf(mesh, "        ); \n");
    fprintf(mesh, "    } \n");
    fprintf(mesh, "); \n");
    fprintf(mesh, " \n");
    fprintf(mesh, "mergePatchPairs \n");
    fprintf(mesh, "( \n");
    fprintf(mesh, "); \n");
    fprinte(mesh);
    
    delete[] beta;
    delete[] x;
    delete[] Xl;
    delete[] Xu;
    delete[] XlA;
    delete[] XuA;
    delete[] Zl;
    delete[] Zu;
    delete[] ZlA;
    delete[] ZuA;
    
    return "blockMeshDict";
}
