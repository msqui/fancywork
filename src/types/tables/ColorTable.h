#ifndef __COLORTABLE_H__
#define __COLORTABLE_H__

#include <set>
#include <string>

#include "types/color/Color.h"

namespace fw {
namespace types {
namespace tables {
/**
 * Represents picture color space
**/
class ColorTable
{
public:
  typedef fw::types::color::Color ColorT;
  typedef std::set<ColorT> ColorSetT;
  
  ColorTable();
  
  void add(const ColorT& color);
  void clear();
  
  ColorT find(const ColorT& color);
  
  size_t size() const;
  bool contains(const ColorT& color) const;
  
  ColorSetT get() const;
  std::string str() const;
  
private:
  ColorSetT _table;
};

}}}

#endif /* end of include guard: __COLORTABLE_H__ */
