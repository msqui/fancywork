#ifndef __IMAGICKIMAGE_H__
#define __IMAGICKIMAGE_H__

#include "Image.h"

#include <string>
#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>

#include <Magick++.h>

#include "types/Color.h"

namespace fw {
namespace fancy {

class IMagickImage : public Image, private boost::noncopyable
{
public:
	typedef boost::shared_ptr<IMagickImage> IMagickImagePtrT;
	
	static IMagickImagePtrT create(const std::string& filename);
	
	void open(const std::string& filename);
	
	unsigned int width() const;
	unsigned int height() const;
	
	void process(unsigned int num_colors, 
								unsigned int square_side, 
								const Image::TTPtrT& ttPtr,
								const std::string& suffix);

	Magick::Color process_element(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1);
	
	// static std::vector<Magick::Color> getColors(unsigned int num_colors, unsigned int max_color);
	
private:
	IMagickImage(const std::string& filename);
	
	Magick::Image _img;
};

}}

#endif /* __IMAGICKIMAGE_H__ */

