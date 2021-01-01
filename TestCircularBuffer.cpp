#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <array>
#include <numeric>

#include "CircularBuffer.h"

using namespace ::testing;

constexpr size_t bufferSize{ 5 };

class CreateAndFillBufferCompletelyTest : public Test
{
protected:

	void SetUp() override
	{
		EXPECT_EQ(buffer.getAllocatedSize(), bufferSize);
		EXPECT_EQ(buffer.getSize(), 0);

		std::iota(vals.begin(), vals.end(), -3);

		for (size_t i = 0; i < vals.size(); i++)
		{
			buffer.add(vals[i]);
			EXPECT_EQ(buffer.getSize(), i + 1);
		}

		EXPECT_EQ(buffer.getAllocatedSize(), bufferSize);
		EXPECT_EQ(buffer.getSize(), bufferSize);
	}

	void TearDown() override
	{
		EXPECT_EQ(buffer.getAllocatedSize(), bufferSize);
	}

	CircularBuffer<bufferSize> buffer;
	std::array<double, bufferSize> vals;
};

TEST_F(CreateAndFillBufferCompletelyTest, RetrieveElementsInOrderOfAdding)
{
	for (auto &v : vals)
		ASSERT_EQ(buffer.pop(), v);
}

TEST_F(CreateAndFillBufferCompletelyTest, AddTooManyElements_shouldNotFail)
{
	ASSERT_NO_THROW(buffer.add(0));
}

TEST_F(CreateAndFillBufferCompletelyTest, AddTooManyElements_shouldOverwriteOldestAndReturnLast)
{
	buffer.add(0);

	for (size_t i = 1; i < vals.size(); i++)
		ASSERT_EQ(buffer.pop(), vals[i]);

	ASSERT_EQ(buffer.pop(), 0);
}