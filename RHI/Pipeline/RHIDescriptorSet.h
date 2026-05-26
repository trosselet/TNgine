#ifndef RHI_DESCRIPTOR_SET_H__INCLUDED
#define RHI_DESCRIPTOR_SET_H__INCLUDED

#include "../RHITypes.h"
#include "../RHIEnums.h"
#include "../RHIResource.h"

namespace TNgine
{
    class RHIBuffer;
    class RHITexture;
    class RHISampler;

    struct DescriptorBinding
    {
        uint32 Binding = 0;

        DescriptorType Type;

        ShaderStage Stage;
    };

    struct DescriptorSetLayoutCreateInfo
    {
        DynArray<DescriptorBinding> Bindings;
    };

    class RHIDescriptorSetLayout
    {
    public:

        virtual ~RHIDescriptorSetLayout() = default;
    };

    class RHIDescriptorSet : public RHIResource
    {
    public:

        virtual ~RHIDescriptorSet() = default;

        virtual void SetUniformBuffer(uint32 binding, RHIBuffer* buffer) = 0;

        virtual void SetStorageBuffer(uint32 binding, RHIBuffer* buffer) = 0;

        virtual void SetTexture(uint32 binding, RHITexture* texture) = 0;

        virtual void SetSampler(uint32 binding, RHISampler* sampler) = 0;

        virtual void Update() = 0;
    };
}

#endif