#ifndef __IMAGICKIMAGE_HPP__
#define __IMAGICKIMAGE_HPP__

#include <gtest/gtest.h>

#include <Magick++.h>

#include "fancy/IMagickImage.h"

namespace {

using namespace fw::fancy;

class IMagickImageTest : public ::testing::Test
{
public:
  static const char* FILENAME;
  static const char* TYPE;
  
  static const unsigned int WIDTH;
  static const unsigned int HEIGHT;
  
  static const Magick::Color WHITE_COLOR;
  
protected:
  virtual void SetUp()
  {
    // Create sample image
    Magick::Geometry geom(IMagickImageTest::WIDTH, IMagickImageTest::HEIGHT);
    Magick::Image img(geom, IMagickImageTest::WHITE_COLOR);
    img.magick(IMagickImageTest::TYPE);
    img.write(IMagickImageTest::FILENAME);
  }
  
  virtual void TearDown()
  {
    remove(IMagickImageTest::FILENAME);
  }
};

const char* IMagickImageTest::FILENAME("test_img.jpg");
const char* IMagickImageTest::TYPE("JPEG");

const unsigned int IMagickImageTest::WIDTH(20);
const unsigned int IMagickImageTest::HEIGHT(20);

const Magick::Color IMagickImageTest::WHITE_COLOR("white");


TEST_F(IMagickImageTest, CalculatesAverageColor)
{
  IMagickImage::IMagickImagePtrT img = 
    IMagickImage::create(IMagickImageTest::FILENAME);
  
  // Magick::Color color = 
  //  img->process_element(0, 0, 
  //            IMagickImageTest::WIDTH, 
  //            IMagickImageTest::HEIGHT);
  Magick::Color color = 
    img->process_element(0, 0, 1, 2);
                            
  ASSERT_EQ(IMagickImageTest::WHITE_COLOR.redQuantum(), color.redQuantum());
  ASSERT_EQ(IMagickImageTest::WHITE_COLOR.greenQuantum(), color.greenQuantum());
  ASSERT_EQ(IMagickImageTest::WHITE_COLOR.blueQuantum(), color.blueQuantum());
}

}

#endif /* end of include guard: __IMAGICKIMAGE_HPP__ */
