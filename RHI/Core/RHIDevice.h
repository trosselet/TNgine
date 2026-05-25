#ifndef RHI_DEVICE_H__INCLUDED
#define RHI_DEVICE_H__INCLUDED

#include "../Resources/RHIBuffer.h"
#include "../Resources/RHITexture.h"
#include "../Resources/RHISampler.h"
#include "../Resources/RHIShader.h"
#include "../Pipeline/RHIPipeline.h"
#include "../Pipeline/RHIRenderPass.h"

namespace TNgine
{
    class RHIDevice
    {
    public:

        virtual ~RHIDevice() = default;

        virtual std::unique_ptr<RHIBuffer>CreateBuffer(const BufferCreateInfo& createInfo) = 0;

        virtual std::unique_ptr<RHITexture>CreateTexture(const TextureCreateInfo& createInfo) = 0;

        virtual std::unique_ptr<RHISampler>CreateSampler(const SamplerCreateInfo& createInfo) = 0;

        virtual std::unique_ptr<RHIShader>CreateShader(const ShaderCreateInfo& createInfo) = 0;

        virtual std::unique_ptr<RHIPipeline>CreateGraphicsPipeline(const GraphicsPipelineCreateInfo& createInfo) = 0;

        virtual std::unique_ptr<RHIRenderPass>CreateRenderPass(const RenderPassCreateInfo& createInfo) = 0;
    };
}

#endif