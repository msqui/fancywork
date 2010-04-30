#ifndef __COLORSYMBOLTABLE_H__
#define __COLORSYMBOLTABLE_H__

#include <map>
#include <string>

#include "Color.h"
#include "ColorTable.h"
#include "SymbolTable.h"

namespace fw {
namespace types {

class ColorSymbolTable
{
public:
	typedef std::map<Color, std::string> ColorSymbolColT;
	
	ColorSymbolTable();
	ColorSymbolTable(const ColorTable::ColorSetT& color_set);
	
	std::string get(const Color& color) const;
	std::string legend() const;
	size_t size() const;
	
	const ColorSymbolColT& table() const;
	
private:
	ColorSymbolColT _table;
	SymbolTable _symbol_table;
};

}}

#endif /* end of include guard: __COLORSYMBOLTABLE_H__ */
