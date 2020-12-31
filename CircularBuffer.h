#pragma once

template<size_t allocatedSize>
class CircularBuffer
{
	size_t first = 0;
	size_t end = 0;
	std::array<double, allocatedSize> vals;
public:
	constexpr size_t getAllocatedSize() const
	{
		return allocatedSize;
	}

	size_t getSize() const
	{
		return end >= first ? end - first : allocatedSize - first + end;
	}

	void add(double d)
	{
		vals[end] = d;
		if (end == allocatedSize - 1)
			end = 0;
		else
			end++;
	}

	double pop()
	{
		auto &toRet = vals[first];
		if (first == allocatedSize - 1)
			first = 0;
		else
			first++;
		return toRet;
	}
};