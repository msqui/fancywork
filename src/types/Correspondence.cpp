#include "Correspondence.h"

namespace fw {
namespace types {

Correspondence::Correspondence(const Color& color, const Symbol& symbol) :
	_pair(color, symbol)
{}

Correspondence::Correspondence(const std::string& color, const std::string& symbol)
{
	Color c(color);
	Symbol s(symbol);
	_pair = CSPairT(c, s);
}

Correspondence::CSPairT
Correspondence::pair() const
{
	return _pair;
}

}}
