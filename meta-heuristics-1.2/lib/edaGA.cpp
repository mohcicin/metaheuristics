/* 
 * File:   edaGA.cpp
 * Author: tieuminh
 * 
 * Created on April 25, 2012, 9:43 PM
 */

#include "edaGA.h"

edaGA::edaGA()
       :edaSearch(),
        con(NULL),
        repre(NULL),
        nSlect(NULL),
        cross(NULL) {}

edaGA::edaGA(edaContinue *_con,  
             edaRepresentation *_repre,
             edaNaturalSelection *_nSlect,
             edaCrossover *_cross,
             edaMutation *_mute,
             unsigned int _elite,
             int _timeout,
             int _power)
  : edaSearch(_timeout, _power)
{
  elite = _elite;  
  repre = _repre->clone();
  con = _con->clone();
  nSlect = _nSlect->clone();
  cross = _cross->clone();
  mute = _mute->clone(); 
}

edaGA::edaGA(const edaGA &ga) 
  : edaSearch(ga)
{
  con = ga.con->clone();
  repre = ga.repre->clone();
  nSlect = ga.nSlect->clone();
  cross = ga.cross->clone();
  mute = ga.mute->clone(); 
  elite = ga.elite;
}
    
edaGA* edaGA::clone() const {
  return new edaGA(*this);
}

edaGA::~edaGA() {
    if(repre != NULL) {
      delete  repre;
      repre = NULL;
    }
    if(con != NULL) {
        delete con;
        con = NULL;
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
}

bool edaGA::search(edaSolutionList &list) 
{    
  edaPopulation pop; 
  edaSolutionList eList;
  con->init(); 
  
  printCSVLog("GA", TaskID, ProcID, "S", list.getBestID() , *con, list);  
  do {
      // Lay elite 
      eList = list.getList(elite);

      // Ma hoa
      repre->encode(list, pop);     
      
      //Chon loc tu nhien               
      nSlect->update(pop);    
      
      //Lai tao;
      cross->update(pop);       
      
      //Dot bien 
      mute->update(pop); 
      
      //Giai ma
      repre->decode(pop, list);     
      
      //Thay elite
      list.replace(eList);
      
      printCSVLog("GA", TaskID, ProcID, "P", list.getBestID() , *con, list); 
      

       
  } while(con->check(list));   
  
  printCSVLog("GA", TaskID, ProcID, "F", list.getBestID() , *con, list);   
  return true;
}

void edaGA::Serialize( edaBuffer &buf, bool pack ) {
  edaSearch::Serialize(buf, pack);
  if (pack)
  {
    buf.Pack(&elite);  
    con->doSerialize(buf, pack);
    nSlect->doSerialize(buf, pack);
    cross->doSerialize(buf, pack);
    mute->doSerialize(buf, pack);
    repre->doSerialize(buf, pack);    
  } else {
    buf.UnPack(&elite);  
    con = (edaContinue*)classGenerateFromBuffer( buf );
    nSlect = (edaNaturalSelection*)classGenerateFromBuffer( buf );
    cross = (edaCrossover*)classGenerateFromBuffer( buf );
    mute = (edaMutation*)classGenerateFromBuffer( buf );
    repre = (edaRepresentation*)classGenerateFromBuffer(buf);
  }
}
