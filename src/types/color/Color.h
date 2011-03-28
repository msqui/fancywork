#ifndef __COLOR_H__
#define __COLOR_H__

#include <iostream>
#include <string>

namespace fw {
namespace types {
namespace color {

class Color
{
public:
  Color();
  Color(size_t r, size_t g, size_t b);
  Color(const std::string& str, const std::string& delimiter = ",");
  
  ~Color();
  
  std::ostream& to_stream(std::ostream& ostr) const;
  std::string str() const;
  
  friend bool operator< (const Color& c1, const Color& c2);
  friend std::ostream& operator<< (std::ostream& ostr, const Color& color);

protected:
  size_t _r;
  size_t _g;
  size_t _b;
};

}}}

#endif /* end of include guard: __COLOR_H__ */
