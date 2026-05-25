#ifndef RHI_TYPES_H__INCLUDED
#define RHI_TYPES_H__INCLUDED

#include <Core/include.h>

namespace TNgine
{

	/*-----HANDLE-----*/
	using BufferHandle = uint32;
	using ShaderHandle = uint32;
	using SamplerHandle = uint32;
	using TextureHandle = uint32;
	using PipelineHandle = uint32;
	using DescriptorSetHandle = uint32;

	/*-----GPU-----*/
	using GPUAddress = uint64;
	using DeviceSize = uint64;


	/*-----IDs-----*/
	using FrameIndex = uint32;
	using QueueIndex = uint32;

	/*-----STRUCT-----*/
	struct Viewport
	{
		float x;
		float y;
		float Width;
		float Height;
		float MinDepth;
		float MaxDepth;
	};

	struct ScissorRect
	{
		int32 x;
		int32 y;
		int32 Width;
		int32 Height;
	};

	struct ClearValue
	{
		float R;
		float G;
		float B;
		float A;
	};

	struct DepthStencil
	{
		float Depth;
		uint32 Stencil;
	};

	struct Extent2D
	{
		uint32 Width;
		uint32 Height;
	};
	
	struct Extent3D
	{
		uint32 Width;
		uint32 Height;
		uint32 Depth;
	};
}
#endif // !RHI_TYPES_H__INCLUDED