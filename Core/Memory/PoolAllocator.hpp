#ifndef POOL_ALLOCATOR_H__INCLUDED
#define POOL_ALLOCATOR_H__INCLUDED

#include <algorithm>

#include "../TMath.h"
#include "AllocatorTracker.hpp"

class PoolAllocator
{
public:
	PoolAllocator(const PoolAllocator&) = delete;
	PoolAllocator& operator=(const PoolAllocator&) = delete;

	PoolAllocator(uint64 elementSize, uint64 elementCount) : m_ElementCount(elementCount)
	{
		m_ElementSize = std::max<uint64>(elementSize, sizeof(FreeNode));

		m_TotalSize = m_ElementSize * elementCount;

		mp_Memory = std::malloc(m_TotalSize);

		InitializeFreeList();
	}

	PoolAllocator(PoolAllocator&& other) noexcept
	{
		mp_Memory				= other.mp_Memory;
		mp_FreeList				= other.mp_FreeList;
		m_ElementSize			= other.m_ElementSize;
		m_ElementCount			= other.m_ElementCount;
		m_TotalSize				= other.m_TotalSize;

		other.mp_Memory			= nullptr;
		other.mp_FreeList		= nullptr;
		other.m_ElementSize		= 0;
		other.m_ElementCount	= 0;
		other.m_TotalSize		= 0;
	}

	PoolAllocator& operator=(PoolAllocator&& other) noexcept
	{
		if (this == &other)
			return *this;

		std::free(mp_Memory);

		mp_Memory = other.mp_Memory;
		mp_FreeList = other.mp_FreeList;
		m_ElementSize = other.m_ElementSize;
		m_ElementCount = other.m_ElementCount;
		m_TotalSize = other.m_TotalSize;

		other.mp_Memory = nullptr;
		other.mp_FreeList = nullptr;
		other.m_ElementSize = 0;
		other.m_ElementCount = 0;
		other.m_TotalSize = 0;

		return *this;
	}

	virtual ~PoolAllocator()
	{
		std::free(mp_Memory);
	}

	void* Allocate(uint64 size, const char* file, uint32 line)
	{
		TNGINE_ASSERT(size <= m_ElementSize, "Allocation too large for pool");

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
		if (!ptr)
		{
			return;
		}

		FreeNode* node = static_cast<FreeNode*>(ptr);

		node->next = mp_FreeList;

		mp_FreeList = node;

		AllocationTracker::Instance().Unregister(node);
	}

	void Reset()
	{
		InitializeFreeList();
	}

private:

	void InitializeFreeList()
	{
		mp_FreeList = nullptr;

		uint8* ptr =
			static_cast<uint8*>(mp_Memory);

		for (uint64 i = 0;
			i < m_ElementCount;
			++i)
		{
			FreeNode* node =
				reinterpret_cast<FreeNode*>(
					ptr + i * m_ElementSize);

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

	void* mp_Memory = nullptr;

	FreeNode* mp_FreeList = nullptr;

	uint64 m_ElementSize = 0;
	uint64 m_ElementCount = 0;
	uint64 m_TotalSize = 0;
};


#endif // !POOL_ALLOCATOR_H__INCLUDED