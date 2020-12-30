#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "CircularBuffer.h"

TEST(TestBuffer, ConstructWithSize)
{
	CircularBuffer<1> buffer;
	ASSERT_EQ(buffer.getAllocatedSize(), 1);
	ASSERT_EQ(buffer.getSize(), 0);
}