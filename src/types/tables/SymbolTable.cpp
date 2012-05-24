#include "SymbolTable.h"

#include <sstream>
#include <cmath>

namespace fw {
namespace types {
namespace tables {

SymbolTable::SymbolTable() :
  _table()
{
  add("abcdefghijklmnopqrstuvwxyz");
}

SymbolTable::SymbolTable(const std::string& string) :
  _table()
{
  add(string);
}

void SymbolTable::add(const std::string& string)
{
  char chr[] = {' ', '\0'};
  std::string::const_iterator it = string.begin();
  for (; it != string.end(); ++it) {
    chr[0] = *it;
    _table.push_back(fwt::Symbol(chr));
  }
}

// TODO return Symbol instead of string
std::string SymbolTable::operator[] (size_t n) const
{
  size_t size = _table.size();
  std::stringstream ss_res;
  if (n < size) {
    ss_res << _table[n];
  } else {
    size_t x = static_cast<size_t>(floor(n / size));
    fwt::Symbol c = _table[n % size];
    for (size_t i = 0; i <= x; ++i) {
      ss_res << c;
    }
  }
  
  return ss_res.str();
}

}}}
