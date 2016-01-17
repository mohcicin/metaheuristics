#include "edaSimpleMoveTabuList.h"

edaSimpleMoveTabuList::edaSimpleMoveTabuList()
  : maxSize (0), currentSize (0)
{
}

edaSimpleMoveTabuList::edaSimpleMoveTabuList(unsigned int _maxSize)
  : maxSize (_maxSize), currentSize (0)
{
}

edaSimpleMoveTabuList::edaSimpleMoveTabuList(const edaSimpleMoveTabuList &tl)
{
  maxSize = tl.maxSize;
  currentSize = tl.currentSize;

  // Copy the tabu list
  std::list<edaMove*>::const_iterator moveIter;
  edaMove *tmpMove;

  for (moveIter = tl.tabuList.begin(); moveIter != tl.tabuList.end(); moveIter++)
  {
    tmpMove = (*moveIter)->clone();
    tabuList.push_back(tmpMove);
  }
}

edaSimpleMoveTabuList::~edaSimpleMoveTabuList()
{
  std::list<edaMove *>::iterator moveIter;
  for (moveIter = tabuList.begin(); moveIter != tabuList.end(); moveIter++)
  {
    if ((*moveIter) != NULL)
    {
      delete *moveIter;
    }
  }
}

edaTabuList* edaSimpleMoveTabuList::clone() const
{
  return new edaSimpleMoveTabuList(*this);
}

void edaSimpleMoveTabuList::init()
{
  // Do nothing
}

void edaSimpleMoveTabuList::add(const edaMove *_move, const edaSolution *_sol)
{
  edaMove *myMove = _move->clone();

  // Remove old move if it is already existed
  if (currentSize != 0)
  {
    removeMove(myMove);
  }

  tabuList.push_back(myMove);
  if (currentSize == maxSize)
  {
    // delete the move in the front and pop off the list
    edaMove *frontmove = tabuList.front();
    delete frontmove;
    tabuList.pop_front();
  }
  else
  {
    currentSize++;
  }

  // No need to delete myMove, destructor will do
  //delete myMove
}

void edaSimpleMoveTabuList::update()
{
  // Do nothing
}

bool edaSimpleMoveTabuList::check(const edaMove *_move, const edaSolution *_sol)
{
  std::list<edaMove *>::iterator moveIter;

  for (moveIter = tabuList.begin(); moveIter != tabuList.end(); moveIter++)
  {
    edaMove *tmpMove = *moveIter;
    if (*tmpMove == *_move)
    {
      return true;
    }
  }
  return false;
}

void edaSimpleMoveTabuList::Serialize(edaBuffer &buf, bool pack)
{
  if (pack)
  {
    buf.Pack(&maxSize, 1);
    buf.Pack(&currentSize, 1);

    // Pack the list size
    unsigned int listSize = tabuList.size();
    buf.Pack(&listSize, 1);

    std::list<edaMove *>::iterator moveIter;
    for (moveIter = tabuList.begin(); moveIter != tabuList.end(); moveIter++)
    {
      // Pack the elements of list
      (*moveIter)->doSerialize(buf, pack);
    }
  }
  else
  {
    // Clear old list content
    std::list<edaMove *>::iterator moveIter;
    for (moveIter = tabuList.begin(); moveIter != tabuList.end(); moveIter++)
    {
      if ((*moveIter) != NULL)
      {
        delete *moveIter;
      }
    }

    buf.UnPack(&maxSize, 1);
    buf.UnPack(&currentSize, 1);

    // Get the number of element
    unsigned int listSize;
    buf.UnPack(&listSize, 1);

    // UnPack the elements
    edaMove *tmpMove;
    for (unsigned int i = 0; i < listSize; i++)
    {
      tmpMove = (edaMove*)classGenerateFromBuffer(buf);
      tabuList.push_back(tmpMove);
    }
  }
}

void edaSimpleMoveTabuList::removeMove(const edaMove *_move)
{
  std::list<edaMove *>::iterator moveIter;

  for (moveIter = tabuList.begin(); moveIter != tabuList.end(); moveIter++)
  {
    if (*(*moveIter) == *_move)
    {
      tabuList.erase(moveIter);
      return;
    }
  }
}

