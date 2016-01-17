/* 
 * File:   edaME.cpp
 * Author: tieuminh
 * 
 * Created on April 25, 2012, 9:43 PM
 */

#include "edaMA.h"
#include "edaMutation.h"


edaMA::edaMA():
        edaSearch(),
        con(NULL),
        repre(NULL),
        nSlect(NULL),
        cross(NULL),
        adapt(NULL),
        bestSol(NULL) {    
}

edaMA::edaMA(edaContinue *_con,
             edaRepresentation *_repre,   
             edaNaturalSelection *_nSlect,
             edaCrossover *_cross,
             edaMutation *_mute,
             edaAdaption *_adapt,
             unsigned int _elite,
             int _timeout,
             int _power)
  : edaSearch(_timeout, _power)
{
    elite = _elite;
    con = _con->clone();
    repre = _repre->clone();
    nSlect = _nSlect->clone();
    cross = _cross->clone();
    mute = _mute->clone();
    adapt = _adapt->clone();
}

edaMA::edaMA(const edaMA &ma) 
  : edaSearch(ma)
{
    elite = ma.elite;
    con = ma.con->clone();
    repre = ma.repre->clone();
    nSlect = ma.nSlect->clone();
    cross = ma.cross->clone();
    mute = ma.mute->clone();
    adapt = ma.adapt->clone();
}

edaMA* edaMA::clone() const {
  return new edaMA(*this);
}

edaMA::~edaMA() {
  if(con != NULL) {
    delete con;
    con = NULL;
  }
  if(repre != NULL) {
    delete repre;
    repre = NULL;
  }
  if(nSlect != NULL) {
    delete nSlect;
    nSlect = NULL;
  }
  if(cross != NULL) {
    delete cross;
    cross = NULL;
  }
  if(mute != NULL) {
    delete mute;
    mute = NULL;
  }
  if(adapt != NULL) {
    delete adapt;
    adapt = NULL;
  }
}

bool edaMA::search(edaSolutionList &list) 
{    
  edaPopulation pop; 
  edaSolutionList eList;
  con->init(); 
  
  printCSVLog("MA", TaskID, ProcID, "S", list.getBestID() , *con, list);  
  do {         
    // Lay elite 
    eList = list.getList(elite);
    
    // Ma hoa
    repre->encode(list, pop);      
    
    //Chon loc tu nhien     
    nSlect->update(pop);        

    
    //Lai tao
    cross->update(pop);
    
    //Dot bien    
    mute->update(pop);
    
    //Giai ma      
    repre->decode(pop, list);      
    
    //Cai tien
    adapt->update(list);
    
    //Thay elite
    list.replace(eList);
    
    printCSVLog("MA", TaskID, ProcID, "P", list.getBestID() , *con, list);  
    
  } while(con->check(list));      
  printCSVLog("MA", TaskID, ProcID, "F", list.getBestID() , *con, list);  

  
  return true;
}

void edaMA::Serialize( edaBuffer &buf, bool pack ) {
  edaSearch::Serialize(buf, pack);
  if (pack)
  {
    buf.Pack(&elite);  
    con->doSerialize(buf, pack);
    repre->doSerialize(buf, pack);
    nSlect->doSerialize(buf, pack);
    cross->doSerialize(buf, pack);
    mute->doSerialize(buf, pack);
    adapt->doSerialize(buf,pack);      
  }
  else
  {   
    buf.UnPack(&elite);  
    con = (edaContinue*)classGenerateFromBuffer( buf );
    repre = (edaRepresentation*)classGenerateFromBuffer( buf );
    nSlect = (edaNaturalSelection*)classGenerateFromBuffer( buf );
    cross = (edaCrossover*)classGenerateFromBuffer( buf );
    mute = (edaMutation*)classGenerateFromBuffer( buf );  
    adapt = (edaAdaption*)classGenerateFromBuffer( buf );
  }
}

