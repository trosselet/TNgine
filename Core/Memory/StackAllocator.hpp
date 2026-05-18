#ifndef STACK_ALLOCATOR_H__INCLUDED
#define STACK_ALLOCATOR_H__INCLUDED

#include "../TMath.h"
#include "AllocatorTracker.hpp"

class StackAllocator
{
public:
	StackAllocator(uint64 size) : m_Size(size), m_Offset(0)
	{
		mp_Memory = std::malloc(size);
	}

	virtual ~StackAllocator()
	{
		std::free(mp_Memory);
	}

	void* Allocate(uint64 size, const char* file, uint32 line)
	{
		const uint64 headerSize = sizeof(AllocationHeader);

		if (m_Offset + headerSize + size > m_Size)
		{
			return nullptr;
		}

		void* current = static_cast<uint8*>(mp_Memory) + m_Offset;

		auto header = reinterpret_cast<AllocationHeader*>(current);

		header->previousOffset = m_Offset;

		m_Offset += headerSize;

		void* userPtr = static_cast<void*>(static_cast<uint8*>(current) + headerSize);

		m_Offset += size;

		AllocationTracker::Instance().Register({ userPtr, size, "StackAllocator", file, line });

		return userPtr;
	}

	void Free(void* ptr)
	{
		uint8* userPtr = static_cast<uint8*>(ptr);

		auto header = reinterpret_cast<AllocationHeader*>(userPtr - sizeof(AllocationHeader));

		m_Offset = header->previousOffset;

		AllocationTracker::Instance().Unregister(userPtr);
	}

	void Reset()
	{
		m_Offset = 0;
	}

private:
	struct AllocationHeader
	{
		uint64 previousOffset;
	};

private:
	uint64 m_Size;
	uint64 m_Offset;
	void* mp_Memory;
};


#endif // !STACK_ALLOCATOR_H__INCLUDED