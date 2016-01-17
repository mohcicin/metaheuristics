#include "edaSearchWrapper.h"

edaSearchWrapper::edaSearchWrapper()
  : searchAlgorithm (NULL)
{
}

edaSearchWrapper::edaSearchWrapper(edaBuffer &_buf)
{
  // New search object
  searchAlgorithm = NULL;
  setAlgorithm(_buf);
}

void edaSearchWrapper::setAlgorithm(edaBuffer &_buf)
{
  if (searchAlgorithm != NULL)
  {
    delete searchAlgorithm;
  }

  searchAlgorithm = (edaSearch*)classGenerateFromBuffer( _buf );
}

edaSearchWrapper::~edaSearchWrapper()
{
  if (searchAlgorithm != NULL)
  {
    delete searchAlgorithm;
  }
}
