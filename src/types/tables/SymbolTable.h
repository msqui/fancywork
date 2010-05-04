#ifndef __SYMBOLTABLE_HPP__
#define __SYMBOLTABLE_HPP__

#include <string>

namespace fw {
namespace types {
namespace tables {

class SymbolTable
{
public:	
	SymbolTable();
	SymbolTable(const std::string& string);
	
	std::string operator[] (size_t n) const;
	
private:
	std::string _string;
};

}}}

#endif /* end of include guard: __SYMBOLTABLE_HPP__ */
