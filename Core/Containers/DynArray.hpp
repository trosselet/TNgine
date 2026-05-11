#ifndef DYN_ARRAY_H__INCLUDED
#define DYN_ARRAY_H__INCLUDED

#include "../define.h"
#include "../Utils/Utils.hpp"

#pragma pack(8) 
template<typename T>
class DynArray
{
public:
	DynArray()
	{
		m_size = 0;
		m_capacity = 0;
		mp_data = nullptr;
	};

	~DynArray()
	{
		delete[] mp_data;
	};

	DynArray(const DynArray& other)
	{
		m_size = other.m_size;
		m_capacity = other.m_capacity;

		mp_data = new T[other.m_size]; 
		for (uint32 i = 0; i < m_size; ++i)
		{
			mp_data[i] = other.mp_data[i];
		}
	};


	DynArray(const uint32 size)
	{
		m_size = size;
		m_capacity = size;
		mp_data = new T[size];
	};

	DynArray(const uint32 size, const T& defaultValue)
	{
		m_size = size;
		m_capacity = size;

		mp_data = new T[size];
		for (uint32 i = 0; i < size; ++i)
		{
			mp_data[i] = defaultValue;
		}
	};

	uint64 Size() const
	{
		return m_size;
	};

	uint64 Capacity() const
	{
		return m_capacity;
	};

	T* Data() const
	{
		return mp_data;
	};

	T* Begin()
	{
		return mp_data;
	}

	const T* Begin() const
	{
		return mp_data;
	}

	T* End()
	{
		return mp_data + m_size;
	}

	const T* End() const
	{
		return mp_data + m_size;
	}

	T* RBegin()
	{
		return mp_data + m_size;
	}

	const T* RBegin() const
	{
		return mp_data + m_size;
	}

	T* REnd()
	{
		return mp_data;
	}

	const T* REnd() const
	{
		return mp_data;
	}

	void Resize(const uint64 size)
	{
		if (size == m_size)
			return;

		T* pNew = new T[size];

		uint64 copySize = std::min(size, m_size);

		for (uint64 i = 0; i < copySize; ++i)
			pNew[i] = std::move(mp_data[i]);

		if (size > m_size)
			memset(pNew + copySize, 0, (size * sizeof(T)) - (m_size * sizeof(T)));

		delete[] mp_data;

		mp_data = pNew;
		m_size = size;
		m_capacity = size;
	}

	void Reserve(const uint64 newCapacity)
	{
		if (newCapacity == m_size)
			return;

		T* pNew = new T[newCapacity];

		uint64 copySize = std::min(newCapacity, m_size);

		for (uint64 i = 0; i < copySize; ++i)
			pNew[i] = std::move(mp_data[i]);

		delete[] mp_data;

		mp_data = pNew; 
		m_capacity = newCapacity;
	}

	void PushBack(const T& value)
	{
		if (m_size >= m_capacity)
			Reserve(static_cast<uint64>(m_size * 1.5f));

		mp_data[m_size] = value;
		m_size++;

		return;
	};

	void Assign(uint64 count, const T& value)
	{
		//TODO
	};

private:
	uint64 m_size = 0;
	uint64 m_capacity = 0;
	T* mp_data = nullptr;
};
#pragma pop(pack)

#endif // !DYN_ARRAY_H__INCLUDED
