#ifndef RHI_SHADER_H__INCLUDED
#define RHI_SHADER_H__INCLUDED

#include "../RHIResource.h"
#include "../RHIEnums.h"

namespace TNgine
{
    struct ShaderCreateInfo
    {
        ShaderStage Stage = ShaderStage::Vertex;

        DynArray<byte> ByteCode;

        std::string DebugName;
    };

    class RHIShader : public RHIResource
    {
    public:

        virtual ~RHIShader() = default;

        virtual ShaderStage GetStage() const = 0;
    };
}

#endif