#ifndef __edaException_h__
#define __edaException_h__

#include <string>

/// Lớp edaException hiện thực việc xử lý ngoại lệ trong thư viện.
class edaException {
public:
    /// Khởi tạo đối tượng
	edaException() {}
    
    /// Khởi tạo đối tượng
    /// \param errorMessage chuổi lỗi
	edaException(std::string errorMessage) : errorMessage (errorMessage) {}
	
    /// Lấy chuổi lổi từ đối tượng
    /// \return Chuổi lỗi
	const std::string &getErrorMessage() {
		return errorMessage;
	}
	
private:
	std::string errorMessage;
};

#endif
