#pragma once

#include "Math/Vector.hpp"
#include "Math/Matrix.hpp"

using Vector2u	= Vector<int32, 2>;
using Vector3u	= Vector<int32, 3>;
using Vector4u	= Vector<int32, 4>;

using Vector2f	= Vector<float32, 2>;
using Vector3f	= Vector<float32, 3>;
using Vector4f	= Vector<float32, 4>;

using Matrix2x2 = Matrix<float32, 2, 2>;
using Matrix3x3 = Matrix<float32, 3, 3>;
using Matrix4x4 = Matrix<float32, 4, 4>;