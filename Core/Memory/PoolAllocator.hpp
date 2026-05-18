#ifndef POOL_ALLOCATOR_H__INCLUDED
#define POOL_ALLOCATOR_H__INCLUDED

#include "../TMath.h"
#include "AllocatorTracker.hpp"

class PoolAllocator
{
public:
	PoolAllocator(uint64 objectSize, uint64 objectCount) : m_Size(objectSize), m_Offset(0)
	{
		mp_Memory = std::malloc(objectSize * objectCount);
		InitializeList(objectSize);
	}

	virtual ~PoolAllocator()
	{
		std::free(mp_Memory);
	}

	void* Allocate(uint64 size, const char* file, uint32 line)
	{
		if (!mp_FreeList)
		{
			return nullptr;
		}

		FreeNode* node = mp_FreeList;

		mp_FreeList = node->next;

		AllocationTracker::Instance().Register({ node, size, "PoolAllocator", file, line });

		return node;
	}

	void Free(void* ptr)
	{
		FreeNode* node = static_cast<FreeNode*>(ptr);

		node->next = mp_FreeList;

		mp_FreeList = node;

		AllocationTracker::Instance().Unregister(node);
	}

	void Reset()
	{
		m_Offset = 0;
	}

private:

	void InitializeList(uint64 objectSize)
	{
		uint8* ptr = static_cast<uint8*>(mp_Memory);

		for (uint64 i = 0; i < m_Size; ++i)
		{
			FreeNode* node = reinterpret_cast<FreeNode*>(ptr + i * objectSize);

			node->next = mp_FreeList;

			mp_FreeList = node;
		}
	}

private:

	struct FreeNode
	{
		FreeNode* next;
	}; 

private:
	uint64 m_Size;
	uint64 m_Offset;
	void* mp_Memory;

	FreeNode* mp_FreeList;
};


#endif // !POOL_ALLOCATOR_H__INCLUDED