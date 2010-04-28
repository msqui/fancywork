#ifndef __CORRESPONDENCE_H__
#define __CORRESPONDENCE_H__

#include <utility>

#include "Color.h"
#include "Symbol.h"

namespace fw {
namespace types {

class Correspondence
{
public:
	typedef std::pair<Color, Symbol> CSPairT;

	Correspondence(const Color& color, const Symbol& symbol);
	Correspondence(const std::string& color, const std::string& symbol);
	
	CSPairT pair() const;
	
protected:
	Correspondence();
	
	CSPairT _pair;
};

}}

#endif /* end of include guard: __CORRESPONDENCE_H__ */
