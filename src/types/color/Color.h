#ifndef __COLOR_H__
#define __COLOR_H__

#include <iostream>
#include <string>

namespace fw {
namespace types {
namespace color {
/**
 * Base class representing Color
**/
class Color
{
public:
  Color();
  Color(unsigned int r,
        unsigned int g,
        unsigned int b);
  Color(const std::string& str, const std::string& delimiter = ",");
  
  virtual ~Color();
  
  // ===================
  // = Utility methods =
  // ===================
  /**
   * Type Color can be converted to string
  **/
  std::string str() const;
  
  /**
   * Type Color can be a map's key
  **/
  friend bool operator< (const Color& c1, const Color& c2);
  
  /**
   * Type Color can be sent to ostream
  **/
  friend std::ostream& operator<< (std::ostream& ostr, const Color& color);

protected:
  // ==========
  // = Fields =
  // ==========
  unsigned int _r;
  unsigned int _g;
  unsigned int _b;

private:
  // =================
  // = Inner methods =
  // =================
  
  std::ostream& Color::to_stream(std::ostream& ostr) const;
};

}}}

#endif /* end of include guard: __COLOR_H__ */
