#ifndef RHI_COMMAND_QUEUE_H__INCLUDED
#define RHI_COMMAND_QUEUE_H__INCLUDED

#include "../RHIResource.h"

namespace TNgine
{
    class RHICommandList;

    class RHICommandQueue : public RHIResource
    {
    public:

        virtual ~RHICommandQueue() = default;

        virtual void Submit(RHICommandList* commandList) = 0;

        virtual void WaitIdle() = 0;
    };
}

#endif //!RHI_COMMAND_QUEUE_H__INCLUDED