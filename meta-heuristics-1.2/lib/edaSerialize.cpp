#include <stdlib.h>

#include "edaSerialize.h"
#include "edaBestImprSelect.h"
#include "edaDefine.h"
#include "edaExpCoolingSchedule.h"
#include "edaLinearCoolingSchedule.h"
#include "edaGenContinue.h"
#include "edaFitContinue.h"
#include "edaHC.h"
#include "edaSA.h"
#include "edaTS.h"
#include "edaGA.h"
#include "edaMA.h"
#include "edaNS.h"
#include "edaNoAspirCrit.h"
#include "edaImprBestFitAspirCrit.h"
#include "edaSimpleMoveTabuList.h"
#include "edaSimpleSolutionTabuList.h"
#include "edaChromosome.h"
#include "edaPopulation.h"
#include "edaRankSelection.h"
#include "edaRouletteWheelSelection.h"
#include "edaOnePointCrossover.h"
#include "edaLambdaPointCrossover.h"
#include "edaRandomMutation.h"
#include "edaAdaption.h"
#include "edaFirstImprSelect.h"
#include "edaPartiallyMatchedCrossover.h"
#include "edaRandSwapMutation.h"
#include "edaVarFitContinue.h"

void edaSerialize::doSerialize(edaBuffer &buf, bool pack)
{
  if (pack)
  {
    int clsid = getClassID();

    buf.Pack(&clsid, 1);
  }

  this->Serialize(buf, pack);
}

void edaSerialize::Serialize(edaBuffer &buf, bool pack)
{}

static edaSerialize* classGenerate(int clsid)
{
  switch (clsid){
  case (_SYSCLASSID_ + _CLSID_EDASOLUTIONLIST_ ):
    return (edaSerialize *)new edaSolutionList();
    
  case (_SYSCLASSID_ + _CLSID_EDAHC_):
    return (edaSerialize *)new edaHC();
    
  case (_SYSCLASSID_ + _CLSID_EDASA_):
    return (edaSerialize *)new edaSA();
    
  /*
  case (_SYSCLASSID_ + _CLSID_EDAMOVE_):
    return (edaSerialize *)new edaMove();
  */
  /*
  case (_SYSCLASSID_ + _CLSID_EDAMOVEGEN_):
    return (edaSerialize *)new edaMoveGen();
  */

  case (_SYSCLASSID_ + _CLSID_EDAHCMOVEEXPL_):
    return (edaSerialize *)new edaHCMoveExpl();

  /*
  case (_SYSCLASSID_ + _CLSID_EDAMOVESELECT_):
    return (edaSerialize *)new edaMoveSelect();
  */

  case (_SYSCLASSID_ + _CLSID_EDABESTIMPRSELECT_):
    return (edaSerialize *)new edaBestImprSelect();
    
  case (_SYSCLASSID_ + _CLSID_EDAFIRSTIMPRSELECT_):
    return (edaSerialize *)new edaFirstImprSelect();  

  case (_SYSCLASSID_ + _CLSID_EXP_COOLING_SCHEDULE_):
    return (edaSerialize *)new edaExpCoolingSchedule;
    
  case (_SYSCLASSID_ + _CLSID_LINEAR_COOLING_SCHEDULE_):
    return (edaSerialize *)new edaLinearCoolingSchedule;

  case (_SYSCLASSID_ + _CLSID_GEN_CONTINUE_):
    return (edaSerialize *)new edaGenContinue;

  case (_SYSCLASSID_ + _CLSID_FIT_CONTINUE_):
    return (edaSerialize *)new edaFitContinue;
    
  case (_SYSCLASSID_ + _CLSID_VAR_FIT_CONTINUE_):
    return (edaSerialize *)new edaVarFitContinue;
    
  // Tabu search
  case (_SYSCLASSID_ + _CLSID_EDATS_):
    return (edaSerialize *)new edaTS;
    
  case (_SYSCLASSID_ + _CLSID_EDANS_):
    return (edaSerialize *)new edaNS;
/*
  case (_SYSCLASSID_ + _CLSID_EDATABULIST_):
    return (edaSerialize *)new edaTabuList;
*/
  case (_SYSCLASSID_ + _CLSID_EDATSMOVEEXPL_):
    return (edaSerialize *)new edaTSMoveExpl;
/*
  case (_SYSCLASSID_ + _CLSID_EDAASPIRCRIT_):
    return (edaSerialize *)new edaAspirCrit;
*/
  case (_SYSCLASSID_ + _CLSID_EDANOASPIRCRIT_):
    return (edaSerialize *)new edaNoAspirCrit;

  case (_SYSCLASSID_ + _CLSID_EDAIMPRBESTFITASPIRCRIT_):
    return (edaSerialize *)new edaImprBestFitAspirCrit;

  case (_SYSCLASSID_ + _CLSID_EDASIMPLEMOVETABULIST_):
    return (edaSerialize *)new edaSimpleMoveTabuList;

  case (_SYSCLASSID_ + _CLSID_EDASIMPLESOLUTIONTABULIST_):
    return (edaSerialize *)new edaSimpleSolutionTabuList;

// GA search
  case (_SYSCLASSID_ + _CLSID_EDAGA_):
    return (edaSerialize *)new edaGA;

  case (_SYSCLASSID_ + _CLSID_EDACHROMOSOME_):
   return (edaSerialize *)new edaChromosome;   
   
  case (_SYSCLASSID_ + _CLSID_EDAPOPULATION_):
   return (edaSerialize *)new edaPopulation;   
   
  case (_SYSCLASSID_ + _CLSID_EDARANKSELECTION_):
   return (edaSerialize *)new edaRankSelection;   
   
  case (_SYSCLASSID_ + _CLSID_EDAROULETTEWHEELSELECTION_):
   return (edaSerialize *)new edaRouletteWheelSelection;   
      
  case (_SYSCLASSID_ + _CLSID_EDAONEPOINTCROSSOVER_):
   return (edaSerialize *)new edaOnePointCrossover;  
   
  case (_SYSCLASSID_ + _CLSID_EDALAMBDAPOINTCROSSOVER_):
   return (edaSerialize *)new edaLambdaPointCrossover; 
   
  case (_SYSCLASSID_ + _CLSID_EDARANDOMMUTATION_):
   return (edaSerialize *)new edaRandomMutation; 
    
  case (_SYSCLASSID_ + _CLSID_EDAPARTIALLYMATCHEDCROSSOVER_):
    return (edaSerialize *)new edaPartiallyMatchedCrossover;
    
  case (_SYSCLASSID_ + _CLSID_EDARANDSWAPMUTATION_):
    return (edaSerialize *)new edaRandSwapMutation;  
    
// MA search
  case (_SYSCLASSID_ + _CLSID_EDAMA_):
    return (edaSerialize *)new edaMA;
    
  case (_SYSCLASSID_ + _CLSID_EDAADAPTION_):
    return (edaSerialize *)new edaAdaption;    
    
  default:
    return userClassGenerate(clsid);
  }
}

#pragma weak userClassGenerate
edaSerialize *userClassGenerate( int clsid )
{
  std::cerr << "User must override userClassGenerate()" << std::endl;
  exit(-1);
}

edaSerialize *classGenerateFromBuffer( edaBuffer &buf )
{
  int clsid;
  edaSerialize *obj;
  
  // unpack the ID
  buf.UnPack( &clsid, 1 );

  // generate the object
  obj = classGenerate( clsid );
  obj->Serialize( buf, false );

  // return
  return obj;
}

