#ifndef RHI_PIPELINE_H__INCLUDED
#define RHI_PIPELINE_H__INCLUDED

#include "../RHIResource.h"
#include "../RHITypes.h"
#include "../RHIEnums.h"

namespace TNgine
{
    struct GraphicsPipelineCreateInfo
    {
        ShaderHandle VertexShader;
        ShaderHandle FragmentShader;

        PrimitiveTopology Topology = PrimitiveTopology::TriangleList;

        PolygonMode Polygon = PolygonMode::Fill;

        CullMode Cull = CullMode::Back;

        FrontFace Front = FrontFace::CounterClockWise;

        bool DepthTest = true;
        bool DepthWrite = true;
    };

    class RHIPipeline : public RHIResource
    {
    public:

        virtual ~RHIPipeline() = default;
    };
}

#endif