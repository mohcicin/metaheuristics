#include "edaTS.h"

edaTS::edaTS()
  : edaSearch(),
    move(NULL),
    con(NULL),
    moveExpl(NULL)
{
}

edaTS::edaTS(int _power)
  : edaSearch(_power),
    move(NULL),
    con(NULL),
    moveExpl(NULL)
{
}

edaTS::edaTS( edaMove *_move,
    edaMoveGen *_moveNext,
    edaTabuList *_tabuList,
    edaAspirCrit *_aspirCrit,
    edaContinue *_continueCriteria,
    int _timeout,
    int _power)
  : edaSearch(_timeout, _power)
{
  move = _move->clone();
  moveExpl = new edaTSMoveExpl(_moveNext, _tabuList, _aspirCrit);
  con = _continueCriteria->clone();
}

edaTS::edaTS(edaMove *_move,
    edaTSMoveExpl *_moveExpl,
    edaContinue *_continueCriteria,
    int _timeout,
    int _power)
  : edaSearch( _timeout, _power)
{
  move = _move->clone();
  moveExpl = _moveExpl->clone();
  con = _continueCriteria->clone();
}

edaTS::edaTS(const edaTS &ts) 
  : edaSearch(ts)
{
  move = ts.move->clone();
  moveExpl = ts.moveExpl->clone();
  con = ts.con->clone();

}

edaTS* edaTS::clone() const 
{
  return new edaTS(*this);
}

edaTS::~edaTS()
{
  easer();
}

bool edaTS::search(edaSolutionList &list) 
{  

  for (unsigned int i = 0; i < list.size(); i++) 
  {
    edaSolution &sol = *list[i];
    edaSolution *bestSol = sol.clone();
    edaSolution *newSol = sol.clone();
    
    con->init();  
    printCSVLog("TS", TaskID, ProcID, "S", i, *con, list);
    
    do
    {     
      *newSol = sol;

      moveExpl->explore(move, sol, *newSol);
      if (newSol->evaluate() - bestSol->evaluate() > Epsilon) 
      {
        *bestSol = *newSol;        
      }
      
      sol = *newSol;      
      printCSVLog("TS", TaskID, ProcID, "P", i, *con, list);
 
      

    } while (con->check(list));
    
    sol = *bestSol;

    printCSVLog("TS", TaskID, ProcID, "F", i, *con, list);
    
    delete newSol;
    delete bestSol;
  }

  
  return true;
}

void edaTS::Serialize(edaBuffer &buf, bool pack)
{
  edaSearch::Serialize(buf, pack);

  if (pack)
  {
    move->doSerialize(buf, pack);
    con->doSerialize(buf, pack);
    moveExpl->doSerialize(buf, pack);
  }
  else
  {
    // Clean old data
    easer();

    move = (edaMove*)classGenerateFromBuffer(buf);
    con = (edaContinue*)classGenerateFromBuffer(buf);
    moveExpl = (edaTSMoveExpl*)classGenerateFromBuffer(buf);
  }
}

void edaTS::easer()
{
  if (move != NULL)
  {
    delete move;
    move = NULL;
  }
  if (con != NULL)
  {
    delete con;
    con = NULL;
  }
  if (moveExpl != NULL)
  {
    delete moveExpl;
    moveExpl = NULL;
  }
}
