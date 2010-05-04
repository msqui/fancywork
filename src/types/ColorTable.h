#ifndef __COLORTABLE_H__
#define __COLORTABLE_H__

#include <set>
#include <string>

#include "Color.h"

namespace fw {
namespace types {

class ColorTable
{
public:
	typedef std::set<Color> ColorSetT;
	
	ColorTable();
	
	void add(const Color& color);
	void clear();
	
	Color find(const Color& color);
	
	unsigned int size() const;
	bool contains(const Color& color) const;
	
	ColorSetT get() const;
	std::string str() const;
	
private:
	ColorSetT _table;
};

}}

#endif /* end of include guard: __COLORTABLE_H__ */
