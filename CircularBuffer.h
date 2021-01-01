#pragma once

template<size_t allocatedSize>
class CircularBuffer
{
	size_t begin = 0;
	size_t end = 0;
	bool isFull = false;
	std::array<double, allocatedSize> vals;

	void incrementModuloSize(size_t& i) const
	{
		i = (i + 1) % allocatedSize;
	}

public:
	constexpr size_t getAllocatedSize() const
	{
		return allocatedSize;
	}

	size_t getSize() const
	{
		return end >= begin ? end - begin : allocatedSize - begin + end;
	}

	void add(double val)
	{
		vals[end] = val;
		
		if (isFull)
			incrementModuloSize(begin);

		incrementModuloSize(end);

		isFull = (begin == end);
	}

	double pop()
	{
		auto &toRet = vals[begin];
		incrementModuloSize(begin);
		return toRet;
	}
};