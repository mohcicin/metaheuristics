#include "edaTSMoveExpl.h"

edaTSMoveExpl::edaTSMoveExpl ():moveNext (NULL),
tabuList (NULL), aspirCrit (NULL)
{
  moveSelect = new edaBestImprSelect ();
}

edaTSMoveExpl::edaTSMoveExpl (const edaMoveGen * _moveNext,
                              const edaTabuList * _tabuList,
                              const edaAspirCrit * _aspirCrit)
{
  moveSelect = new edaBestImprSelect ();
  moveNext = _moveNext->clone ();
  tabuList = _tabuList->clone ();
  aspirCrit = _aspirCrit->clone ();

  tabuList->init ();
  aspirCrit->init ();
}

edaTSMoveExpl::edaTSMoveExpl (const edaTSMoveExpl & _moveExpl)
{
  moveSelect = new edaBestImprSelect ();
  moveNext = _moveExpl.moveNext->clone ();
  tabuList = _moveExpl.tabuList->clone ();
  aspirCrit = _moveExpl.aspirCrit->clone ();
}

edaTSMoveExpl::~edaTSMoveExpl ()
{
  clean ();
  delete moveSelect;
}

edaTSMoveExpl *
edaTSMoveExpl::clone () const
{
  return new edaTSMoveExpl (*this);
}

void
edaTSMoveExpl::explore (const edaMove * move,
                        edaSolution & oldSolution, edaSolution & newSolution)
{
  edaMove *myMove = move->clone ();

  myMove->init (oldSolution);
  moveSelect->init (oldSolution.evaluate ());

  // Explore
  do
    {
      double fitness = myMove->incrEval (oldSolution);
      if (!tabuList->check (myMove, &oldSolution)
          || aspirCrit->check (myMove, fitness))
        {
          if (!moveSelect->update (myMove, fitness))
            {
              break;
            }
        }
    }
  while (moveNext->generate (myMove, oldSolution));
  edaMove *bestMove = myMove->clone ();
  
  double bestFitness;

  moveSelect->save (bestMove, bestFitness);
  bestMove->update (newSolution);

//  printDebug(3, moveSelect->getClassName() << ", " << bestMove->getClassName()  
//    << " " << *bestMove << ", fitness " << newSolution.evaluate()
//    << ", time " << time(NULL) );
  
  tabuList->update ();
  tabuList->add (bestMove, &newSolution);

  delete bestMove;
  delete myMove;
  
}

void
edaTSMoveExpl::Serialize (edaBuffer & buf, bool pack)
{
  if (pack)
    {
      moveNext->doSerialize (buf, pack);
      tabuList->doSerialize (buf, pack);
      aspirCrit->doSerialize (buf, pack);
    }
  else
    {
      clean ();
      moveNext = (edaMoveGen *) classGenerateFromBuffer (buf);
      tabuList = (edaTabuList *) classGenerateFromBuffer (buf);
      aspirCrit = (edaAspirCrit *) classGenerateFromBuffer (buf);
    }
}

void
edaTSMoveExpl::clean ()
{
  if (moveNext != NULL)
    {
      delete moveNext;
      moveNext = NULL;
    }
  if (tabuList != NULL)
    {
      delete tabuList;
      tabuList = NULL;
    }
  if (aspirCrit != NULL)
    {
      delete aspirCrit;
      aspirCrit = NULL;
    }
}
