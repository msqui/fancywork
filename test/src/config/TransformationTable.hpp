#ifndef __TRANSFORMATION_TABLE_HPP__
#define __TRANSFORMATION_TABLE_HPP__

#include <gtest/gtest.h>

#include <fstream>
#include <cstdio>

#include "config/TransformationTable.h"

using namespace fw::config;

class TransformationTableTest : public ::testing::Test
{
public:
	static const char* FILENAME;
protected:
	virtual void SetUp()
	{
		// Create sample file
		std::ofstream fs;
		fs.open(TransformationTableTest::FILENAME);
		fs << "0,0,0:b" << std::endl;
		fs << "255,255,255:w" << std::endl;
		fs << "# comment" << std::endl;
		fs << "	 # formatted comment" << std::endl;
		fs << "255,0,0:r" << std::endl;
		fs.close();
	}
	
	virtual void TearDown()
	{
		remove(TransformationTableTest::FILENAME);
	}
};

const char* TransformationTableTest::FILENAME = "test_table.tmp";



TEST_F(TransformationTableTest, ReadsGoodConfig)
{
	EXPECT_NO_THROW({
		TransformationTable::TransformationTablePtrT tt =
			TransformationTable::create(TransformationTableTest::FILENAME);
	});
}

TEST_F(TransformationTableTest, ProperlyReadsAndOutputs)
{
	TransformationTable::TransformationTablePtrT tt =
		TransformationTable::create(TransformationTableTest::FILENAME);
	EXPECT_EQ( fw::types::Symbol("b"), tt->find(fw::types::Color(0,0,0)) );
	EXPECT_EQ( fw::types::Symbol("w"), tt->find(fw::types::Color(255,255,255)) );
	EXPECT_EQ( fw::types::Symbol("r"), tt->find(fw::types::Color(255,0,0)) );
	EXPECT_EQ( fw::types::NoSymbol(), tt->find(fw::types::Color(1,1,1)) );
}

#endif /* end of include guard: __TRANSFORMATION_TABLE_HPP__ */
