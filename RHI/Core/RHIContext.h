#ifndef RHI_CONTEXT_H__INCLUDED
#define RHI_CONTEXT_H__INCLUDED

#include "RHIDevice.h"
#include "RHIAdapter.h"
#include "../RHIEnums.h"
#include "../RHIResource.h"

namespace TNgine
{
    class RHIContext : public RHIResource
    {
    public:

        virtual ~RHIContext() = default;

        virtual const DynArray<std::shared_ptr<RHIAdapter>>& GetAdapters() const = 0;

        virtual std::shared_ptr<RHIDevice> CreateDevice(RHIAdapter* adapter) = 0;
    };
}

#endif