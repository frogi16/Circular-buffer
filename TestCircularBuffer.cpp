#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "CircularBuffer.h"

TEST(TestBuffer, ConstructWithSize)
{
	CircularBuffer<1> buffer;
}