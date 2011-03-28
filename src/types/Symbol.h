#ifndef __SYMBOL_H__
#define __SYMBOL_H__

#include <vector>
#include <string>
#include <iostream>

namespace fw {
namespace types {

/*
  TODO add Symbol superposition
*/
class Symbol
{
public:
  typedef std::vector<Symbol> SymbolCollT;
  
  Symbol();
  Symbol(const std::string& s);
  
  void add(const Symbol& symbol);
  
  std::string str() const;
  
  friend std::ostream& operator<< (std::ostream& ostr, const Symbol& symbol);
  friend bool operator== (const Symbol& s1, const Symbol& s2);
  
private:
  // SymbolCollT _symbol;
  std::string _symbol;
};



class NoSymbol : public Symbol
{
public:
  NoSymbol();
};

}}

#endif /* end of include guard: __SYMBOL_H__ */
