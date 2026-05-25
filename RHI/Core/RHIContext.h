#ifndef RHI_CONTEXT_H__INCLUDED
#define RHI_CONTEXT_H__INCLUDED

#include "RHIDevice.h"
#include "../RHIEnums.h"

namespace TNgine
{
    class RHIContext
    {
    public:

        static std::unique_ptr<RHIDevice> CreateDevice(Backend backend);
    };
}

#endif