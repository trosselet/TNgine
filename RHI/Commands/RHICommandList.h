#ifndef RHI_COMMAND_LIST_H__INCLUDED
#define RHI_COMMAND_LIST_H__INCLUDED

#include "../RHITypes.h"
#include "../RHIEnums.h"
#include "../RHIResource.h"

namespace TNgine
{
    class RHIBuffer;
    class RHITexture;
    class RHIPipeline;
    class RHIRenderPass;

    class RHICommandList : public RHIResource
    {
    public:

        virtual ~RHICommandList() = default;

        virtual void Begin() = 0;

        virtual void End() = 0; 

        virtual void BeginRenderPass(RHIRenderPass* renderPass) = 0;

        virtual void EndRenderPass() = 0; 

        virtual void BindPipeline(RHIPipeline* pipeline) = 0;

        virtual void BindVertexBuffer(RHIBuffer* buffer, uint64 offset = 0) = 0;

        virtual void BindIndexBuffer(RHIBuffer* buffer, uint64 offset = 0) = 0;
         
        virtual void SetViewport(const Viewport& viewport) = 0;

        virtual void SetScissor(const ScissorRect& scissor) = 0;

        virtual void Draw(uint32 vertexCount, uint32 instanceCount = 1, uint32 firstVertex = 0, uint32 firstInstance = 0) = 0;

        virtual void DrawIndexed(uint32 indexCount, uint32 instanceCount = 1, uint32 firstIndex = 0, int32  vertexOffset = 0, uint32 firstInstance = 0) = 0;

        virtual void Dispatch(uint32 groupX, uint32 groupY, uint32 groupZ) = 0;

        virtual void CopyBuffer(RHIBuffer* src, RHIBuffer* dst, DeviceSize size) = 0;

        virtual void CopyBufferToTexture(RHIBuffer* src, RHITexture* dst) = 0;

        virtual void TransitionTexture(RHITexture* texture, ResourceState oldState, ResourceState newState) = 0;

        virtual void TransitionBuffer(RHIBuffer* buffer, ResourceState oldState, ResourceState newState) = 0;
    };
}

#endif