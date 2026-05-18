#ifndef LINEAR_ALLOCATOR_H__INCLUDED
#define LINEAR_ALLOCATOR_H__INCLUDED

#include "../TMath.h"
#include "AllocatorTracker.hpp"

class LinearAllocator
{
public:
	LinearAllocator(const LinearAllocator&) = delete;
	LinearAllocator& operator=(const LinearAllocator&) = delete;

    LinearAllocator(uint64 size, const char* name = "") : m_Size(size), m_Offset(0)
    {
		mp_Memory = std::malloc(size);
		const char* allocatorName = name[0] ? name : "LinearAllocator";
		AllocationTracker::Instance().Register({ mp_Memory, size, allocatorName, __FILE__, __LINE__});
    }

	LinearAllocator(LinearAllocator&& other) noexcept
	{
		m_Size = other.m_Size;
		m_Offset = other.m_Offset;
		mp_Memory = other.mp_Memory;

		other.mp_Memory = nullptr;
		other.m_Size = 0;
		other.m_Offset = 0;
	}

	LinearAllocator& operator=(LinearAllocator&& other) noexcept
	{
		if (this == &other)
			return *this;

		std::free(mp_Memory);

		m_Size = other.m_Size;
		m_Offset = other.m_Offset;
		mp_Memory = other.mp_Memory;

		other.mp_Memory = nullptr;
		other.m_Size = 0;
		other.m_Offset = 0;

		return *this;
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