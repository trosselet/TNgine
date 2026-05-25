#ifndef RHI_FORMATS_H__INCLUDED
#define RHI_FORMATS_H__INCLUDED

#include <Core/include.h>

namespace TNgine
{
    enum class RHIFormat
    {
        Unknown,

        R8_UNORM,
        R8_SNORM,

        RG8_UNORM,
        RG8_SNORM,

        RGB8_UNORM,
        RGBA8_UNORM,

        BGRA8_UNORM,

        RGBA16_FLOAT,

        RG32_FLOAT,
        RGB32_FLOAT,
        RGBA32_FLOAT,

        D16_UNORM,
        D24_UNORM_S8_UINT,
        D32_FLOAT,

        BC1,
        BC3,
        BC5,
        BC7
    };
}

#endif