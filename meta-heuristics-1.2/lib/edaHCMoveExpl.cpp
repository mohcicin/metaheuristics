#include "edaHCMoveExpl.h"

edaHCMoveExpl::edaHCMoveExpl(const edaMoveGen *_moveNext,
    const edaMoveSelect *_moveSelect)
{
  moveNext = _moveNext->clone();
  moveSelect = _moveSelect->clone();
}

edaHCMoveExpl::edaHCMoveExpl( const edaHCMoveExpl &_moveExpl )
{
  moveNext = _moveExpl.moveNext->clone();
  moveSelect = _moveExpl.moveSelect->clone();
}

edaHCMoveExpl::~edaHCMoveExpl()
{
  delete moveNext;
  delete moveSelect;
}

edaHCMoveExpl* edaHCMoveExpl::clone() const
{
  return new edaHCMoveExpl(*this);
}

/**
 * Run the explorer
 * 
 * \param oldSolution The current solution
 * \param newSolution The new solution
 */
void edaHCMoveExpl::explore(const edaMove *move, 
			    edaSolution &oldSolution, 
			    edaSolution &newSolution)
{
  edaMove *mymove = move->clone();

  // Restart the exploration
  mymove->init(oldSolution);
  moveSelect->init(oldSolution.evaluate());  
  
  // Explore
  while(moveSelect->update(mymove, mymove->incrEval(oldSolution))
	&& moveNext->generate(mymove, oldSolution)) {
//      cout << *mymove << ": " << mymove->incrEval(oldSolution) << endl;
  };

  // Save the result
  edaMove *bestMove = mymove->clone();
  double bestFitness;
  
  if (moveSelect->save(bestMove, bestFitness)) {
//      cout << *bestMove << ": " << bestMove->incrEval(newSolution) << endl;
      bestMove->update(newSolution);  
  }
            
  delete bestMove;
  delete mymove;
  
}

void edaHCMoveExpl::Serialize(edaBuffer &buf, bool pack)
{
  if (pack)
  {
    moveNext->doSerialize(buf, pack);
    moveSelect->doSerialize(buf, pack);
  }
  else
  {
    moveNext = (edaMoveGen*)classGenerateFromBuffer( buf );
    moveSelect = (edaMoveSelect*)classGenerateFromBuffer( buf );
  }
}
