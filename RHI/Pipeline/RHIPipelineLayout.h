#ifndef RHI_PIPELINE_LAYOUT_H__INCLUDED
#define RHI_PIPELINE_LAYOUT_H__INCLUDED

#include "../RHIEnums.h"
#include "RHIDescriptorLayout.h"
#include "../RHIResource.h"

namespace TNgine
{
    struct PushConstantRange
    {
        ShaderStage Stage;

        uint32 Offset;

        uint32 Size;
    };

    struct PipelineLayoutCreateInfo
    {
        DynArray<RHIDescriptorLayout*> DescriptorLayouts;

        DynArray<PushConstantRange> PushConstants;
    };

    class RHIPipelineLayout : public RHIResource
    {
    public:

        virtual ~RHIPipelineLayout() = default;
    };
}

#endif // !RHI_PIPELINE_LAYOUT_H__INCLUDED