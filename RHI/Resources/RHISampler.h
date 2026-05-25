#ifndef RHI_SAMPLER_H__INCLUDED
#define RHI_SAMPLER_H__INCLUDED

#include "../RHIResource.h"
#include "../RHIEnums.h"

namespace TNgine
{
    struct SamplerCreateInfo
    {
        Filter MinFilter = Filter::Linear;
        Filter MagFilter = Filter::Linear;

        MipmapMode MipFilter = MipmapMode::Linear;

        AddressMode AddressU = AddressMode::Repeat;
        AddressMode AddressV = AddressMode::Repeat;
        AddressMode AddressW = AddressMode::Repeat;

        float MaxAnisotropy = 1.0f;

        std::string DebugName;
    };

    class RHISampler : public RHIResource
    {
    public:

        virtual ~RHISampler() = default;
    };
}

#endif