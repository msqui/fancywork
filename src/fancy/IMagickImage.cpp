#include "IMagickImage.h"

namespace fw {
namespace fancy {

IMagickImage::IMagickImage(const std::string& filename) :
	Image(filename)
{
	open(_filename);
}

IMagickImage* IMagickImage::create(const std::string& filename)
{
	return new IMagickImage(filename);
}

void IMagickImage::open(const std::string& filename)
{
	_img.read(filename);
}

unsigned int IMagickImage::width() const
{
	return _img.columns();
}

unsigned int IMagickImage::height() const
{
	return _img.rows();
}

}}

