#pragma once

template<size_t allocatedSize>
class CircularBuffer
{
	size_t begin = 0;
	size_t end = 0;
	bool isFull = false;
	std::array<double, allocatedSize> vals;
public:
	constexpr size_t getAllocatedSize() const
	{
		return allocatedSize;
	}

	size_t getSize() const
	{
		return end >= begin ? end - begin : allocatedSize - begin + end;
	}

	void add(double d)
	{
		vals[end] = d;
		
		if (isFull)
			begin = (begin + 1) % allocatedSize;

		end = (end + 1) % allocatedSize;

		isFull = (begin == end);
	}

	double pop()
	{
		auto &toRet = vals[begin];
		begin = (begin + 1) % allocatedSize;
		return toRet;
	}
};