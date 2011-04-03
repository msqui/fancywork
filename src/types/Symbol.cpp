#include "Symbol.h"

namespace fw {
namespace types {

Symbol::Symbol() :
  _symbol("")
{}

Symbol::Symbol(const std::string& s) :
  _symbol(s)
{}

void Symbol::add(const Symbol& symbol)
{
  _symbol += symbol.str();
}

std::string Symbol::str() const
{
  return _symbol;
}

std::ostream& operator<< (std::ostream& ostr, const Symbol& symbol)
{
  ostr << symbol._symbol;
  return ostr;
}

bool operator== (const Symbol& s1, const Symbol& s2)
{
  return s1._symbol == s2._symbol;
}

// ====================
// = Undefined symbol =
// ====================
NoSymbol::NoSymbol() :
  Symbol("NONE")
{}

}}
