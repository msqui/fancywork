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
	
	std::string str() const;

	friend std::ostream& operator<< (std::ostream& ostr, const Symbol& symbol);
	
private:
	std::string _symbol;
};

}}

#endif /* end of include guard: __SYMBOL_H__ */
