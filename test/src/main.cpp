#include <gtest/gtest.h>

#include "test/src/util/Messages.hpp"
#include "test/src/fancy/Image.hpp"
#include "test/src/fancy/IMagickImage.hpp"

int main (int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	
	return RUN_ALL_TESTS();
}