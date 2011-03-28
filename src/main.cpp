#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include "util/Messages.h"
#include "fancy/IMagickImage.h"
#include "fancy/GILImage.h"

#include "types/common/NullPtr.h"

using namespace fw;

// Usage help message
void usage(const std::string& message, const po::options_description& desc);

// Used types
typedef std::string FilenameT;
typedef std::vector<FilenameT> FilenamesVecT;

/**
 * Functor to process each file in list
**/
struct ProcessFile : public std::unary_function<FilenameT, void> {
  ProcessFile(size_t num_colors, size_t square_side) :
    _num_colors(num_colors),
    _square_side(square_side)
  {}
  
  void operator() (FilenameT filename) const {
    fancy::Image::ImagePtrT myImg = 
        fancy::Image::create<fancy::IMagickImage>(filename);
        
    std::cout << myImg->filename() << " has:" << std::endl;
    std::cout << myImg->width() << " columns" << std::endl;
    std::cout << myImg->height() << " rows" << std::endl;
    
    myImg->process(_num_colors, _square_side);
    
    // myImg = fancy::Image::create<fancy::GILImage>(filename);
    // myImg->process(num_colors, square_side, tt);
  }
  
private:
  size_t _num_colors;
  size_t _square_side;
};

int main (int argc, char* argv[])
{
  // ==================
  // = Config options =
  // ==================
  FilenameT tt_filename;
  FilenamesVecT input_files;
  
  size_t num_colors;
  size_t square_side;
  
  // ===========================
  // = Command line processing =
  // ===========================
  try {
    po::options_description main_desc("Mandatory params");
    main_desc.add_options()
      ("input-file,i", po::value<FilenamesVecT>(&input_files), "input image file")
    ;

    po::options_description opt_desc("Optional params");
    opt_desc.add_options()
      ("side,s", po::value<size_t>(&square_side)->default_value(5), "fancy square side")
      ("colors,c", po::value<size_t>(&num_colors)->default_value(16), "number of colors")
    ;
      
    po::options_description help_desc("Help");
    help_desc.add_options()
      ("help,h", "produce help message")
      ("version,v", "display program version")
    ;
      
    po::options_description desc("");
    desc.add(main_desc).add(opt_desc).add(help_desc);
        
    po::positional_options_description p;
    p.add("input-file", -1);
    
    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).
      options(desc).positional(p).run(), vm);
    po::notify(vm);
  
    if (vm.count("help")) {
      usage(util::Messages::usage, desc);
      return EXIT_FAILURE;
    }
    if (vm.count("version")) {
      std::cout << util::Messages::version << std::endl;
      return EXIT_FAILURE;
    }
  
    if (!vm.count("input-file")) {
      std::cout << util::Messages::no_files_to_process << std::endl;
      return EXIT_FAILURE;
    }
  }
  catch (std::exception& exc) {
    std::cerr << "Error: " << exc.what() << std::endl;
    return EXIT_FAILURE;
  }
  catch (...) {
    std::cerr << "Unknown exception!" << std::endl;
    return EXIT_FAILURE;
  }
  
  
  // =====================
  // = Images processing =
  // =====================
  try {
    fancy::Image::ImagePtrT myImg;
    ProcessFile process_file(num_colors, square_side);
    std::for_each(input_files.begin(), input_files.end(), process_file);
  }
  catch (Magick::Error& e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  catch (...) {
    std::cout << "Unhandled exception!" << std::endl;
    return EXIT_FAILURE;
  }
    
  return EXIT_SUCCESS;
}


// ======================
// = Usage help message =
// ======================
void usage(const std::string& message, const po::options_description& desc)
{
  std::cout << std::endl
            << message 
            << std::endl;
  
  std::cout << desc << std::endl;
}
