#ifndef RHI_COMMAND_ALLOCATOR_H__INCLUDED
#define RHI_COMMAND_ALLOCATOR_H__INCLUDED

#include "../RHIResource.h"

namespace TNgine
{
    class RHICommandAllocator : public RHIResource
    {
    public:

        virtual ~RHICommandAllocator() = default;

        virtual void Reset() = 0;
    };
}

#endif //!RHI_COMMAND_ALLOCATOR_H__INCLUDED