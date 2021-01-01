#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <array>
#include <numeric>
#include <random>
#include <algorithm>

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

	std::random_device rd;
	std::mt19937 gen{ rd() };

	size_t generateRandomValue(size_t min, size_t max)
	{
		std::uniform_int_distribution<> distrib(min, max);
		return distrib(gen);
	}
};

TEST_F(CreateAndFillBufferCompletelyTest, RetrieveElementsInOrderOfAdding)
{
	for (auto &v : vals)
		ASSERT_EQ(buffer.pop(), v);
}

TEST_F(CreateAndFillBufferCompletelyTest, RetrieveTooManyElements_shouldThrow)
{
	for (auto &v : vals)
		buffer.pop();

	ASSERT_THROW(buffer.pop(), RetrieveFromEmptyBufferException);
}
TEST_F(CreateAndFillBufferCompletelyTest, AddAdditionalElement_shouldNotFail)
{
	ASSERT_NO_THROW(buffer.add(0));
}

TEST_F(CreateAndFillBufferCompletelyTest, AddAdditionalElement_shouldOverwriteOldestAndReturnLast)
{
	buffer.add(0);

	for (size_t i = 1; i < vals.size(); i++)
		ASSERT_EQ(buffer.pop(), vals[i]);

	ASSERT_EQ(buffer.pop(), 0);
}

TEST_F(CreateAndFillBufferCompletelyTest, AddTooManyElements_shouldOverwriteAllNeededAndReturnInOrderOfAddition)
{
	std::vector<double> additionalElements(generateRandomValue(20, 50));
	std::generate(additionalElements.begin(), additionalElements.end(), [this](){ return generateRandomValue(0, 100) / 3.14f; });
	for (auto &v : additionalElements)
		buffer.add(v);

	EXPECT_EQ(buffer.getSize(), bufferSize);

	for (size_t i = additionalElements.size() - bufferSize; i < additionalElements.size(); i++)
		ASSERT_EQ(buffer.pop(), additionalElements[i]);

	EXPECT_EQ(buffer.getSize(), 0);
}