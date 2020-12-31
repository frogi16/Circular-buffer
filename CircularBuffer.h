#pragma once

template<size_t allocatedSize>
class CircularBuffer
{
	size_t size = 0;
	double val = 0;
public:
	constexpr size_t getAllocatedSize() const
	{
		return allocatedSize;
	}

	size_t getSize() const
	{
		return size;
	}

	void add(double d)
	{
		val = d;
		++size;
	}

	double pop()
	{
		--size;
		return val;
	}
};