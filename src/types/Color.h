#ifndef __COLOR_H__
#define __COLOR_H__

#include <iostream>
#include <string>

namespace fw {
namespace types {

class Color
{
public:
	Color();
	Color(unsigned int r, unsigned int g, unsigned int b);
	
	std::ostream& to_stream(std::ostream& ostr) const;
	std::string str() const;
	
	friend bool operator< (const Color& c1, const Color& c2);
	friend std::ostream& operator<< (std::ostream& ostr, const Color& color);

protected:
	unsigned int _r;
	unsigned int _g;
	unsigned int _b;
};

}}

#endif /* end of include guard: __COLOR_H__ */
