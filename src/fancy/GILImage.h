#ifndef __GILIMAGE_H__
#define __GILIMAGE_H__

#include "Image.h"

#include <string>

#include <boost/shared_ptr.hpp>

#include <boost/gil/gil_all.hpp>
namespace bg = boost::gil;

namespace fw {
namespace fancy {
/**
 * boost::gil Image implementation
**/
class GILImage : public Image
{
public:
  typedef boost::shared_ptr<GILImage> GILImagePtrT;
  
  /**
   * Factory
  **/
  static GILImagePtrT create(const std::string& filename);
  
  // ============================
  // = Image ABC implementation =
  // ============================
  void open(const std::string& filename);
  
  void process(size_t num_colors,
                size_t square_side,
                const std::string& suffix);
  
private:
  // ==========
  // = Fields =
  // ==========
  bg::rgb8_image_t _img;
  
  /**
   * Construct only using Image::create factory method
  **/
  GILImage(const std::string& filename);
};

}}

#endif /* end of include guard: __GILIMAGE_H__ */
