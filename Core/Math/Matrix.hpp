#ifndef MATRIX_H__INCLUDED
#define MATRIX_H__INCLUDED

#include <cmath>
#include <algorithm>
#include <iostream>

#include "../define.h"
#include "../Utils/Utils.hpp"

template<typename T, uint32 Rows, uint32 Cols>
struct Matrix
{
public:

	T data[Rows][Cols];

	// =========================
	// Constructors
	// =========================

	Matrix()
	{
		if (Rows == Cols)
		{
			SetIdentity();
		}
		else
		{
			SetZero();
		} 
	}

	explicit Matrix(const T& value)
	{
		for (uint32 r = 0; r < Rows; ++r)
		{
			for (uint32 c = 0; c < Cols; ++c)
			{
				data[r][c] = value;
			}
		}
	}

	// =========================
	// Basic init
	// =========================

	void SetZero()
	{
		for (uint32 r = 0; r < Rows; ++r)
		{
			for (uint32 c = 0; c < Cols; ++c)
			{
				data[r][c] = T(0);
			}
		}
	}

	void SetIdentity()
	{
		TNGINE_STATIC_ASSERT(Rows == Cols, "Identity requires square matrix.");

		for (uint32 r = 0; r < Rows; ++r)
		{
			for (uint32 c = 0; c < Cols; ++c)
			{
				data[r][c] = (r == c) ? T(1) : T(0);
			}
		}
	}

	// =========================
	// Access
	// =========================

	T* operator[](uint32 row)
	{
		return data[row];
	}

	const T* operator[](uint32 row) const
	{
		return data[row];
	}

	// =========================
	// Transpose
	// =========================

	Matrix<T, Cols, Rows> Transpose() const
	{
		Matrix<T, Cols, Rows> result;

		for (uint32 r = 0; r < Rows; ++r)
		{
			for (uint32 c = 0; c < Cols; ++c)
			{
				result[c][r] = data[r][c];
			}
		}

		return result;
	}

	// =========================
	// Determinant (square only)
	// =========================

	T Determinant() const
	{
		TNGINE_STATIC_ASSERT(Rows == Cols, "Determinant requires square matrix.");

		if constexpr (Rows == 1)
		{
			return data[0][0];
		}
		else if constexpr (Rows == 2)
		{
			return data[0][0] * data[1][1] - data[0][1] * data[1][0];
		}
		else
		{
			T det = T(0);

			for (uint32 c = 0; c < Cols; ++c)
			{
				T sign = (c % 2 == 0) ? T(1) : T(-1);
				det += sign * data[0][c] * GetSubmatrix(0, c).Determinant();
			}

			return det;
		}
	}

	// =========================
	// Submatrix
	// =========================

	Matrix<T, Rows - 1, Cols - 1> GetSubmatrix(uint32 excludeRow, uint32 excludeCol) const
	{
		TNGINE_STATIC_ASSERT(Rows > 1 && Cols > 1, "Invalid submatrix size.");

		Matrix<T, Rows - 1, Cols - 1> result;

		uint32 r2 = 0;

		for (uint32 r = 0; r < Rows; ++r)
		{
			if (r == excludeRow) continue;

			uint32 c2 = 0;

			for (uint32 c = 0; c < Cols; ++c)
			{
				if (c == excludeCol) continue;

				result[r2][c2] = data[r][c];
				++c2;
			}

			++r2;
		}

		return result;
	}

	// =========================
	// Inverse (adjugate method)
	// =========================

	Matrix Inverse() const
	{
		TNGINE_STATIC_ASSERT(Rows == Cols, "Inverse requires square matrix.");

		T det = Determinant();
		TNGINE_ASSERT(det != T(0), "Matrix is singular.");

		Matrix<T, Rows, Cols> adj;

		for (uint32 r = 0; r < Rows; ++r)
		{
			for (uint32 c = 0; c < Cols; ++c)
			{
				T sign = ((r + c) % 2 == 0) ? T(1) : T(-1);
				adj[c][r] = sign * GetSubmatrix(r, c).Determinant();
			}
		}

		return adj / det;
	}

	void Print() const
	{
		for (uint32 r = 0; r < Rows; ++r)
		{
			for (uint32 c = 0; c < Cols; ++c)
			{
				std::cout << data[r][c] << " ";
			}
			std::cout << std::endl;
		}
	}

	// =========================
	// Operators
	// =========================

	Matrix operator+(const Matrix& other) const
	{
		Matrix result;

		for (uint32 r = 0; r < Rows; ++r)
		{
			for (uint32 c = 0; c < Cols; ++c)
			{
				result[r][c] = data[r][c] + other[r][c];
			}
		}

		return result;
	}

	Matrix operator-(const Matrix& other) const
	{
		Matrix result;

		for (uint32 r = 0; r < Rows; ++r)
		{
			for (uint32 c = 0; c < Cols; ++c)
			{
				result[r][c] = data[r][c] - other[r][c];
			}
		}

		return result;
	}

	Matrix operator*(const T& scalar) const
	{
		Matrix result;

		for (uint32 r = 0; r < Rows; ++r)
		{
			for (uint32 c = 0; c < Cols; ++c)
			{
				result[r][c] = data[r][c] * scalar;
			}
		}

		return result;
	}

	Matrix operator/(const T& scalar) const
	{
		TNGINE_ASSERT(scalar != T(0), "Divide by zero.");

		Matrix result;

		for (uint32 r = 0; r < Rows; ++r)
		{
			for (uint32 c = 0; c < Cols; ++c)
			{
				result[r][c] = data[r][c] / scalar;
			}
		}

		return result;
	}

	Matrix& operator+=(const Matrix& other)
	{
		for (uint32 r = 0; r < Rows; ++r)
		{
			for (uint32 c = 0; c < Cols; ++c)
			{
				data[r][c] += other[r][c];
			}
		}

		return *this;
	}

	Matrix& operator-=(const Matrix& other)
	{
		for (uint32 r = 0; r < Rows; ++r)
		{
			for (uint32 c = 0; c < Cols; ++c)
			{
				data[r][c] -= other[r][c];
			}
		}

		return *this;
	}

	Matrix& operator*=(const T& scalar)
	{
		for (uint32 r = 0; r < Rows; ++r)
		{
			for (uint32 c = 0; c < Cols; ++c)
			{
				data[r][c] *= scalar;
			}
		}

		return *this;
	}

	Matrix& operator*=(const Matrix& other)
	{
		TNGINE_STATIC_ASSERT(Rows == Cols, "Only square matrices supported for *=");

		Matrix result;

		for (uint32 r = 0; r < Rows; ++r)
		{
			for (uint32 c = 0; c < Cols; ++c)
			{
				result[r][c] = T(0);

				for (uint32 k = 0; k < Cols; ++k)
				{
					result[r][c] += data[r][k] * other[k][c];
				}
			}
		}

		*this = result;
		return *this;
	}
};

#endif