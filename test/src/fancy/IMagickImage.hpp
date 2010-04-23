#ifndef __IMAGICKIMAGE_HPP__
#define __IMAGICKIMAGE_HPP__

#include <gtest/gtest.h>

#include "src/fancy/IMagickImage.h"

namespace {

using namespace fw;

class IMagickImageTest : public ::testing::Test
{
protected:
	IMagickImageTest() {}
};

TEST_F(IMagickImageTest, OpenTest)
{
	ASSERT_EQ(1,1);
}

}

#endif /* end of include guard: __IMAGICKIMAGE_HPP__ */
