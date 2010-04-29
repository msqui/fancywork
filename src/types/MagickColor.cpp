#include "MagickColor.h"

namespace fw {
namespace types {

MagickColor::MagickColor() :
	Color()
{}

MagickColor::MagickColor(const Color& color) :
	Color(color)
{}

MagickColor::MagickColor(const Magick::Color& color) :
	Color(color.redQuantum(), color.greenQuantum(), color.blueQuantum())
{}

MagickColor::operator Magick::Color ()
{
	return Magick::Color(_r, _g, _b, 0);
}

}}