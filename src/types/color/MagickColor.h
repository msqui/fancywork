#ifndef __MAGICKCOLOR_H__
#define __MAGICKCOLOR_H__

#include "Color.h"

#include <Magick++.h>

namespace fw {
namespace types {
namespace color {

class MagickColor : public Color
{
public:
  MagickColor();
  MagickColor(const Color& color);
  MagickColor(const Magick::Color& color);
  
  operator Magick::Color ();
};

}}}

#endif /* end of include guard: __MAGICKCOLOR_H__ */
