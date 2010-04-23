#ifndef __FILECONFIG_H__
#define __FILECONFIG_H__

#include "Config.h"

#include <string>
#include <boost/utility.hpp>

namespace fw {
namespace config {

class FileConfig : public Config, private boost::noncopyable
{
public:
	void open(const std::string& filename);
	
protected:
	FileConfig(const std::string& filename);
};

}}

#endif /* end of include guard: __FILECONFIG_H__ */
