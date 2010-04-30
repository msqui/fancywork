#ifndef __COLORTABLE_H__
#define __COLORTABLE_H__

#include <map>
#include <set>
#include <string>

#include "Color.h"

namespace fw {
namespace types {

class ColorTable
{
public:
	typedef std::map<Color, Color> ColorColT;
	typedef std::pair<Color, Color> ColorPairT;
	typedef std::set<Color> ColorSetT;
	
	ColorTable();
	
	void add(const Color& color, const Color& color);
	void reduce(unsigned int n);
	void clear();
	
	Color find(const Color& color);
	
	unsigned int size() const;
	bool contains(const Color& color) const;
	
	ColorSetT used_colors() const;

	std::string str() const;
	
private:
	ColorColT _table;
	ColorSetT _used_colors;
};

}}

#endif /* end of include guard: __COLORTABLE_H__ */
