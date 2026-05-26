#ifndef RHI_BARRIER_LAYOUT_H__INCLUDED
#define RHI_BARRIER_LAYOUT_H__INCLUDED

#include "../Resources/RHITexture.h"
#include "../Resources/RHIBuffer.h" 

namespace TNgine
{
    struct BufferBarrier
    {
        RHIBuffer* Buffer;

        ResourceState OldState;

        ResourceState NewState;
    };

    struct TextureBarrier
    {
        RHITexture* Texture;

        ResourceState OldState;

        ResourceState NewState;
    };
}

#endif // !RHI_BARRIER_LAYOUT_H__INCLUDED