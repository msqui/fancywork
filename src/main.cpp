#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <iterator>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include "util/Messages.h"
#include "fancy/IMagickImage.h"

#include "config/TransformationTable.h"

using namespace fw;

void usage(const std::string& message, const po::options_description& desc);

int main (int argc, char* argv[])
{
	typedef std::string FilenameT;
	typedef std::vector<FilenameT> FilenamesVecT;
	
	FilenameT tt_filename;
	FilenamesVecT input_files;
	
	try
	{
		po::options_description desc("Options");
		desc.add_options()
			("help,h", "produce help message")
			("transformation-table,t", po::value<FilenameT>(&tt_filename), 
								"file containing the table of color-symbol correspondence")
			("input-file,i", po::value<FilenamesVecT>(&input_files), "input image file")
			;
		
		po::positional_options_description p;
		p.add("input-file", -1);
		
		po::variables_map vm;
		po::store(po::command_line_parser(argc, argv).
			options(desc).positional(p).run(), vm);
		po::notify(vm);
	
		if(vm.count("help"))
		{
			usage(util::Messages::usage, desc);
			return EXIT_FAILURE;
		}
	
		if(!vm.count("transformation-table"))
		{
			usage(util::Messages::usage, desc);
			return EXIT_FAILURE;
		}
		if (!vm.count("input-file"))
		{
			std::cout << util::Messages::no_files_to_process << std::endl;
			return EXIT_FAILURE;
		}
	}
	catch(std::exception& exc)
	{
		std::cerr << "Error: " << exc.what() << std::endl;
		return EXIT_FAILURE;
	}
	catch(...)
	{
		std::cerr << "Unknown exception!" << std::endl;
		return EXIT_FAILURE;
	}
	
	
	// Parse Transformation table
	config::TransformationTable::TransformationTablePtrT tt = 
		config::TransformationTable::create(tt_filename);

	// Process images
	try
	{
		for(FilenamesVecT::const_iterator it = input_files.begin();
				it != input_files.end();
				++it)
		{
			fancy::Image::ImagePtrT myImg = 
					fancy::Image::create<fancy::IMagickImage>(*it);
		
			std::cout << myImg->filename() << " has:" << std::endl;
			std::cout << myImg->width() << " columns" << std::endl;
			std::cout << myImg->height() << " rows" << std::endl;
		}
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

void usage(const std::string& message, const po::options_description& desc)
{
	std::cout << std::endl
						<< message 
						<< std::endl
						<< std::endl;
	
	std::cout << desc << std::endl;
}
