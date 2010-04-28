#ifndef __MESSAGES_HPP__
#define __MESSAGES_HPP__

#include <gtest/gtest.h>

#include "util/Messages.h"

using namespace fw;

TEST(MessagesTest, UsageWorks)
{
	ASSERT_STREQ("Usage: fancywork <filename>", 
								util::Messages::usage().c_str());
}

#endif /* end of include guard: __MESSAGES_HPP__ */
