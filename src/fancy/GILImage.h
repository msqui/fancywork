#ifndef __GILIMAGE_H__
#define __GILIMAGE_H__

#include "Image.h"

#include <string>
#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>

#include <boost/gil/gil_all.hpp>
namespace bg = boost::gil;

namespace fw {
namespace fancy {

class GILImage : public Image, private boost::noncopyable
{
public:
	typedef boost::shared_ptr<GILImage> GILImagePtrT;
	
	static GILImagePtrT create(const std::string& filename);
	
	void open(const std::string& filename);
	
	void process(unsigned int num_colors,
								unsigned int square_side,
								const Image::TTPtrT& ttPtr,
								const std::string& suffix);
								
	void process_2(size_t num_colors,
									size_t square_side,
									const Image::TTPtrT& ttPtr,
									const std::string& suffix);
								
private:
	GILImage(const std::string& filename);
	
	bg::rgb8_image_t _img;
};

}}

#endif /* end of include guard: __GILIMAGE_H__ */
