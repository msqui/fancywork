#ifndef __COLORTABLE_H__
#define __COLORTABLE_H__

#include <set>
#include <string>

#include "types/color/Color.h"

namespace fw {
namespace types {
namespace tables {

class ColorTable
{
public:
  typedef std::set<fw::types::color::Color> ColorSetT;
  
  ColorTable();
  
  void add(const fw::types::color::Color& color);
  void clear();
  
  fw::types::color::Color find(const fw::types::color::Color& color);
  
  size_t size() const;
  bool contains(const fw::types::color::Color& color) const;
  
  ColorSetT get() const;
  std::string str() const;
  
private:
  ColorSetT _table;
};

}}}

#endif /* end of include guard: __COLORTABLE_H__ */
