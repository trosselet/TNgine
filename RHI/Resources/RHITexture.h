#ifndef RHI_TEXTURE_H__INCLUDED
#define RHI_TEXTURE_H__INCLUDED

#include "../RHIResource.h"
#include "../RHITypes.h"
#include "../RHIEnums.h"
#include "../RHIFormats.h"

namespace TNgine
{
    struct TextureCreateInfo
    {
        uint32 Width = 1;
        uint32 Height = 1;
        uint32 Depth = 1;

        uint32 MipLevels = 1;

        RHIFormat Format = RHIFormat::RGBA8_UNORM;

        TextureUsage Usage = TextureUsage::Sampled;

        std::string DebugName;
    };

    class RHITexture : public RHIResource
    {
    public:

        virtual ~RHITexture() = default;

        virtual uint32 GetWidth() const = 0;

        virtual uint32 GetHeight() const = 0;

        virtual RHIFormat GetFormat() const = 0;
    };
}

#endif