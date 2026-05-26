#ifndef RHI_DESCRIPTOR_LAYOUT_H__INCLUDED
#define RHI_DESCRIPTOR_LAYOUT_H__INCLUDED

#include "../RHIEnums.h"
#include "../RHIResource.h"

namespace TNgine
{
    struct DescriptorLayoutBinding
    {
        uint32 Binding;

        DescriptorType Type;

        ShaderStage Stage;
    };

    struct DescriptorLayoutCreateInfo
    {
        DynArray<DescriptorLayoutBinding> Bindings;
    };

    class RHIDescriptorLayout : public RHIResource
    {
    public:

        virtual ~RHIDescriptorLayout() = default;
    };
}

#endif // !RHI_DESCRIPTOR_LAYOUT_H__INCLUDED