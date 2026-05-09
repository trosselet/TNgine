#pragma once

#include "Math/Vector.hpp"

using byte				= unsigned char;

using int8				= __int8;
using int16				= __int16;
using int32				= __int32;
using int64				= __int64; 

using uint8				= unsigned __int8;
using uint16			= unsigned __int16;
using uint32			= unsigned __int32;
using uint64			= unsigned __int64; 

using float32			= float;
using float64			= double;

using Vector2u			= Vector<int32, 2>;
using Vector3u			= Vector<int32, 3>;
using Vector4u			= Vector<int32, 4>;

using Vector2f			= Vector<float32, 2>;
using Vector3f			= Vector<float32, 3>;
using Vector4f			= Vector<float32, 4>;


constexpr float32 PI	= 3.14159265358979323846;