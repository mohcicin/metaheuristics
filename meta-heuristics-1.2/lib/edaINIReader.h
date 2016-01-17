#ifndef __EDAINIREADER_H__
#define __EDAINIREADER_H__

#include <map>
#include <string>
/// Lớp edaINIReader thực hiện việc xử lý file ASCII theo chuẩn INI.
class edaINIReader
{
public:
    /// Khởi tạo đối tượng
    edaINIReader();
    /// Hủy đối tượng
    virtual ~edaINIReader();
    /// Đọc file INI
    /// \param filename Tên file INI cần đọc
    edaINIReader(std::string filename);    
    /// Lấy thuộc tính dạng chuổi
    /// \param section Mục cần đọc
    /// \param name Tên thuộc tính
    /// \param default_value Giá trị mặc định khi thuộc tính không có giá trị
    std::string GetString(std::string section, std::string name,
                    std::string default_value);
    
    /// Lấy thuộc tính dạng số nguyên
    /// \param section Mục cần đọc
    /// \param name Tên thuộc tính
    /// \param default_value Giá trị mặc định khi thuộc tính không có giá trị
    long GetInteger(std::string section, std::string name, long default_value);    
    
    /// Lấy các thuộc tính dạng số nguyên vào mãng
    /// \param section Mục cần đọc
    /// \param name Tên thuộc tính
    /// \param default_value Giá trị mặc định khi thuộc tính không có giá trị
    /// \param number Số thuộc tính
    long* GetInteger(std::string section, std::string name, double default_value, unsigned int number);
    
    /// Lấy thuộc tính dạng số thực
    /// \param section Mục cần đọc
    /// \param name Tên thuộc tính
    /// \param default_value Giá trị mặc định khi thuộc tính không có giá trị
    double GetDouble(std::string section, std::string name, double default_value);
    
    /// Lấy các thuộc tính dạng số thực vào mãng
    /// \param section Mục cần đọc
    /// \param name Tên thuộc tính
    /// \param default_value Giá trị mặc định khi thuộc tính không có giá trị
    /// \param number Số thuộc tính
    double* GetDouble(std::string section, std::string name, double default_value, unsigned int number);
    
    /// Lấy thuộc tính dạng luận lý
    /// \param section Mục cần đọc
    /// \param name Tên thuộc tính
    /// \param default_value Giá trị mặc định khi thuộc tính không có giá trị    
    bool GetBoolean(std::string section, std::string name, bool default_value);
    

private:
    int _error;
    std::map<std::string, std::string> _values;
    static std::string MakeKey(std::string section, std::string name);
    static int ValueHandler(void* user, const char* section, const char* name,
                            const char* value);
    void checkError();
};

#endif  // __EDAINIREADER_H__
