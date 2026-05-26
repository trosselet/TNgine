#pragma once

#include "TMath.h"

#include "Containers/DynArray.hpp"
#include "Containers/HashMap.hpp"

#include "Utils/Utils.hpp"
#include "Utils/ProfileScope.hpp"

#include "Events/EventQueue.hpp"
#include "Events/EventBus.hpp"
#include "Events/Events.h"

#include "Memory/PoolAllocator.hpp"
#include "Memory/StackAllocator.hpp"
#include "Memory/LinearAllocator.hpp"

#include "UUID/UUID.h"

#include "Threads/JobSystem.h"
#include "Threads/ThreadUtils.hpp"

template<typename T, typename Allocator, typename... Args>
T* AllocateObject(Allocator& allocator, Args&&... args)
{
    void* memory = allocator.Allocate(sizeof(T), __FILE__, __LINE__);

    return new(memory) T(std::forward<Args>(args)...);
}

template<typename T, typename Allocator>
void FreeObject(Allocator& allocator, T* ptr)
{
    if (!ptr)
        return;

    ptr->~T();

    allocator.Free(ptr);
}