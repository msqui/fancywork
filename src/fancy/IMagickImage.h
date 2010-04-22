#ifndef __IMAGICKIMAGE_H__
#define __IMAGICKIMAGE_H__

#include "Image.h"

#include <string>
#include <boost/utility.hpp>
#include <Magick++.h>

namespace fw {
namespace fancy {

class IMagickImage : public Image, private boost::noncopyable
{
public:
	static IMagickImage* create(const std::string& filename);
	
	void open(const std::string& filename);
	
	unsigned int width() const;
	unsigned int height() const;
	
private:
	Magick::Image _img;

	IMagickImage(const std::string& filename);
};

}}

#endif /* __IMAGICKIMAGE_H__ */

