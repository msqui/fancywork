#ifndef __SAMPLE_TEST_HPP__
#define __SAMPLE_TEST_HPP__

#include <gtest/gtest.h>

namespace {
	
class SampleTest : public ::testing::Test
{
protected:
	SampleTest() {}
};

TEST_F(SampleTest, TestOfTest)
{
	ASSERT_EQ(4, 2*2);
}

}

#endif /* end of include guard: __SAMPLE_TEST_HPP__ */
