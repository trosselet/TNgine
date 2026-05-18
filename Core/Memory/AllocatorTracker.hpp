#ifndef ALLOCATOR_TRACKER_H__INCLUDED
#define ALLOCATOR_TRACKER_H__INCLUDED

#include "../TMath.h"
#include "../Containers/HashMap.hpp"

struct AllocationInfo
{
    void* Address;

    uint64 Size;

    const char* AllocatorName;

    const char* File;
    uint32 Line;
};

struct MemoryStats
{
    uint64 TotalAllocated = 0;
    uint64 CurrentAllocated = 0;
    uint64 PeakAllocated = 0;

    uint64 AllocationCount = 0;
    uint64 FreeCount = 0;
};

class AllocationTracker
{
public:

    static AllocationTracker& Instance()
    {
        static AllocationTracker instance;
		return instance;
    }

    void Register(const AllocationInfo& info)
    {
		m_Allocations[info.Address] = info;

        m_Stats.TotalAllocated += info.Size;
        m_Stats.CurrentAllocated += info.Size;
        m_Stats.AllocationCount++;

        if (m_Stats.CurrentAllocated > m_Stats.PeakAllocated)
        {
            m_Stats.PeakAllocated = m_Stats.CurrentAllocated;
        }
    }

    void Unregister(void* ptr)
    {
        AllocationInfo* info = m_Allocations.Find(ptr);

        if (!info)
        {
            CLOG_ERROR("Double free detected {:p}", ptr);
            return;
        }

        m_Stats.CurrentAllocated -= info->Size;
        m_Stats.FreeCount++;

        m_Allocations.Remove(ptr);
    }

    void DumpLeaks()
    {
        for (auto& pair : m_Allocations)
        {
            const AllocationInfo& info = pair.second;

            CLOG_WARN(
                "Memory Leak | Address: {:p} | Size: {} bytes | Allocator: {} | Location: {}:{}",
                info.Address,
                info.Size,
                info.AllocatorName,
                info.File,
                info.Line);
        }
    }

    ~AllocationTracker()
    {
        DumpLeaks();
    }

private:

    TNgine::HashMap<void*, AllocationInfo> m_Allocations;
    MemoryStats m_Stats;
};


#endif // !ALLOCATOR_TRACKER_H__INCLUDED
