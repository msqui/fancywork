#include "Color.h"

#include <sstream>

namespace fw {
namespace types {

Color::Color() :
	_r(0), _g(0), _b(0)
{}

Color::Color(unsigned int r, unsigned int g, unsigned int b) :
	_r(r), _g(g), _b(b)
{}

std::ostream& Color::to_stream(std::ostream& ostr) const
{
	ostr << "(" << _r << ";" << _g << ";" << _b << ")";
	return ostr;
}

std::string Color::str() const
{
	std::stringstream ss;
	(void) to_stream(ss);

	return ss.str();
}



bool operator< (const Color& c1, const Color& c2)
{
	unsigned int sum1(c1._r + c1._g + c1._b);
	unsigned int sum2(c2._r + c2._g + c2._b);
	
	return sum1 < sum2;
}

std::ostream& operator<< (std::ostream& ostr, const Color& color)
{
	(void) color.to_stream(ostr);
	return ostr;
}

}}
