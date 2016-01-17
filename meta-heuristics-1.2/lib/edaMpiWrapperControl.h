#ifndef __edaMpiWrapperControl_h__
#define __edaMpiWrapperControl_h__

#include <list>
#include <map>
#include <vector>
#include <sys/types.h>

using namespace std;

#include "edaSearch.h"
#include "edaDAG.h"
#include "edaDefine.h"
#include "edaWrapperControl.h"

// status of workers in master
#define EDA_MPI_PROCESSOR_IDLE      0
#define EDA_MPI_PROCESSOR_COMPUTING 1

// commands from master
#define EDA_MPI_START_SEARCH        0
#define EDA_MPI_QUIT                1

// respond status from worker
#define EDA_MPI_WAITING_COMMAND     0
#define EDA_MPI_SEARCH_FINISHED     1
#define EDA_MPI_QUIT_DONE           2
#define EDA_MPI_UNKNOWN_COMMAND     3
/// Cấu trúc edaMpiProcStatus chứa thông tin tra trạng thái của các node tìm kiếm
typedef struct {
  int stat_;
  int taskID_;
} edaMpiProcStatus;
/// Lớp edaMpiWrapperControl điều khiển quá trình tối ưu bằng cơ chế MPI
class edaMpiWrapperControl : public edaWrapperControl
{
 public:
  /// Khởi tạo đối tượng
  edaMpiWrapperControl();
  /// Hủy dối tượng
  ~edaMpiWrapperControl();

  bool search(edaSolutionList &list);
  
  /*
   * Checking for any return from workers
   *
   * \param nodeID Node that has finished its task
   * \return The polling result: no changed, finished or error
   */
  /// Thăm dò các kết quả trả về của các máy trạm
  /// \param nodeID ID của node cần thăm dò
  int polling( int &nodeID );

 private:
  list<int> searchOrder;
  int runningJobCount;
  int nprocs_;
  edaMpiProcStatus *workers_;
};

#endif
