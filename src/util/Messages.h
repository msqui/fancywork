#ifndef __MESSAGES_H__
#define __MESSAGES_H__

#include <string>

#include <boost/utility.hpp>

namespace fw {
namespace util {
/**
 * Contains command line messages.
 * Can not be instantiated.
**/
class Messages : private boost::noncopyable
{
public:
  static const std::string usage; 
  static const std::string version;
  
  static const std::string no_files_to_process;
  
private:
  /**
   * This class can not be instantiated
  **/
  Messages ();
};

}}

#endif /* __MESSAGES_H__ */

