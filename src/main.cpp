#include <cstdlib>
#include <iostream>

#include <Magick++.h>

#include "util/Messages.h"

using namespace fw;

int main (int argc, char const* argv[])
{
	if (argc < 2)
	{
		util::Messages::usage();
		return EXIT_FAILURE;
	}
	
	std::string filename = argv[1];
	try
	{
		Magick::Image myImg;
		myImg.read(filename);
		std::cout << filename << " has:" << std::endl;
		std::cout << myImg.columns() << " columns" << std::endl;
		std::cout << myImg.rows() << " rows" << std::endl;
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
	
	return EXIT_SUCCESS;
}


