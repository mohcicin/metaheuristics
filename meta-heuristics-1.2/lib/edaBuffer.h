#ifndef __edaBuffer_h__
#define __edaBuffer_h__

/// Lớp edaBuffer thực việc đóng gói (pack) và mở gói (unpack) các loại dữ liệu cơ bản.
class edaBuffer
#ifdef _PAROC_
: public POPBase
#endif
{
 public:
  edaBuffer();
  ~edaBuffer();
  
  /// Xóa tất cả các thông tin đang lưu giữ trong đối tượng
  void reset();
  
  // char
  void Pack(const char *data, int count = 1);
  void UnPack(char *data, int count = 1);
  
  // unsigned char
  void Pack(const unsigned char *data, int count = 1);
  void UnPack(unsigned char *data, int count = 1);
  
  // bool
  void Pack(const bool *data, int count = 1);
  void UnPack(bool *data, int count = 1);
	
  // int
  void Pack(const int *data, int count = 1);
  void UnPack(int *data, int count = 1);
	
  // unsigned
  void Pack(const unsigned *data, int count = 1);
  void UnPack(unsigned *data, int count = 1);
	
  // long
  void Pack(const long *data, int count = 1);
  void UnPack(long *data, int count = 1);
  
  // unsigned long
  void Pack(const unsigned long *data, int count = 1);
  void UnPack(unsigned long *data, int count = 1);
	
  // short
  void Pack(const short *data, int count = 1);
  void UnPack(short *data, int count = 1);
	
  // unsigned short
  void Pack(const unsigned short *data, int count = 1);
  void UnPack(unsigned short *data, int count = 1);
	
  // float
  void Pack(const float *data, int count = 1);
  void UnPack(float *data, int count = 1);
	
  // double
  void Pack(const double *data, int count = 1);
  void UnPack(double *data, int count = 1);

#ifdef _PAROC_
  void Serialize(POPBuffer &buf, bool pack);
#endif

  /// Lấy dữ liệu trong đối tượng
  /// \return Dữ liệu  nhị phân được lưu giữ trong đối tượng
  char *getBuffer() { return bufferData; }
  
  /// Lấy kích thưóc dữ liệu hiện lưu trữ trong đối tượng
  /// \return Kích thưóc dữ liệu được lưu giữ trong đối tượng
  int getActualSize() const { return actualSize_; }

  /// Gán thông tin dữ liệu cho đối tượng
  /// \param as Kích thước của dữ liệu (bội số của giá trị byte)
  /// \param buf Chuổi chứa thông tin dữ liệu dưới dạng nhị phân
  void setBuffer( int as, char *buf ) {
    size_ = actualSize_ = as;
    if ( bufferData )
      delete [] bufferData;
    bufferData = buf;
  }

 protected:
  bool checkUnPack(int sz);
	
  char *bufferData;
  int size_, actualSize_;

  int unpackPos;
};

#endif

