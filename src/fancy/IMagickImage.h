#ifndef __IMAGICKIMAGE_H__
#define __IMAGICKIMAGE_H__

#include "Image.h"

#include <string>
#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>

#include <Magick++.h>

namespace fw {
namespace fancy {

class IMagickImage : public Image, private boost::noncopyable
{
public:
  typedef boost::shared_ptr<IMagickImage> IMagickImagePtrT;
  
  static IMagickImagePtrT create(const std::string& filename);
  
  void open(const std::string& filename);
  
  void process(size_t num_colors, 
                size_t square_side, 
                const std::string& suffix);
                  
  Magick::Color process_element(size_t x0, size_t y0, size_t x1, size_t y1);
  
  // static std::vector<Magick::Color> getColors(size_t num_colors, size_t max_color);
  
private:
  IMagickImage(const std::string& filename);
  
  Magick::Image _img;
};

}}

#endif /* __IMAGICKIMAGE_H__ */

