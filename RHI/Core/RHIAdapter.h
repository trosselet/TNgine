#ifndef RHI_ADAPTER_H__INCLUDED
#define RHI_ADAPTER_H__INCLUDED

#include <Core/include.h>
#include "../RHIResource.h"

namespace TNgine
{
    class RHIAdapter : public RHIResource
    {
    public:

        virtual ~RHIAdapter() = default;

        virtual const std::string&
            GetName() const = 0;

        virtual uint64
            GetDedicatedVideoMemory() const = 0;

        virtual bool
            IsDiscrete() const = 0;
    };
}

#endif // !RHI_ADAPTER_H__INCLUDED
