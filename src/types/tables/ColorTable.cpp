#include "ColorTable.h"

#include <sstream>
#include <algorithm>

#include <boost/lambda/lambda.hpp>
using namespace boost::lambda;

namespace fw {
namespace types {
namespace tables {

ColorTable::ColorTable() :
  _table()
{}

void ColorTable::add(const ColorT& color)
{
  _table.insert(color);
}

void ColorTable::clear()
{
  _table.clear();
}

ColorTable::ColorT
ColorTable::find(const ColorT& color)
{
  ColorSetT::const_iterator it = _table.find(color);
  if (it == _table.end()) throw;
  
  return *it;
}

size_t ColorTable::size() const
{
  return _table.size();
}

bool ColorTable::contains(const ColorT& color) const
{
  return _table.find(color) == _table.end();
}

ColorTable::ColorSetT
ColorTable::get() const
{
  return _table;
}

std::string ColorTable::str() const
{
  std::stringstream ss;
  
  for_each(_table.begin(), _table.end(), ss << _1 << "\n");
  
  return ss.str();
}

}}}
