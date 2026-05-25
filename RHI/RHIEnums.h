#ifndef RHI_ENUMS_H__INCLUDED
#define RHI_ENUMS_H__INCLUDED

namespace TNgine
{
	enum class Backend
	{
		DirectX12,
		Vulkan,
		OpenGL
	};

	enum class ShaderStage
	{
		Vertex,
		Fragment,
		Compute,
		Geometry,
		TessControl,
		TessEvaluation
	};

	enum class BufferUsage
	{
		Vertex,
		Index,
		Uniform,
		Storage,
		Staging,
		Indirect
	};

	enum class TextureUsage
	{
		Sampled,
		Storage,
		RenderTarget,
		DepthStencil,
		TransferSrc,
		TransferDst
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

	enum class CompareOP
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
		Graphic,
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
}

#endif // !RHI_ENUMS_H__INCLUDED