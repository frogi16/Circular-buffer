#pragma once

template<size_t size>
class CircularBuffer
{
public:
	constexpr size_t getAllocatedSize() const
	{
		return size;
	}
};