#ifndef RHI_RENDER_PASS_H__INCLUDED
#define RHI_RENDER_PASS_H__INCLUDED

#include "../RHIResource.h"
#include "../RHITypes.h"
#include "../RHIFormats.h"

namespace TNgine
{
    struct RenderPassAttachment
    {
        RHIFormat Format = RHIFormat::RGBA8_UNORM;

        bool Clear = true;

        ClearColor ClearValue = { 0, 0, 0, 1 };
    };

    struct RenderPassCreateInfo
    {
        DynArray<RenderPassAttachment> ColorAttachments;
    };

    class RHIRenderPass : public RHIResource
    {
    public:

        virtual ~RHIRenderPass() = default;
    };
}

#endif