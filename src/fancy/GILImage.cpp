#include "GILImage.h"

#include <boost/gil/extension/io/jpeg_io.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>
#include <boost/gil/extension/numeric/resample.hpp>

#include "types/Color.h"
#include "types/ColorTable.h"

namespace fw {
namespace fancy {

GILImage::GILImage(const std::string& filename) :
  Image(filename)
{
  open(filename);
}

GILImage::GILImagePtrT
GILImage::create(const std::string& filename)
{
  return GILImagePtrT(new GILImage(filename));
}

void GILImage::open(const std::string& filename)
{
  bg::jpeg_read_image(filename, _img);
  
  _width = _img.width();
  _height = _img.height();
}

void GILImage::process(size_t num_colors,
                        size_t square_side,
                        const std::string& suffix)
{
  // =================
  // = Process image =
  // =================
  
  // reduce image
  size_t new_width = width() / square_side;
  size_t new_height = height() / square_side;
  
  bg::rgb8_image_t new_img(new_width, new_height);
  // bg::resize_view(bg::const_view(_img), bg::view(new_img), bg::nearest_neighbor_sampler());
  bg::resize_view(bg::const_view(_img), bg::view(new_img), bg::bilinear_sampler());


  // reduce color table
  fw::types::ColorTable color_table;
  fw::types::Color color;
  bg::rgb8_view_t new_img_view = bg::view(new_img);
  for(size_t y = 0; y < new_height; ++y)
  {
    bg::rgb8_view_t::x_iterator x_it = new_img_view.row_begin(y);
    for(size_t x = 0; x < new_width; ++x)
    {
      // std::cout << x_it[x].red << "\t";
    }
    std::cout << std::endl;
  }
  
  // write image
  bg::jpeg_write_view("out-test.jpg", bg::const_view(new_img));
  
  // // analyze image colors
  // fw::types::ColorTable color_table;
  // Magick::Color color;
  // for(size_t y = 0; y < new_height; ++y)
  // {
  //  for(size_t x = 0; x < new_width; ++x)
  //  {
  //    color = new_img.pixelColor(x,y);
  //    color_table.add(fw::types::MagickColor(color), fw::types::MagickColor(color));
  //  }
  // }
  // 
  // // process color table
  // color_table.reduce(num_colors);
  // 
  // // =======================
  // // = Save modified image =
  // // =======================
  // for(size_t y = 0; y < new_height; ++y)
  // {
  //  for(size_t x = 0; x < new_width; ++x)
  //  {
  //    new_img.pixelColor(x, y, fw::types::MagickColor(color_table.find(fw::types::MagickColor(new_img.pixelColor(x, y)))));
  //  }
  // }
  // 
  // new_img.magick("PNG");
  // new_img.write(_filename + "_" + suffix + "_2." + new_img.magick());
}

}}
