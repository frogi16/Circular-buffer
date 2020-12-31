#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <array>
#include <numeric>

#include "CircularBuffer.h"

TEST(TestBuffer, ConstructWithSize)
{
	CircularBuffer<1> buffer;
	ASSERT_EQ(buffer.getAllocatedSize(), 1);
	ASSERT_EQ(buffer.getSize(), 0);
}

TEST(TestBuffer, AddAndPopElement)
{
	CircularBuffer<3> buffer;
	ASSERT_EQ(buffer.getSize(), 0);
	ASSERT_EQ(buffer.getAllocatedSize(), 3);

	buffer.add(3.14);
	ASSERT_EQ(buffer.getSize(), 1);
	ASSERT_EQ(buffer.getAllocatedSize(), 3);

	ASSERT_DOUBLE_EQ(buffer.pop(), 3.14);
	ASSERT_EQ(buffer.getSize(), 0);
	ASSERT_EQ(buffer.getAllocatedSize(), 3);
}

TEST(TestBuffer, RetrieveElementsInOrderOfAdding)
{
	CircularBuffer<5> buffer;
	std::array<double, 5> vals;
	std::iota(vals.begin(), vals.end(), -3);

	for (auto &v : vals)
		buffer.add(v);

	for (auto &v : vals)
		ASSERT_EQ(buffer.pop(), v);
}

TEST(TestBuffer, AddTooManyElements_shouldNotFail)
{
	CircularBuffer<5> buffer;
	std::array<double, 5> vals;
	std::iota(vals.begin(), vals.end(), -3);

	for (auto &v : vals)
		buffer.add(v);

	ASSERT_NO_THROW(buffer.add(0));
}