#ifndef __COLORSYMBOLTABLE_H__
#define __COLORSYMBOLTABLE_H__

#include <map>
#include <string>

#include "types/color/Color.h"
#include "ColorTable.h"
#include "SymbolTable.h"

namespace fw {
namespace types {
namespace tables {
/**
 * Maps Color to appropriate symbol
**/
class ColorSymbolTable
{
public:
  typedef fw::types::color::Color ColorT;
  typedef std::map<ColorT, std::string> ColorSymbolColT;
  
  ColorSymbolTable();
  ColorSymbolTable(const ColorTable::ColorSetT& color_set);
  
  std::string get(const ColorT& color) const;
  std::string legend() const;
  size_t size() const;
  
  const ColorSymbolColT& table() const;
  
private:
  ColorSymbolColT _table;
  SymbolTable _symbol_table;
};

}}}

#endif /* end of include guard: __COLORSYMBOLTABLE_H__ */
