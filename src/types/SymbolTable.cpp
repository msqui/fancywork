#include "SymbolTable.h"

#include <sstream>
#include <cmath>

namespace fw {
namespace types {

SymbolTable::SymbolTable() :
	_string("abcdefghijklmnopqrstuvwxyz")
{}

SymbolTable::SymbolTable(const std::string& string) :
	_string(string)
{}

std::string SymbolTable::operator[] (size_t n) const
{
	size_t size = _string.size();
	std::stringstream ss_res;
	if(n < size)
	{
		ss_res << _string[n];
	} else
	{
		size_t x = static_cast<size_t>(floor(n / size));
		ss_res << _string[n % size];
		for(size_t i = 0; i < x; ++i)
		{
			ss_res << ss_res;
		}
	}
	
	return ss_res.str();
}

}}
