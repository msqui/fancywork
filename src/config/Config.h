#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <string>
#include <boost/shared_ptr.hpp>

namespace fw {
namespace config {

class Config
{
public:
	typedef boost::shared_ptr<Config> ConfigPtrT;
	
	template <typename CreatorT>
	static ConfigPtrT create(const std::string& filename)
	{
		return CreatorT::create(filename);
	}
	
	std::string filename() const;
	
	virtual void open(const std::string& filename) = 0;
	
protected:
	Config(const std::string& filename);
	
	std::string _filename;
};

}}

#endif /* end of include guard: __CONFIG_H__ */
