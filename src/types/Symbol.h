#ifndef __SYMBOL_H__
#define __SYMBOL_H__

#include <string>
#include <iostream>

namespace fw {
namespace types {

class Symbol
{
public:
	Symbol();
	Symbol(const std::string& s);
	// Symbol(const char chr);
	
	std::string str() const;

	friend std::ostream& operator<< (std::ostream& ostr, const Symbol& symbol);
	friend bool operator== (const Symbol& s1, const Symbol& s2);
	
private:
	std::string _symbol;
};



class NoSymbol : public Symbol
{
public:
	NoSymbol();
};

}}

#endif /* end of include guard: __SYMBOL_H__ */
