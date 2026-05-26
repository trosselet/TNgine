#ifndef RHI_CAPABILITIES_H__INCLUDED
#define RHI_CAPABILITIES_H__INCLUDED

#include <Core/include.h>

namespace TNgine
{
    struct RHICapabilities
    {
        bool RayTracing = false;

        bool MeshShaders = false;

        bool Bindless = false;

        bool MultiDrawIndirect = false;

        uint32 MaxTextureSize = 16384;

        uint32 MaxSamplerAnisotropy = 16;
    };
}

#endif // !RHI_CAPABILITIES_H__INCLUDED
