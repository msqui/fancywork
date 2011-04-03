#include "Color.h"

#include <sstream>
#include <exception>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

namespace fw {
namespace types {
namespace color {

Color::Color() :
  _r(0), _g(0), _b(0)
{}

Color::Color(unsigned int r,
              unsigned int g,
              unsigned int b) :
  _r(r), _g(g), _b(b)
{}

Color::Color(const std::string& str, const std::string& delimiter)
{
  std::vector<std::string> rgb;
  boost::split(rgb, str, boost::is_any_of(delimiter));
  
  if (rgb.size() < 3) {
    throw std::runtime_error("wrong file format");
  }
  
  try {
    _r = boost::lexical_cast<unsigned int>(rgb[0]);
    _g = boost::lexical_cast<unsigned int>(rgb[1]);
    _b = boost::lexical_cast<unsigned int>(rgb[2]);
  }
  catch (boost::bad_lexical_cast& exc) {
    throw std::runtime_error("wrong file format");
  }
}

Color::~Color()
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

}}}
