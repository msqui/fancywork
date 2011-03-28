#ifndef __IMAGE_HPP__
#define __IMAGE_HPP__

#include <gtest/gtest.h>

#include "fancy/Image.h"

namespace {

class ImageTest : public ::testing::Test
{
protected:
  ImageTest() {}
};

TEST_F(ImageTest, FilenameTest)
{
  ASSERT_EQ(4, 2*2);
}

}

#endif /* end of include guard: __IMAGE_HPP__ */
