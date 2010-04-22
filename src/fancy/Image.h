#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <string>
#include <boost/shared_ptr.hpp>

namespace fw {
namespace fancy {

class Image
{
public:
	typedef boost::shared_ptr<Image> ImagePtrT;
	
	template <typename CreatorT>
	static ImagePtrT create(const std::string& filename)
	{
		return CreatorT::create(filename);
	}

	std::string filename() const;
		
	virtual void open(const std::string& filename) = 0;

	virtual unsigned int width() const = 0;
	virtual unsigned int height() const = 0;
	
protected:
	Image (const std::string& filename);
	
	std::string _filename;
};

}}


#endif /* __IMAGE_H__ */

