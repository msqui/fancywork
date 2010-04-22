#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <string>

namespace fw {
namespace fancy {

class Image
{
public:

	std::string filename() const;
		
	virtual void open(const std::string& filename) = 0;

	virtual unsigned int width() const = 0;
	virtual unsigned int height() const = 0;
	
protected:
	Image (const std::string& filename);
	
	std::string _filename;

private:
	Image ();
	Image (const Image&);
	void operator= (const Image&);
};

}}


#endif /* __IMAGE_H__ */

