#include "Image.h"

namespace fw {
namespace fancy {

Image::~Image()
{}

Image::Image(const std::string& filename) :
	_filename(filename)
{}

std::string Image::filename() const
{
	return _filename;
}

size_t Image::width() const
{
	return _width;
}

size_t Image::height() const
{
	return _height;
}

}}
