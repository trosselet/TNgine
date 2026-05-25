#ifndef RHI_BUFFER_H__INCLUDED
#define RHI_BUFFER_H__INCLUDED

#include "../RHIResource.h"
#include "../RHITypes.h"
#include "../RHIEnums.h"

namespace TNgine
{
    struct BufferCreateInfo
    {
        DeviceSize Size = 0;

        BufferUsage Usage = BufferUsage::None;

        MemoryUsage Memory = MemoryUsage::GPUOnly;

        bool PersistentMap = false;

        const void* InitialData = nullptr;

        std::string DebugName;
    };

    class RHIBuffer : public RHIResource
    {
    public:

        virtual ~RHIBuffer() = default;

        virtual DeviceSize GetSize() const = 0;

        virtual BufferUsage GetUsage() const = 0;
    };
}

#endif