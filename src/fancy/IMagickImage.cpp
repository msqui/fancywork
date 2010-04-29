#include "IMagickImage.h"

#include <cmath>
#include <stdexcept>

#include "types/common/NullPtr.h"
#include "types/Color.h"
#include "types/MagickColor.h"
#include "types/ColorTable.h"

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
}

unsigned int IMagickImage::width() const
{
	return _img.columns();
}

unsigned int IMagickImage::height() const
{
	return _img.rows();
}

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
	
	for(unsigned int y = 0; y < new_image.rows(); ++y)
	{
		for(unsigned int x = 0; x < new_image.columns(); ++x)
		{
			new_image.pixelColor(x, y, fw::types::MagickColor(color_table.find(fw::types::MagickColor(new_image.pixelColor(x, y)))));
		}
	}
	
	new_image.write(_filename + "_" + suffix + "." + _img.magick());
}

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

