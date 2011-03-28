#ifndef __FILE_H__
#define __FILE_H__

#include <string>
#include <fstream>

#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>

namespace fw {
namespace util {
/**
 * File abstraction for RAII paradigm
**/
class File : private boost::noncopyable
{
public:
  typedef boost::shared_ptr<File> FilePtrT;
  
  static FilePtrT create();
  
  virtual ~File();
  
  void open(const std::string& filename, std::ios_base::openmode);
  void open_in(const std::string& filename);
  void open_out(const std::string& filename);
  
  /**
   * Reads line from opened file
   * \param[out] line string to which read line
   * \return true if line is read and false if eof reached or in case of bad fstrea
  **/
  bool getline(std::string& line);
  
  /**
   * Is called automatically by destructor
  **/
  void close();
  
protected:
  File();
  File(const std::string& filename, std::ios_base::openmode mode);
  
private:
  std::fstream _fs;
};

}}

#endif /* end of include guard: __FILE_H__ */
