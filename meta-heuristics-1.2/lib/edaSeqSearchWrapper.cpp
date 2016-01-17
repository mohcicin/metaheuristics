#include "edaSeqSearchWrapper.h"

edaSeqSearchWrapper::edaSeqSearchWrapper() : edaSearchWrapper()
{
}

edaSeqSearchWrapper::edaSeqSearchWrapper(edaBuffer &_buf) :
  edaSearchWrapper(_buf)
{
}

edaSeqSearchWrapper::~edaSeqSearchWrapper()
{
}

void edaSeqSearchWrapper::search( edaBuffer &_buf_in, edaBuffer &_buf_out)
{
  // Create new solution object
  edaSolutionList *list = (edaSolutionList*)classGenerateFromBuffer( _buf_in );

  // Call search algorithm
  searchAlgorithm->search( *list );

  // Pack output solution
  list->doSerialize( _buf_out, true );

  // Clean up
  delete list;

  // return
}
