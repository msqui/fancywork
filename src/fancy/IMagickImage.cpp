#include "IMagickImage.h"

#include <cmath>
#include <stdexcept>

#include "types/color/Color.h"
#include "types/color/MagickColor.h"
#include "types/tables/ColorTable.h"
#include "types/tables/ColorSymbolTable.h"

#include <map>
#include <fstream>

namespace fwt = fw::types;

namespace fw {
namespace fancy {

IMagickImage::IMagickImage(const std::string& filename) :
  Image(filename)
{
  open(_filename);
}

IMagickImage::IMagickImagePtrT
IMagickImage::create(const std::string& filename)
{
  return IMagickImagePtrT(new IMagickImage(filename));
}

void IMagickImage::open(const std::string& filename)
{
  _img.read(filename);
  
  _width = _img.columns();
  _height = _img.rows();
}

void IMagickImage::process(size_t num_colors,
                              unsigned int square_side,
                              const std::string& suffix)
{
  // =================
  // = Process image =
  // =================
  
  // reduce image
  unsigned int mod_width = width() / square_side;
  unsigned int mod_height = height() / square_side;
  Magick::Image new_img(_img);
  
  new_img.zoom(Magick::Geometry(mod_width, mod_height));
  unsigned int new_width = new_img.columns();
  unsigned int new_height = new_img.rows();
  
  // new_img.quantize();
  
  // ==================
  // = Process colors =
  // ==================
  // analyze image colors
  fwt::tables::ColorTable color_table;
  Magick::Color color;
  // new_img.reduceNoise();
  new_img.quantizeColors(num_colors);
  new_img.quantize();
  for (unsigned int y = 0; y < new_height; ++y) {
    for (unsigned int x = 0; x < new_width; ++x) {
      color = new_img.pixelColor(x,y);
      color_table.add(fwt::color::MagickColor(color));
    }
  }
  
  #ifdef DEBUG
    std::cout << color_table.str() << std::endl;
  #endif
  
  // =======================
  // = Save modified image =
  // =======================
  new_img.magick("PNG");
  new_img.write(_filename + "_" + suffix + "." + new_img.magick());
  
  // =============
  // = Save text =
  // =============
  fwt::tables::ColorSymbolTable color_letter(color_table.get());
  std::string line = "";
  for (unsigned int y = 0; y < new_height; ++y) {
    for (unsigned int x = 0; x < new_width; ++x) {
      line += color_letter.get(fwt::color::MagickColor(new_img.pixelColor(x, y)));
      line += " ";
    }
    line += "\n";
  }
  
  std::ofstream fs;
  fs.open("test.file.txt");
  fs << line << "\n";
  fs << "Legend:\n" << color_letter.legend();
  fs.close();
}

Magick::Color
IMagickImage::process_element(unsigned int x0, unsigned int y0,
                              unsigned int x1, unsigned int y1)
{
  
  unsigned int r = 0, 
                g = 0, 
                b = 0;
                
  unsigned int total = 0;
  
  Magick::Color color;
  
  for (unsigned int y = y0; y < y1; ++y) {
    for (unsigned int x = x0; x < x1; ++x) {
      color = _img.pixelColor(x, y);
      r += color.redQuantum();
      g += color.greenQuantum();
      b += color.blueQuantum();
      
      ++total;
    }
  }
  
  r = static_cast<unsigned int>(floor(r / total));
  g = static_cast<unsigned int>(floor(g / total));
  b = static_cast<unsigned int>(floor(b / total));
  
  return Magick::Color(r, g, b, 0);
}

}}

