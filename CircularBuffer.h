#pragma once

template<size_t allocatedSize>
class CircularBuffer
{
	size_t first = 0;
	size_t size = 0;
	std::array<double, allocatedSize> vals;
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
		vals[size++] = d;
	}

	double pop()
	{
		--size;
		return vals[first++];
	}
};