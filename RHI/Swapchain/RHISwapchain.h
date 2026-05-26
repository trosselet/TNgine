#ifndef RHI_SWAPCHAIN_H__INCLUDED
#define RHI_SWAPCHAIN_H__INCLUDED

#include "../RHITypes.h"
#include "../RHIFormats.h"
#include "../RHIResource.h"

namespace TNgine
{
    class RHITexture;

    struct SwapchainCreateInfo
    {
        void* WindowHandle = nullptr;

        uint32 Width = 1;
        uint32 Height = 1;

        uint32 BufferCount = 2;

        RHIFormat Format = RHIFormat::BGRA8_UNORM;

        bool VSync = true;
    };

    class RHISwapchain : public RHIResource
    {
    public:

        virtual ~RHISwapchain() = default;

        virtual void Resize(uint32 width, uint32 height) = 0;

        virtual void Present() = 0;

        virtual uint32 AcquireNextImage() = 0;

        virtual RHITexture* GetBackBuffer(uint32 index) = 0;

        virtual uint32 GetWidth() const = 0;

        virtual uint32 GetHeight() const = 0;
    };
}

#endif