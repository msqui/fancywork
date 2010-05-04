#include "ColorTable.h"

#include <sstream>

namespace fw {
namespace types {
namespace tables {

ColorTable::ColorTable() :
	_table()
{}

void ColorTable::add(const fw::types::color::Color& color)
{
	_table.insert(color);
}

void ColorTable::clear()
{
	_table.clear();
}

fw::types::color::Color 
ColorTable::find(const fw::types::color::Color& color)
{
	ColorSetT::const_iterator it = _table.find(color);
	if(it == _table.end()) throw;
	
	return *it;
}

unsigned int ColorTable::size() const
{
	return _table.size();
}

bool ColorTable::contains(const fw::types::color::Color& color) const
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
	ColorSetT::const_iterator it = _table.begin();
	for(; it != _table.end(); ++it)
	{
		ss << *it << "\n";
	}
	
	return ss.str();
}

}}}
