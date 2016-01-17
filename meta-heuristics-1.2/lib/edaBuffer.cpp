#include <memory.h>
#include <assert.h>

#include "edaBuffer.h"

edaBuffer::edaBuffer() 
  : bufferData(0)
{
  reset();
}

edaBuffer::~edaBuffer() 
{
  if ( bufferData )
    delete [] bufferData;
}

void edaBuffer::reset() 
{
  unpackPos = 0;
  if ( bufferData )
    delete [] bufferData;
  bufferData = 0;
  size_ = 0;
  actualSize_ = 0;
}

bool edaBuffer::checkUnPack(int sz)
{
  return true;
  // TODO complete this
}

void edaBuffer::Pack(const char *data, int count) 
{
  assert( count > 0 );

  // increase the buffer if needed
  if ( actualSize_ + count > size_ ){
    // calculate the new size
    int newsize = 1024 * ((actualSize_ + count) / 1024 + 1 );
    // allocate memory
    char *newBufferData = new char[newsize];
    // copy old data (if not NULL) to new memory
    if ( bufferData )
      memcpy( newBufferData, bufferData, actualSize_ );
    // delete the old memory (if not NULL)
    if ( bufferData )
      delete [] bufferData;
    // set data members to new values
    size_ = newsize;
    bufferData = newBufferData;
  }

  // copy new data to the back of new memory
  memcpy( bufferData + actualSize_, data, count );
  // set data members to new values
  actualSize_ += count;
}

void edaBuffer::UnPack(char *data, int count) 
{
  assert( count > 0);
  
  memcpy(data, ((char *)bufferData) + unpackPos, count);
  unpackPos += count;
}

void edaBuffer::Pack(const unsigned char *data, int count) 
{
  Pack((char *)data, count * sizeof(unsigned char));
}

void edaBuffer::UnPack(unsigned char *data, int count) 
{
  UnPack((char *)data, count * sizeof(unsigned char));
}

void edaBuffer::Pack(const bool *data, int count) 
{
  Pack((char *)data, count * sizeof(bool));
}

void edaBuffer::UnPack(bool *data, int count) 
{
  UnPack((char *)data, count * sizeof(bool));
}

void edaBuffer::Pack(const int *data, int count) 
{
  Pack((char *)data, count * sizeof(int));
}

void edaBuffer::UnPack(int *data, int count) 
{
  UnPack((char *)data, count * sizeof(int));
}

void edaBuffer::Pack(const unsigned *data, int count) 
{
  Pack((char *)data, count * sizeof(unsigned));
}

void edaBuffer::UnPack(unsigned *data, int count) 
{
  UnPack((char *)data, count * sizeof(unsigned));
}

void edaBuffer::Pack(const long *data, int count) 
{
  Pack((char *)data, count * sizeof(long));
}

void edaBuffer::UnPack(long *data, int count) 
{
  UnPack((char *)data, count * sizeof(long));
}

void edaBuffer::Pack(const unsigned long *data, int count) 
{
  Pack((char *)data, count * sizeof(unsigned long));
}

void edaBuffer::UnPack(unsigned long *data, int count) 
{
  UnPack((char *)data, count * sizeof(unsigned long));
}

void edaBuffer::Pack(const short *data, int count) 
{
  Pack((char *)data, count * sizeof(short));
}

void edaBuffer::UnPack(short *data, int count) 
{
  UnPack((char *)data, count * sizeof(short));
}

void edaBuffer::Pack(const unsigned short *data, int count) 
{
  Pack((char *)data, count * sizeof(unsigned short));
}

void edaBuffer::UnPack(unsigned short *data, int count) 
{
  UnPack((char *)data, count * sizeof(unsigned short));
}

void edaBuffer::Pack(const float *data, int count) 
{
  Pack((char *)data, count * sizeof(float));
}

void edaBuffer::UnPack(float *data, int count) 
{
  UnPack((char *)data, count * sizeof(float));
}

void edaBuffer::Pack(const double *data, int count) 
{
  Pack((char *)data, count * sizeof(double));
}

void edaBuffer::UnPack(double *data, int count) 
{
  UnPack((char *)data, count * sizeof(double));
}

#ifdef _PAROC_
void edaBuffer::Serialize(POPBuffer &buf, bool pack) 
{
//  bufferData.Serialize(buf, pack);

  if (pack) {
    buf.Push( "UnpackPos", "int", 1 );
    buf.Pack(&unpackPos, 1);
    buf.Pop();

    buf.Push( "BufferSize", "int", 1 );
    buf.Pack(&size_, 1);
    buf.Pop();

    buf.Push( "ActualSize", "int", 1 );
    buf.Pack(&actualSize_, 1);
    buf.Pop();

    buf.Push( "BufferData", "char", size_ );
    buf.Pack(bufferData, size_);
    buf.Pop();
  } else {
    // Clean up old data
    reset();

    buf.Push( "UnpackPos", "int", 1 );
    buf.UnPack(&unpackPos, 1);
    buf.Pop();

    buf.Push( "BufferSize", "int", 1 );
    buf.UnPack(&size_, 1);
    buf.Pop();

    buf.Push( "ActualSize", "int", 1 );
    buf.UnPack(&actualSize_, 1);
    buf.Pop();

    bufferData = new char[size_];
    buf.Push( "BufferData", "char", size_ );
    buf.UnPack(bufferData, size_);
    buf.Pop();
  }
}
#endif
