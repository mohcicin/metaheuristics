#include "edaHC.h"

edaHC::edaHC()
  : edaSearch(), move (NULL), moveExpl (NULL), con (NULL)
{
}

edaHC::edaHC(int _power)
  : edaSearch(_power), move (NULL), moveExpl (NULL), con (NULL)
{
}

edaHC::edaHC(edaMove *_move,
    edaMoveGen *_moveNext,
    edaMoveSelect *_moveSelect,
    edaContinue *_continueCrit,
    int _timeout,
    int _power)
  : edaSearch(_timeout, _power)
{
  move = _move->clone();
  moveExpl = new edaHCMoveExpl( _moveNext, _moveSelect );
  con = _continueCrit->clone();
}

edaHC::edaHC(edaMove *_move,
    edaHCMoveExpl *_moveExpl,
    edaContinue *_continueCrit,
    int _timeout,
    int _power)
  : edaSearch(_timeout, _power)
{
  move = _move->clone();
  moveExpl = new edaHCMoveExpl( *_moveExpl );
  con = _continueCrit->clone();

}

edaHC::edaHC(const edaHC &hc) 
  : edaSearch(hc) 
{
    move = hc.move->clone();
    moveExpl = hc.moveExpl->clone();
    con = hc.con->clone();
}

edaHC *edaHC::clone() const {
  return new edaHC(*this);
}


edaHC::~edaHC()
{
  delete move;
  delete moveExpl;
  delete con;
}

bool edaHC::search(edaSolutionList &list) 
{     
  for (unsigned int i = 0; i < list.size(); i++) 
  {    
    edaSolution *sol = list[i];    
    edaSolution *newSol = NULL;
    con->init();
    
    printCSVLog("HC", TaskID, ProcID, "S", i, *con, list);
    
    do
    {
      newSol = sol->clone();
      moveExpl->explore(move, *sol, *newSol);
      
      if (newSol->evaluate() - sol->evaluate() > Epsilon)
      {
        *sol = *newSol;
        delete newSol;
      }
      else
      {
        delete newSol;
        break;
      }    
//      cout << *sol << ": " << sol->evaluate() << endl;
      printCSVLog("HC", TaskID, ProcID, "P", i, *con, list);
    } while ( con->check(list) );
    printCSVLog("HC", TaskID, ProcID, "F", i, *con, list);
  }

  return true;
}

void edaHC::Serialize(edaBuffer &buf, bool pack)
{
  edaSearch::Serialize(buf, pack);
  if (pack)
  {
    moveExpl->doSerialize(buf, pack);
    move->doSerialize(buf, pack);
    con->doSerialize(buf, pack);
  }
  else
  {
    moveExpl = (edaHCMoveExpl*)classGenerateFromBuffer( buf );
    move = (edaMove*)classGenerateFromBuffer( buf );
    con = (edaContinue*) classGenerateFromBuffer( buf );
  }
}
