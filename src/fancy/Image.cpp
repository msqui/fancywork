#include "Image.h"

namespace fw {
namespace fancy {

Image::Image(const std::string& filename) :
	_filename(filename)
{}

std::string Image::filename() const
{
	return _filename;
}

}}
