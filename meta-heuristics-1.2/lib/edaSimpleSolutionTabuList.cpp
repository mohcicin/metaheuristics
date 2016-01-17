#include "edaSimpleSolutionTabuList.h"

edaSimpleSolutionTabuList::edaSimpleSolutionTabuList()
  : maxSize (0), currentSize (0)
{
}

edaSimpleSolutionTabuList::edaSimpleSolutionTabuList(unsigned int _maxSize)
  : maxSize (_maxSize), currentSize (0)
{
}

edaSimpleSolutionTabuList::edaSimpleSolutionTabuList(const edaSimpleSolutionTabuList &tl)
{
  maxSize = tl.maxSize;
  currentSize = tl.currentSize;

  // Copy the tabu list
  std::list<edaSolution *>::const_iterator solutionIter;
  edaSolution *tmpSol;

  for (solutionIter = tl.tabuList.begin(); solutionIter != tl.tabuList.end(); solutionIter++)
  {
    tmpSol = (*solutionIter)->clone();
    tabuList.push_back(tmpSol);
  }
}

edaSimpleSolutionTabuList::~edaSimpleSolutionTabuList()
{
  std::list<edaSolution *>::iterator solutionIter;
  for (solutionIter = tabuList.begin(); solutionIter != tabuList.end(); solutionIter++)
  {
    if ((*solutionIter) != NULL)
    {
      delete *solutionIter;
    }
  }
}

edaTabuList* edaSimpleSolutionTabuList::clone() const
{
  return new edaSimpleSolutionTabuList(*this);
}

void edaSimpleSolutionTabuList::init()
{
  // Do nothing
}

void edaSimpleSolutionTabuList::add(const edaMove *_move, const edaSolution *_sol)
{
  // Apply the move on the solution
  edaMove *myMove = _move->clone();
  edaSolution *mySol = _sol->clone();
  //myMove->update(*mySol);

  // Remove old move if it is already existed
  if (currentSize != 0)
  {
    removeSolution(mySol);
  }

  // insert solution to the back of list
  tabuList.push_back(mySol);

  // keep the size of tabu list
  if (currentSize == maxSize)
  {
    edaSolution *fsol = tabuList.front();
    delete fsol;
    tabuList.pop_front();
  }
  else
  {
    currentSize++;
  }

  // delete the move
  delete myMove;
}

void edaSimpleSolutionTabuList::update()
{
  // Do nothing
}

bool edaSimpleSolutionTabuList::check(const edaMove *_move, const edaSolution *_sol)
{
  // Apply the move on the solution
  edaMove *myMove = _move->clone();
  edaSolution *mySol = _sol->clone();
  myMove->update(*mySol);

  std::list<edaSolution *>::iterator solutionIter;
  bool result = false;

  for (solutionIter = tabuList.begin(); solutionIter != tabuList.end(); solutionIter++)
  {
    edaSolution *tmpSol = *solutionIter;
    if (*tmpSol == *mySol)
    {
      result = true;
      break;
    }
  }

  delete myMove;
  delete mySol;

  return result;
}

void edaSimpleSolutionTabuList::Serialize(edaBuffer &buf, bool pack)
{
  if (pack)
  {
    buf.Pack(&maxSize, 1);
    buf.Pack(&currentSize, 1);

    // Pack the list size
    unsigned int listSize = tabuList.size();
    buf.Pack(&listSize, 1);

    std::list<edaSolution *>::iterator solutionIter;
    for (solutionIter = tabuList.begin(); solutionIter != tabuList.end(); solutionIter++)
    {
      // Pack the elements of list
      (*solutionIter)->doSerialize(buf, pack);
    }
  }
  else
  {
    // Clear old list content
    std::list<edaSolution *>::iterator solutionIter;
    for (solutionIter = tabuList.begin(); solutionIter != tabuList.end(); solutionIter++)
    {
      if ((*solutionIter) != NULL)
      {
        delete *solutionIter;
      }
    }

    buf.UnPack(&maxSize, 1);
    buf.UnPack(&currentSize, 1);

    // Get the number of element
    unsigned int listSize;
    buf.UnPack(&listSize, 1);

    // UnPack the elements
    edaSolution *tmpSol;
    for (unsigned int i = 0; i < listSize; i++)
    {
      tmpSol = (edaSolution*)classGenerateFromBuffer(buf);
      tabuList.push_back(tmpSol);
    }
  }
}

void edaSimpleSolutionTabuList::removeSolution(const edaSolution *_sol)
{
  std::list<edaSolution *>::iterator solutionIter;

  for (solutionIter = tabuList.begin(); solutionIter != tabuList.end(); solutionIter++)
  {
    if (*(*solutionIter) == *_sol)
    {
      // remove the solution
      edaSolution *sol = *solutionIter;
      delete sol;

      // remove the pointer to the solution
      tabuList.erase(solutionIter);
      return;
    }
  }
}

