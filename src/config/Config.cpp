#include "Config.h"

namespace fw{
namespace config{

Config::Config(const std::string& filename) :
		_filename(filename)
{}

std::string Config::filename() const
{
	return _filename;
}
	
}}
