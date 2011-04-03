#ifndef __IMAGICKIMAGE_H__
#define __IMAGICKIMAGE_H__

#include "Image.h"

#include <string>

#include <boost/shared_ptr.hpp>

#include <Magick++.h>

namespace fw {
namespace fancy {
/**
 * ImageMagick Image implementation
**/
class IMagickImage : public Image
{
public:
  typedef boost::shared_ptr<IMagickImage> IMagickImagePtrT;
  
  /**
   * Factory
  **/
  static IMagickImagePtrT create(const std::string& filename);
  
  // ============================
  // = Image ABC implementation =
  // ============================
  void open(const std::string& filename);
  
  void process(size_t num_colors, 
                unsigned int square_side, 
                const std::string& suffix);
  
private:
  // ==========
  // = Fields =
  // ==========
  Magick::Image _img;
  
  /**
   * Construct only using Image::create factory method
  **/
  IMagickImage(const std::string& filename);
  
  // =================
  // = Inner methods =
  // =================
  Magick::Color process_element(unsigned int x0, unsigned int y0,
                                unsigned int x1, unsigned int y1);
  
};

}}

#endif /* __IMAGICKIMAGE_H__ */

