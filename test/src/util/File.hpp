#ifndef __FILE_HPP__
#define __FILE_HPP__

#include <gtest/gtest.h>

#include "util/File.h"

TEST(FileTest, CorrectUninitializedBehaviour)
{
  ASSERT_NO_THROW({
    fw::util::File::FilePtrT f = fw::util::File::create();
    f->close();
  });
}

#endif /* end of include guard: __FILE_HPP__ */
