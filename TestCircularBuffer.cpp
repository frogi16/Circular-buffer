#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "CircularBuffer.h"

TEST(TestBuffer, ConstructWithSize)
{
	CircularBuffer<1> buffer;
	ASSERT_EQ(buffer.getAllocatedSize(), 1);
	ASSERT_EQ(buffer.getSize(), 0);
}

TEST(TestBuffer, AddElement)
{
	CircularBuffer<3> buffer;
	ASSERT_EQ(buffer.getSize(), 0);
	buffer.add(3.14);
	ASSERT_EQ(buffer.getSize(), 1);
}