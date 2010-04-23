#include "Symbol.h"

namespace fw {
namespace types {

Symbol::Symbol() :
	_symbol("")
{}

Symbol::Symbol(const std::string& s) :
	_symbol(s)
{}

std::string Symbol::str() const
{
	return _symbol;
}

std::ostream& operator<< (std::ostream& ostr, const Symbol& symbol)
{
	ostr << symbol._symbol;
	return ostr;
}

}}
