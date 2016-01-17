/* 
 * File:   PARSECMesh.h
 * Author: Tieu Minh
 *
 * Created on March 6, 2013, 7:11 PM
 */

#ifndef AIRMESH_H
#define	AIRMESH_H

#include "Define.h"
#include "airFoil.h"

class airMesh : public edaSerialize  {
public:
  airMesh();
  airMesh(const airMesh& mesh);
  airMesh(const char* filename);
  virtual ~airMesh();
  airMesh* clone() const;
  void createData(const airFoil& foil) const;
  void printOn(ostream& os) const;
  void Serialize( edaBuffer &buf, bool pack );  
  setClassID(_USERCLASSID_ + _CLSID_AIR_MESH_);
  
private: 
  const char* createBlockMeshFile(const airFoil& par) const;
  
  //Foil geometry
  double c;                     //Geometric chord length
  double alpha;                 //Angle of attack (in radians)

  //Mesh dimensions
  double scale;                 //Scaling factor
  double H;                     //Half height of channel
  double W;                     //Half depth of foil (y-direction)
  double D;                     //Length of downstream section

  unsigned int Ni;              //Number of interpolation points along the foil
  unsigned int Nx;              //Number of mesh cells along the foil
  unsigned int ND;              //Number of cells in the downstream direction
  unsigned int NT;              //Number of cells the transverse direction
  unsigned int NW;              //Number of cells in the y-direction (along the foil axis)

  // Expansion rates
  double ExpT;                  //Expansion rate in transverse direction
  double ExpD;                  //Expansion rate in the downstream direction
  double ExpArc;                //Expansion rate along the inlet arc

};

ostream& operator<< (ostream &os, const airMesh &meshGen);
#endif	/* AIRMESH_H */

