#ifndef RHI_FENCE_LAYOUT_H__INCLUDED
#define RHI_FENCE_LAYOUT_H__INCLUDED

#include "../RHIResource.h"

namespace TNgine
{
    class RHIFence : public RHIResource
    {
    public:

        virtual ~RHIFence() = default;

        virtual void Wait() = 0;

        virtual void Reset() = 0;

        virtual bool IsSignaled() const = 0;
    };
}

#endif // !RHI_FENCE_LAYOUT_H__INCLUDED