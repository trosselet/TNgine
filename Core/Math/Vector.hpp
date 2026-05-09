#ifndef VECTOR_H__INCLUDED
#define VECTOR_H__INCLUDED

#include <algorithm>
#include <cmath>

#include "../define.h"
#include "../Utils/Utils.hpp"


template <typename T, uint32 Size>
struct Vector
{
	T data[Size];

	Vector() = default;

	Vector()
	{
		for (uint32 i = 0; i < Size; ++i)
		{
			data[i] = T(0);
		}
	};

	explicit Vector(const T& value)
	{
		for (uint32 i = 0; i < Size; ++i)
		{
			data[i] = value;
		}
	};

	Vector(std::initializer_list<T> list)
	{
		TNGINE_ASSERT(list.size() == Size, "Initializer list size must match vector size.");
		uint32 i = 0;
		for (auto v : list)
		{
			data[i++] = v;
		}
	};

	Vector(const Vector& other)
	{
		TNGINE_ASSERT(other.GetSize() == Size, "Vector sizes must match for copy construction.");
		uint32 i = 0;
		for (auto v : other.data)
		{
			data[i++] = v;
		}
	};

	T Norm()
	{
		return static_cast<T>(std::sqrt(NormSquared()));
	}

	T NormSquared()
	{
		T sum = T(0);
		for (uint32 i = 0; i < Size; ++i)
		{
			sum += data[i] * data[i];
		}
		return sum;
	};

	float32 Dot(const Vector& other)
	{
		TNGINE_ASSERT(other.GetSize() == Size, "Vector sizes must match for dot product.");
		T sum = T(0);
		for (uint32 i = 0; i < Size; ++i)
		{
			sum += data[i] * other.data[i];
		}
		return sum;
	};

	float32 Scalar(Vector& other)
	{
		TNGINE_ASSERT(other.GetSize() == Size, "Vector sizes must match.");

		T dot = Dot(other);
		T norms = Norm() * other.Norm();

		TNGINE_ASSERT(norms != T(0), "Cannot compute angle with zero-length vector.");

		return std::acos(static_cast<float32>(dot) / norms);
	};

	Vector& operator=(const Vector& other)
	{
		TNGINE_ASSERT(other.GetSize() == Size, "Vector sizes must match for assignment.");
		std::copy(std::begin(other.data), std::end(other.data), std::begin(data));
		return *this;
	}

	Vector operator+(const Vector& other) const
	{
		TNGINE_ASSERT(other.GetSize() == Size, "Vector sizes must match for addition.");
		Vector result;
		for (uint32 i = 0; i < Size; ++i)
		{
			result.data[i] = data[i] + other.data[i];
		}
		return result;
	}

	Vector operator-(const Vector& other) const
	{
		TNGINE_ASSERT(other.GetSize() == Size, "Vector sizes must match for subtraction.");
		Vector result;
		for (uint32 i = 0; i < Size; ++i)
		{
			result.data[i] = data[i] - other.data[i];
		}
		return result;
	}	

	Vector operator*(const T& scalar) const
	{
		Vector result;
		for (uint32 i = 0; i < Size; ++i)
		{
			result.data[i] = data[i] * scalar;
		}
		return result;
	}

	Vector operator/(const T& scalar) const
	{
		TNGINE_ASSERT(scalar != T(0), "Cannot divide by zero.");
		Vector result;
		for (uint32 i = 0; i < Size; ++i)
		{
			result.data[i] = data[i] / scalar;
		}
		return result;
	}

	Vector operator-() const
	{
		Vector result;
		for (uint32 i = 0; i < Size; ++i)
		{
			result.data[i] = -data[i];
		}
		return result;
	}

	Vector& operator+=(const Vector& other)
	{
		TNGINE_ASSERT(other.GetSize() == Size, "Vector sizes must match for addition.");
		for (uint32 i = 0; i < Size; ++i)
		{
			data[i] += other.data[i];
		}
		return *this;
	}

	Vector& operator-=(const Vector& other)
	{
		TNGINE_ASSERT(other.GetSize() == Size, "Vector sizes must match for subtraction.");
		for (uint32 i = 0; i < Size; ++i)
		{
			data[i] -= other.data[i];
		}
		return *this;
	}

	Vector& operator*=(const T& scalar)
	{
		for (uint32 i = 0; i < Size; ++i)
		{
			data[i] *= scalar;
		}
		return *this;
	}

	Vector& operator/=(const T& scalar)
	{
		TNGINE_ASSERT(scalar != T(0), "Cannot divide by zero.");
		for (uint32 i = 0; i < Size; ++i)
		{
			data[i] /= scalar;
		}
		return *this;
	}

	Vector operator*(const Vector& other) const
	{
		TNGINE_ASSERT(other.GetSize() == Size, "Vector sizes must match for element-wise multiplication.");
		Vector result;
		for (uint32 i = 0; i < Size; ++i)
		{
			result.data[i] = data[i] * other.data[i];
		}
		return result;
	}

	Vector operator/(const Vector& other) const
	{
		TNGINE_ASSERT(other.GetSize() == Size, "Vector sizes must match for element-wise division.");
		Vector result;
		for (uint32 i = 0; i < Size; ++i)
		{
			TNGINE_ASSERT(other.data[i] != T(0), "Cannot divide by zero in element-wise division.");
			result.data[i] = data[i] / other.data[i];
		}
		return result;
	}

	Vector& operator*=(const Vector& other)
	{
		TNGINE_ASSERT(other.GetSize() == Size, "Vector sizes must match for element-wise multiplication.");
		for (uint32 i = 0; i < Size; ++i)
		{
			data[i] *= other.data[i];
		}
		return *this;
	}

	Vector& operator/=(const Vector& other)
	{
		TNGINE_ASSERT(other.GetSize() == Size, "Vector sizes must match for element-wise multiplication.");
		for (uint32 i = 0; i < Size; ++i)
		{
			data[i] /= other.data[i];
		}
		return *this;
	}

	Vector Normalize()
	{
		T norm = Norm();
		TNGINE_ASSERT(norm != T(0), "Cannot normalize zero-length vector.");
		return *this / norm;
	}

	Vector Cross(const Vector& other) const
	{
		TNGINE_ASSERT(Size == 3, "Cross product is only defined for 3D vectors.");
		TNGINE_ASSERT(other.GetSize() == Size, "Vector sizes must match for cross product.");
		Vector result;
		result.data[0] = data[1] * other.data[2] - data[2] * other.data[1];
		result.data[1] = data[2] * other.data[0] - data[0] * other.data[2];
		result.data[2] = data[0] * other.data[1] - data[1] * other.data[0];
		return result;
	}

private:
	uint32 GetSize() const
	{
		return Size;
	}

};



#endif // !VECTOR_H__INCLUDED
