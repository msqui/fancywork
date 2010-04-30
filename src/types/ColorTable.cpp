#include "ColorTable.h"

#include <sstream>

#include <cmath>

namespace fw {
namespace types {

ColorTable::ColorTable() :
	_table(),
	_used_colors()
{}

void ColorTable::add(const Color& color_s, const Color& color_t)
{
	_table.insert(ColorPairT(color_s, color_t));
}

void ColorTable::reduce(unsigned int n)
{
	if(n == 0)
	{
		clear();
		return;
	}
	
	if(n > size()) return;
	
	unsigned int size = this->size();
	unsigned int step = static_cast<unsigned int>(floor(size / n));
	unsigned int round_size = step * n;
	

	Color curr_color;
	unsigned int i = 0;
	unsigned int j = 0;
	for(ColorColT::iterator it = _table.begin();
			it != _table.end();
			++it)
	{
		if( (i == j) && (i <= round_size) )
		{
			curr_color = it->second;
			_used_colors.insert(curr_color);
			j += step;
		} else
		{
			it->second = curr_color;
		}
		
		++i;
	}
}

void ColorTable::clear()
{
	_table.clear();
}

Color ColorTable::find(const Color& color)
{
	ColorColT::const_iterator it = _table.find(color);
	if(it == _table.end()) throw;
	
	return it->second;
}

unsigned int ColorTable::size() const
{
	return _table.size();
}

bool ColorTable::contains(const Color& color) const
{
	return _table.find(color) == _table.end();
}

ColorTable::ColorSetT
ColorTable::used_colors() const
{
	return _used_colors;
}

std::string ColorTable::str() const
{
	std::stringstream ss;
	for(ColorColT::const_iterator it = _table.begin();
			it != _table.end();
			++it)
	{
		ss << it->first << " => " << it->second << "\n";
	}
	
	return ss.str();
}

}}
