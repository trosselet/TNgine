#ifndef RHI_DEVICE_H__INCLUDED
#define RHI_DEVICE_H__INCLUDED

#include "../Core/RHICapabilities.h"
#include "../Resources/RHIBuffer.h"
#include "../Resources/RHITexture.h"
#include "../Resources/RHISampler.h"
#include "../Resources/RHIShader.h"
#include "../Pipeline/RHIPipeline.h"
#include "../Pipeline/RHIRenderPass.h"
#include "../Commands/RHICommandList.h"
#include "../Commands/RHICommandQueue.h"
#include "../Commands/RHICommandAllocator.h"
#include "../Sync/RHIFence.h"
#include "../Sync/RHISemaphore.h"

#include "../RHIResource.h"

namespace TNgine
{
    class RHIDevice : public RHIResource
    {
    public:

        virtual ~RHIDevice() = default;

        virtual RHICapabilities GetCapabilities() const = 0;

        virtual std::unique_ptr<RHIBuffer>CreateBuffer(const BufferCreateInfo& createInfo) = 0;

        virtual std::unique_ptr<RHITexture>CreateTexture(const TextureCreateInfo& createInfo) = 0;

        virtual std::unique_ptr<RHISampler>CreateSampler(const SamplerCreateInfo& createInfo) = 0;

        virtual std::unique_ptr<RHIShader>CreateShader(const ShaderCreateInfo& createInfo) = 0;

        virtual std::unique_ptr<RHIPipeline>CreateGraphicsPipeline(const GraphicsPipelineCreateInfo& createInfo) = 0;

        virtual std::unique_ptr<RHIRenderPass>CreateRenderPass(const RenderPassCreateInfo& createInfo) = 0;

        virtual std::unique_ptr<RHICommandAllocator> CreateCommandAllocator(QueueType queue) = 0;

        virtual std::unique_ptr<RHICommandList> CreateCommandList(RHICommandAllocator*) = 0;

        virtual std::unique_ptr<RHICommandQueue> GetQueue(QueueType queue) = 0;

        virtual std::unique_ptr<RHIFence> CreateFence() = 0;

        virtual std::unique_ptr<RHISemaphore> CreateSemaphore() = 0;
    };
}

#endif