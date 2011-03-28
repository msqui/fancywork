#include "File.h"

namespace fw {
namespace util {

File::File()
{}

File::File(const std::string& filename, 
  std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out)
{
  open(filename, mode);
}

File::~File()
{
  close();
}

File::FilePtrT
File::create()
{
  return File::FilePtrT(new File());
}



void File::open(const std::string& filename, 
  std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out)
{
  close();
  _fs.open(filename.c_str(), mode);
}

void File::open_in(const std::string& filename)
{
  open(filename, std::ios_base::in);
}

void File::open_out(const std::string& filename)
{
  open(filename, std::ios_base::out);
}




bool File::getline(std::string& line)
{
  if( (!_fs.good()) || (_fs.eof()) )
  {
    return false;
  }
  
  std::getline(_fs, line);
  return true;
}

void File::close()
{
  if(_fs.is_open())
  {
    _fs.close();
  }
}

}}
