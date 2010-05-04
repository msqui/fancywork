#include "IMagickImage.h"

#include <cmath>
#include <stdexcept>

#include "types/common/NullPtr.h"
#include "types/Color.h"
#include "types/MagickColor.h"
#include "types/ColorTable.h"
#include "types/ColorSymbolTable.h"

#include <map>
#include <fstream>

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
	fw::types::ColorTable color_table;
	Magick::Color color;
	// new_img.reduceNoise();
	new_img.quantizeColors(num_colors);
	new_img.quantize();
	for(size_t y = 0; y < new_height; ++y)
	{
		for(size_t x = 0; x < new_width; ++x)
		{
			color = new_img.pixelColor(x,y);
			color_table.add(fw::types::MagickColor(color));
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
	fw::types::ColorSymbolTable color_letter(color_table.get());
	std::string line = "";
	for(unsigned int y = 0; y < new_height; ++y)
	{
		for(unsigned int x = 0; x < new_width; ++x)
		{
			line += color_letter.get(fw::types::MagickColor(new_img.pixelColor(x, y)));
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
void IMagickImage::process(unsigned int num_colors, 
														unsigned int square_side, 
														const Image::TTPtrT& ttPtr,
														const std::string& suffix)
{
	unsigned int width = this->width();
	unsigned int height = this->height();
	
	unsigned int h_step = square_side;
	unsigned int v_step = square_side;
	
	if( (h_step == 0) || (v_step == 0) )
	{
		throw std::invalid_argument("Step must be greater than 0");
	}

	unsigned int h_steps_cnt = static_cast<unsigned int>(floor(width / h_step));
	unsigned int v_steps_cnt = static_cast<unsigned int>(floor(height / v_step));
	
	unsigned int round_width = h_step * h_steps_cnt;
	unsigned int round_height = v_step * v_steps_cnt;
	
	// Magick::Image new_image(Magick::Geometry(h_steps_cnt, v_steps_cnt), 
	// 												Magick::Color("white"));	
													
	Magick::Image new_image(Magick::Geometry(round_width, round_height), 
													Magick::Color("white"));
	
	Magick::Color new_color;
	fw::types::ColorTable color_table;
	
	for(unsigned int y = 0; y < v_steps_cnt; ++y)
	{
		for(unsigned int x = 0; x < h_steps_cnt; ++x)
		{
			new_color = process_element(x * h_step, y * v_step, (x + 1) * h_step, (y + 1) * v_step);
			// new_image.pixelColor(x, y, new_color);
			color_table.add(fw::types::MagickColor(new_color), 
											fw::types::MagickColor(new_color));
			
			for(unsigned int yy = y * v_step; yy < (y + 1) * v_step; ++yy)
			{
				for(unsigned int xx = x * h_step; xx < (x + 1) * h_step; ++xx)
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
	for(unsigned int y = 0; y < new_image.rows(); ++y)
	{
		for(unsigned int x = 0; x < new_image.columns(); ++x)
		{
			new_image.pixelColor(x, y, fw::types::MagickColor(color_table.find(fw::types::MagickColor(new_image.pixelColor(x, y)))));
		}
	}
	
	new_image.write(_filename + "_" + suffix + "_1." + _img.magick());
	
	
	// =============
	// = Save text =
	// =============
	
	// std::string letters = " abcdefghijklmnopqrstuvwxyz";
	// size_t curr_letter_ind = 0;
	// std::string curr_letter;
	// std::map<fw::types::MagickColor, std::string> color_letter;
	// std::map<fw::types::MagickColor, std::string>::const_iterator it;
	
	fw::types::ColorSymbolTable color_letter(color_table.used_colors());
	fw::types::MagickColor curr_color;
	
	std::string line = "";
	for(unsigned int y = 0; y < v_steps_cnt; ++y)
	{
		for(unsigned int x = 0; x < h_steps_cnt; ++x)
		{
			// curr_color = new_image.pixelColor(x * h_step, y * v_step);
			// it = color_letter.find(curr_color);
			// if(it != color_letter.end())
			// {
			// 	line += it->second;
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
	fw::types::ColorSymbolTable::ColorSymbolColT::const_iterator it = color_letter.table().begin();
	size_t i = 0;
	for(; it != color_letter.table().end(); ++it, ++i)
	{
		objects_to_draw.push_back(Magick::DrawableFillColor(fw::types::MagickColor(it->first)));
		objects_to_draw.push_back(Magick::DrawableRectangle(10, i * 200 + 10, 280, (i + 1) * 200));
		objects_to_draw.push_back(Magick::DrawableFillColor(Magick::Color("black")));
		objects_to_draw.push_back(Magick::DrawableText(130, i * 200 + 100 + 10, it->second));
	}
	img_legend.draw(objects_to_draw);
	img_legend.magick("JPEG");
	img_legend.write("legend.jpeg");
}
*/

Magick::Color IMagickImage::process_element(unsigned int x0, unsigned int y0, 
																								unsigned int x1, unsigned int y1)
{
	
	unsigned long	r = 0, 
								g = 0, 
								b = 0;
								
	unsigned long	total = 0;
	
	Magick::Color color;
	
	for(unsigned int y = y0; y < y1; ++y)
	{
		for(unsigned int x = x0; x < x1; ++x)
		{
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


// std::vector<Magick::Color> IMagickImage::getColors(unsigned int num_colors, unsigned int max_color)
// {
// 	
// 	// fw::types::Color start_color(0, 0, 0);
// 	// fw::types::Color end_color(max_color, max_color, max_color);
// 	// 
// 	// fw::types::ColorRange range(start_color, end_color);
// 	// 
// 	// std::vector<fw::types::Color> colorsVec(start_color);
// 	// for(unsigned int i = 0; i <= num_colors - 2; ++i)
// 	// {
// 	// 	colorsVec.push_back(range.middle());
// 	// }
// 	// colorsVec.push_back(end_color);
// 	
// 	
// 	
// 	
// 	// unsigned int color_line = max_color * pow(10,2) + max_color * pow(10,1) + max_color;
// 	// if(num_colors >= color_line)
// 	// {
// 	// 	return std::vector<Magick::Color>();
// 	// }
// 	// 
// 	// std::vector<Magick::Color> colorsVec;
// 	// unsigned int step = static_cast<unsigned int>(floor(color_line / num_colors));
// 	// 
// 	// for(unsigned int i = 0; i <= step * num_colors; ++i)
// 	// {
// 	// 	i / max_color;
// 	// 	colorsVec.push_back(Magick::Color(i, i, i))
// 	// }
// }


}}

