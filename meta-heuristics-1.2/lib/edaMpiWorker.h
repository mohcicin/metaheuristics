#ifndef __edaMpiWorker_h__
#define __edaMpiWorker_h__
/// Lớp edaMpiWorker thực thi việc phân chia tác vụ giữa giữa máy chủ và các máy trạm
class edaMpiWorker {
 public:
  /// Khởi tạo đối tượng
  /// \param master ID của node master
  edaMpiWorker( int master = 0 );
  /// Hủy đối tượng
  ~edaMpiWorker();
  /// Thực thi tác vụ do máy chủ phân phối
  void serve();

 private:
  int master_;
  int rank_;
};

#endif
