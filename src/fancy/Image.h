#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <string>
#include <boost/shared_ptr.hpp>

#include "config/TransformationTable.h"
#include "types/common/NullPtr.h"

namespace fw {
namespace fancy {

class Image
{
public:
	virtual ~Image();
	
	typedef boost::shared_ptr<Image> ImagePtrT;
	typedef fw::config::TransformationTable::TransformationTablePtrT TTPtrT;
	
	template <typename CreatorT>
	static ImagePtrT create(const std::string& filename)
	{
		return CreatorT::create(filename);
	}

	std::string filename() const;
	
	size_t width() const;
	size_t height() const;
		
	virtual void open(const std::string& filename) = 0;
	
	virtual void process(unsigned int num_colors, 
												unsigned int square_side, 
												const TTPtrT& ttPtr = nullPtr,
												const std::string& suffix = "fancy") = 0;

	virtual void process_2(size_t num_colors,
													size_t square_side,
													const Image::TTPtrT& ttPtr,
													const std::string& suffix = "fancy") = 0;

protected:
	Image (const std::string& filename);
	
	std::string _filename;
	size_t _width;
	size_t _height;
};

}}


#endif /* __IMAGE_H__ */

