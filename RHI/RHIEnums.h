#ifndef RHI_ENUMS_H__INCLUDED
#define RHI_ENUMS_H__INCLUDED

#include <Core/include.h>

namespace TNgine
{
    enum class Backend
    {
        Vulkan,
        OpenGL,
        DirectX12
    };

    enum class ShaderStage : uint32
    {
        None = 0,

        Vertex = 1 << 0,
        Fragment = 1 << 1,
        Compute = 1 << 2,
        Geometry = 1 << 3,
        TessControl = 1 << 4,
        TessEvaluation = 1 << 5
    };

    enum class BufferUsage : uint32
    {
        None = 0,

        Vertex = 1 << 0,
        Index = 1 << 1,
        Uniform = 1 << 2,
        Storage = 1 << 3,
        Staging = 1 << 4,
        Indirect = 1 << 5,

        TransferSrc = 1 << 6,
        TransferDst = 1 << 7
    };

    enum class TextureUsage : uint32
    {
        None = 0,

        Sampled = 1 << 0,
        Storage = 1 << 1,
        RenderTarget = 1 << 2,
        DepthStencil = 1 << 3,

        TransferSrc = 1 << 4,
        TransferDst = 1 << 5
    };

    enum class MemoryUsage
    {
        CPUOnly,
        GPUOnly,
        CPUToGPU,
        GPUToCPU
    };

    enum class PrimitiveTopology
    {
        TriangleList,
        TriangleStrip,

        LineList,
        LineStrip,

        PointList
    };

    enum class PolygonMode
    {
        Fill,
        Line,
        Point
    };

    enum class CullMode
    {
        None,
        Front,
        Back
    };

    enum class FrontFace
    {
        ClockWise,
        CounterClockWise
    };

    enum class CompareOp
    {
        Never,
        Less,
        Equal,
        LessEqual,
        Greater,
        NotEqual,
        GreaterEqual,
        Always
    };

    enum class BlendFactor
    {
        Zero,
        One,

        SrcColor,
        OneMinusSrcColor,

        DstColor,
        OneMinusDstColor,

        SrcAlpha,
        OneMinusSrcAlpha
    };

    enum class QueueType
    {
        Graphics,
        Compute,
        Transfer
    };

    enum class ResourceState
    {
        Undefined,

        RenderTarget,

        DepthWrite,
        DepthRead,

        ShaderRead,
        ShaderWrite,

        CopySrc,
        CopyDst,

        Present
    };

    enum class Filter
    {
        Nearest,
        Linear
    };

    enum class MipmapMode
    {
        Nearest,
        Linear
    };

    enum class AddressMode
    {
        Repeat,
        MirroredRepeat,

        ClampToEdge,
        ClampToBorder
    };

    enum class DescriptorType
    {
        UniformBuffer,
        StorageBuffer,

        SampledTexture,
        StorageTexture,

        Sampler
    };

    enum class BarrierType
    {
        Buffer,
        Texture
    };
}

#endif