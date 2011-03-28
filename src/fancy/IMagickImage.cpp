#include "IMagickImage.h"

#include <cmath>
#include <stdexcept>

#include "types/common/NullPtr.h"
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
                              size_t square_side,
                              const std::string& suffix)
{
  // =================
  // = Process image =
  // =================
  
  // reduce image
  size_t mod_width = width() / square_side;
  size_t mod_height = height() / square_side;
  Magick::Image new_img(_img);
  
  new_img.zoom(Magick::Geometry(mod_width, mod_height));
  size_t new_width = new_img.columns();
  size_t new_height = new_img.rows();
  
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
  for(size_t y = 0; y < new_height; ++y)
  {
    for(size_t x = 0; x < new_width; ++x)
    {
      color = new_img.pixelColor(x,y);
      color_table.add(fwt::color::MagickColor(color));
    }
  }
  
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
  for(size_t y = 0; y < new_height; ++y)
  {
    for(size_t x = 0; x < new_width; ++x)
    {
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


/*
void IMagickImage::process(size_t num_colors, 
                            size_t square_side, 
                            const Image::TTPtrT& ttPtr,
                            const std::string& suffix)
{
  size_t width = this->width();
  size_t height = this->height();
  
  size_t h_step = square_side;
  size_t v_step = square_side;
  
  if( (h_step == 0) || (v_step == 0) )
  {
    throw std::invalid_argument("Step must be greater than 0");
  }

  size_t h_steps_cnt = static_cast<size_t>(floor(width / h_step));
  size_t v_steps_cnt = static_cast<size_t>(floor(height / v_step));
  
  size_t round_width = h_step * h_steps_cnt;
  size_t round_height = v_step * v_steps_cnt;
  
  // Magick::Image new_image(Magick::Geometry(h_steps_cnt, v_steps_cnt), 
  //                        Magick::Color("white"));  
                          
  Magick::Image new_image(Magick::Geometry(round_width, round_height), 
                          Magick::Color("white"));
  
  Magick::Color new_color;
  fwt::tables::ColorTable color_table;
  
  for(size_t y = 0; y < v_steps_cnt; ++y)
  {
    for(size_t x = 0; x < h_steps_cnt; ++x)
    {
      new_color = process_element(x * h_step, y * v_step, (x + 1) * h_step, (y + 1) * v_step);
      // new_image.pixelColor(x, y, new_color);
      color_table.add(fwt::MagickColor(new_color), 
                      fwt::MagickColor(new_color));
      
      for(size_t yy = y * v_step; yy < (y + 1) * v_step; ++yy)
      {
        for(size_t xx = x * h_step; xx < (x + 1) * h_step; ++xx)
        {
          new_image.pixelColor(xx, yy, new_color);
        }
      }
      
    }
  }
  
  color_table.reduce(num_colors);
  std::cout << "num colors: " << color_table.size() << std::endl;
  
  // std::cout << "Table: " << color_table.str() << std::endl;
  
  
  // =======================
  // = Save modified image =
  // =======================
  for(size_t y = 0; y < new_image.rows(); ++y)
  {
    for(size_t x = 0; x < new_image.columns(); ++x)
    {
      new_image.pixelColor(x, y, fwt::MagickColor(color_table.find(fwt::MagickColor(new_image.pixelColor(x, y)))));
    }
  }
  
  new_image.write(_filename + "_" + suffix + "_1." + _img.magick());
  
  
  // =============
  // = Save text =
  // =============
  
  // std::string letters = " abcdefghijklmnopqrstuvwxyz";
  // size_t curr_letter_ind = 0;
  // std::string curr_letter;
  // std::map<fwt::MagickColor, std::string> color_letter;
  // std::map<fwt::MagickColor, std::string>::const_iterator it;
  
  fwt::ColorSymbolTable color_letter(color_table.used_colors());
  fwt::MagickColor curr_color;
  
  std::string line = "";
  for(size_t y = 0; y < v_steps_cnt; ++y)
  {
    for(size_t x = 0; x < h_steps_cnt; ++x)
    {
      // curr_color = new_image.pixelColor(x * h_step, y * v_step);
      // it = color_letter.find(curr_color);
      // if(it != color_letter.end())
      // {
      //  line += it->second;
      // }
      curr_color = new_image.pixelColor(x * h_step, y * v_step);
      line += color_letter.get(curr_color);
      line += " ";
    }
    line += "\n";
  }
  
  std::ofstream fs;
  fs.open("test.file.txt");
  fs << line << "\n";
  fs << "Legend:\n" << color_letter.legend();
  fs.close();
  
  
  // ===================
  // = Legend in image =
  // ===================
  Magick::Image img_legend(Magick::Geometry(300, color_letter.size() * 220),
                            Magick::Color("white"));
  std::list<Magick::Drawable> objects_to_draw;
  objects_to_draw.push_back(Magick::DrawableStrokeColor(Magick::Color("black")));
  objects_to_draw.push_back(Magick::DrawableFont("-*-helvetica-medium-r-normal-*-*-300-*-*-*-*-iso8859-1"));
  fwt::ColorSymbolTable::ColorSymbolColT::const_iterator it = color_letter.table().begin();
  size_t i = 0;
  for(; it != color_letter.table().end(); ++it, ++i)
  {
    objects_to_draw.push_back(Magick::DrawableFillColor(fwt::MagickColor(it->first)));
    objects_to_draw.push_back(Magick::DrawableRectangle(10, i * 200 + 10, 280, (i + 1) * 200));
    objects_to_draw.push_back(Magick::DrawableFillColor(Magick::Color("black")));
    objects_to_draw.push_back(Magick::DrawableText(130, i * 200 + 100 + 10, it->second));
  }
  img_legend.draw(objects_to_draw);
  img_legend.magick("JPEG");
  img_legend.write("legend.jpeg");
}
*/

Magick::Color IMagickImage::process_element(size_t x0, size_t y0, 
                                                size_t x1, size_t y1)
{
  
  unsigned long r = 0, 
                g = 0, 
                b = 0;
                
  unsigned long total = 0;
  
  Magick::Color color;
  
  for(size_t y = y0; y < y1; ++y)
  {
    for(size_t x = x0; x < x1; ++x)
    {
      color = _img.pixelColor(x, y);
      r += color.redQuantum();
      g += color.greenQuantum();
      b += color.blueQuantum();
      
      ++total;
    }
  }
  
  r = static_cast<size_t>(floor(r / total));
  g = static_cast<size_t>(floor(g / total));
  b = static_cast<size_t>(floor(b / total));
  
  return Magick::Color(r, g, b, 0);
}


// std::vector<Magick::Color> IMagickImage::getColors(size_t num_colors, size_t max_color)
// {
//  
//  // fwt::Color start_color(0, 0, 0);
//  // fwt::Color end_color(max_color, max_color, max_color);
//  // 
//  // fwt::ColorRange range(start_color, end_color);
//  // 
//  // std::vector<fwt::Color> colorsVec(start_color);
//  // for(size_t i = 0; i <= num_colors - 2; ++i)
//  // {
//  //  colorsVec.push_back(range.middle());
//  // }
//  // colorsVec.push_back(end_color);
//  
//  
//  
//  
//  // size_t color_line = max_color * pow(10,2) + max_color * pow(10,1) + max_color;
//  // if(num_colors >= color_line)
//  // {
//  //  return std::vector<Magick::Color>();
//  // }
//  // 
//  // std::vector<Magick::Color> colorsVec;
//  // size_t step = static_cast<size_t>(floor(color_line / num_colors));
//  // 
//  // for(size_t i = 0; i <= step * num_colors; ++i)
//  // {
//  //  i / max_color;
//  //  colorsVec.push_back(Magick::Color(i, i, i))
//  // }
// }


}}

