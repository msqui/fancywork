#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>

namespace fw {
namespace fancy {
/**
 * Abstract base class for image processors
**/
class Image : private boost::noncopyable
{
public:
  typedef boost::shared_ptr<Image> ImagePtrT;
  
  Image (const std::string& filename);
  virtual ~Image();
  
  /**
   * Factory to create different image processors
  **/
  template <typename CreatorT>
  static ImagePtrT create(const std::string& filename)
  {
    return CreatorT::create(filename);
  }
  
  // ===========
  // = Getters =
  // ===========
  std::string filename() const;
  
  size_t width() const;
  size_t height() const;
  
  // ====================
  // = Abstract methods =
  // ====================
  virtual void open(const std::string& filename) = 0;
  
  virtual void process(size_t num_colors, 
                        size_t square_side, 
                        const std::string& suffix = "fancy") = 0;
  
protected:
  // ==========
  // = Fields =
  // ==========
  std::string _filename;
  size_t _width;
  size_t _height;
};

}}


#endif /* __IMAGE_H__ */

