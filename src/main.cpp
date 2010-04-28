#include <cstdlib>
#include <iostream>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include "util/Messages.h"
#include "fancy/IMagickImage.h"

#include "config/TransformationTable.h"

using namespace fw;

int main (int argc, char* argv[])
{
	std::string filename;
	
	po::options_description desc("Options");
	desc.add_options()
		("help,h", "produce help message")
		("filename,f", po::value<std::string>(&filename), "set file to process")
		;
	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);
	
	if(vm.count("help"))
	{
		std::cout << desc << std::endl;
		return EXIT_FAILURE;
	}
	
	if(!vm.count("filename"))
	{
		std::cout << desc << std::endl;
		return EXIT_FAILURE;
	}

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
		config::TransformationTable::create(filename);
		
	return EXIT_SUCCESS;
}


