#ifndef __SYMBOLTABLE_HPP__
#define __SYMBOLTABLE_HPP__

#include <vector>
#include <string>

#include "types/Symbol.h"

namespace fwt = fw::types;

namespace fw {
namespace types {
namespace tables {
/**
 * Represents symbol alphabet
**/
class SymbolTable
{
public: 
  typedef std::vector<fwt::Symbol> SymbolCollT;
  
  SymbolTable();
  SymbolTable(const std::string& string);
  
  void add(const std::string& string);
  
  std::string operator[] (size_t n) const;
  
private:
  SymbolCollT _table;
  
};

}}}

#endif /* end of include guard: __SYMBOLTABLE_HPP__ */
