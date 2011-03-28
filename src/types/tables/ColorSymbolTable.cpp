#include "ColorSymbolTable.h"

namespace fw {
namespace types {
namespace tables {

ColorSymbolTable::ColorSymbolTable() :
  _table(),
  _symbol_table()
{}

ColorSymbolTable::ColorSymbolTable(const ColorTable::ColorSetT& color_set) :
  _table(),
  _symbol_table()
{
  ColorTable::ColorSetT::const_iterator it = color_set.begin();
  size_t i = 0;
  for(; it != color_set.end(); ++it, ++i)
  {
    _table.insert(std::make_pair(*it, _symbol_table[i]));
  }
}

std::string ColorSymbolTable::get(const fw::types::color::Color& color) const
{
  ColorSymbolColT::const_iterator it = _table.find(color);
  if(it != _table.end())
  {
    return it->second;
  }
  
  return "";
}

std::string ColorSymbolTable::legend() const
{
  std::string res = "";
  
  ColorSymbolTable::ColorSymbolColT::const_iterator it = _table.begin();
  for(; it != _table.end(); ++it)
  {
    res += it->second + " => " + it->first.str() + "\n";
  }
  
  return res;
}

size_t ColorSymbolTable::size() const
{
  return _table.size();
}

const ColorSymbolTable::ColorSymbolColT& 
ColorSymbolTable::table() const
{
  return _table;
}

}}}
