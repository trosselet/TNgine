#ifndef RHI_SEMAPHORE_LAYOUT_H__INCLUDED
#define RHI_SEMAPHORE_LAYOUT_H__INCLUDED

#include "../RHIResource.h"

namespace TNgine
{
    class RHISemaphore : public RHIResource
    {
    public:

        virtual ~RHISemaphore() = default;
    };
}

#endif // !RHI_SEMAPHORE_LAYOUT_H__INCLUDED