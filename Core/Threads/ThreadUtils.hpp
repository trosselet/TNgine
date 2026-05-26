#ifndef THREAD_UTILS_H__INCLUDED
#define THREAD_UTILS_H__INCLUDED

#include "../PrimitivesTypes.h"
#include "../define.h"

#include <thread>
#include <string>

#ifdef TNGINE_OS_WINDOWS
#include <Windows.h>
#endif

namespace TNgine
{
    namespace ThreadUtils
    {
        inline uint32 GetHardwareThreadCount()
        {
            return static_cast<uint32>(
                std::thread::hardware_concurrency()
                );
        }

        inline void SetCurrentThreadName(
            const std::string& name
        )
        {
#ifdef TNGINE_OS_WINDOWS

            std::wstring wideName(name.begin(), name.end());

            SetThreadDescription(GetCurrentThread(),  wideName.c_str());

#endif
        }
    }
}

#endif //!THREAD_UTILS_H__INCLUDED