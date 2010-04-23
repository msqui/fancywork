#include "Correspondence.h"

namespace fw {
namespace types {

Correspondence::Correspondence(const Color& color, const Symbol& symbol) :
	_pair(color, symbol)
{}

Correspondence::CSPairT
Correspondence::pair() const
{
	return _pair;
}

}}
