#ifndef LINEAR_ALLOCATOR_H__INCLUDED
#define LINEAR_ALLOCATOR_H__INCLUDED

#include "../TMath.h"
#include "AllocatorTracker.hpp"

class LinearAllocator
{
public:
    LinearAllocator(uint64 size) : m_Size(size), m_Offset(0)
    {
		mp_Memory = std::malloc(size);
		AllocationTracker::Instance().Register({ mp_Memory, size, "LinearAllocator", __FILE__, __LINE__ });
    }

	virtual ~LinearAllocator()
	{
		AllocationTracker::Instance().Unregister(mp_Memory);
		std::free(mp_Memory);
	}

	void* Allocate(uint64 size, const char* file, uint32 line)
	{
		if (m_Offset + size > m_Size)
		{
			return nullptr;
		}

		void* ptr = static_cast<uint8*>(mp_Memory) + m_Offset;

		m_Offset += size;

		return ptr;
	}

	void Reset()
	{
		m_Offset = 0;
	}


private:
    uint64 m_Size;
    uint64 m_Offset;
    void*  mp_Memory;
};

#endif // !LINEAR_ALLOCATOR_H__INCLUDED