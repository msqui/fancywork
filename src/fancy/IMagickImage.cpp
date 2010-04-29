#include "IMagickImage.h"

#include <cmath>
#include <stdexcept>

#include "types/common/NullPtr.h"

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
	
	for(unsigned int y = 0; y < v_steps_cnt; ++y)
	{
		for(unsigned int x = 0; x < h_steps_cnt; ++x)
		{
			new_color = process_element(x * h_step, y * v_step, (x + 1) * h_step, (y + 1) * v_step);
			// new_image.pixelColor(x, y, new_color);
			
			for(unsigned int yy = y * v_step; yy < (y + 1) * v_step; ++yy)
			{
				for(unsigned int xx = x * h_step; xx < (x + 1) * h_step; ++xx)
				{
					new_image.pixelColor(xx, yy, new_color);
				}
			}
			
		}
	}
	
	new_image.write(_filename + suffix + "." + _img.magick());
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

}}

