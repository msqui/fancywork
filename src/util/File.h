#ifndef __FILE_H__
#define __FILE_H__

#include <string>
#include <fstream>

#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>

namespace fw {
namespace util {
	
class File : private boost::noncopyable
{
public:
	typedef boost::shared_ptr<File> FilePtrT;
	
	static FilePtrT create();
	
	~File();
	
	void open(const std::string& filename, std::ios_base::openmode);
	void open_in(const std::string& filename);
	void open_out(const std::string& filename);
	
	bool getline(std::string& line);
	void close();
	
protected:
	File();
	File(const std::string& filename, std::ios_base::openmode mode);
	
private:
	std::fstream _fs;
};

}}

#endif /* end of include guard: __FILE_H__ */
