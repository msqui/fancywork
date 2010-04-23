#include "FileConfig.h"

#include <fstream>

namespace fw {
namespace config {

FileConfig::FileConfig(const std::string& filename) :
	Config(filename)
{
	open(filename);
}

void FileConfig::open(const std::string& filename)
{
	// std::ifstream ifs();
	// ifs.open
}

}
}
