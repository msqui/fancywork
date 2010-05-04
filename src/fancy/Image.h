#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <string>
#include <boost/shared_ptr.hpp>

#include "types/common/NullPtr.h"

namespace fw {
namespace fancy {

class Image
{
public:
	virtual ~Image();
	
	typedef boost::shared_ptr<Image> ImagePtrT;
	
	template <typename CreatorT>
	static ImagePtrT create(const std::string& filename)
	{
		return CreatorT::create(filename);
	}

	std::string filename() const;
	
	size_t width() const;
	size_t height() const;
		
	virtual void open(const std::string& filename) = 0;
	
	virtual void process(size_t num_colors, 
												size_t square_side, 
												const std::string& suffix = "fancy") = 0;

protected:
	Image (const std::string& filename);
	
	std::string _filename;
	size_t _width;
	size_t _height;
};

}}


#endif /* __IMAGE_H__ */

