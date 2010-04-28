#include <cstdlib>
#include <iostream>

#include "util/Messages.h"
#include "fancy/IMagickImage.h"

#include "config/TransformationTable.h"

using namespace fw;

int main (int argc, char const* argv[])
{
	if (argc < 2)
	{
		std::cerr << util::Messages::usage() << std::endl;
		return EXIT_FAILURE;
	}
	
	std::string filename = argv[1];
	/*
	try
	{
		fancy::Image::ImagePtrT myImg = 
					fancy::Image::create<fancy::IMagickImage>(filename);
		
		std::cout << myImg->filename() << " has:" << std::endl;
		std::cout << myImg->width() << " columns" << std::endl;
		std::cout << myImg->height() << " rows" << std::endl;
	}
	catch(Magick::Error& e)
	{
		std::cout << "Exception caught: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	catch(...)
	{
		std::cout << "Unhandled exception!" << std::endl;
		return EXIT_FAILURE;
	}
	*/
	
	config::TransformationTable::TransformationTablePtrT tt = 
		config::TransformationTable::create(argv[1]);
		
	return EXIT_SUCCESS;
}


