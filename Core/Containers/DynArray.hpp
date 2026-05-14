#ifndef DYN_ARRAY_H__INCLUDED
#define DYN_ARRAY_H__INCLUDED

#include <algorithm>

#include "../define.h"
#include "../Utils/Utils.hpp"

template<typename DynArray>
class DynArrayIterator
{
public:
	using ValueType = typename DynArray::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;
public:
	DynArrayIterator(PointerType ptr) : m_ptr(ptr)
	{
	}

	DynArrayIterator& operator++()
	{
		m_ptr++;
		return *this;
	}

	DynArrayIterator operator++(int)
	{
		DynArrayIterator iterator = *this;
		++(*this);
		return iterator;
	}
	
	DynArrayIterator& operator--()
	{
		m_ptr--;
		return *this;
	}

	DynArrayIterator operator--(int)
	{
		DynArrayIterator iterator = *this;
		--(*this);
		return iterator;
	}

	ReferenceType operator[](int index)
	{
		return *(m_ptr + index);
	}

	PointerType operator->()
	{
		return m_ptr;
	}

	ReferenceType operator*()
	{
		return *m_ptr;
	}

	bool operator==(const DynArrayIterator& other) const
	{
		return m_ptr == other.m_ptr;
	}
	
	bool operator!=(const DynArrayIterator& other) const
	{
		return !(*this == other);
	}

private:
	PointerType m_ptr;
};


#pragma pack(8) 
template<typename T>
class DynArray
{
public:
	using ValueType = T;
	using Iterator = DynArrayIterator<DynArray<T>>;
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

	DynArray(DynArray&& other) noexcept
	{
		m_size = other.m_size;
		m_capacity = other.m_capacity;
		mp_data = other.mp_data;

		other.m_size = 0;
		other.m_capacity = 0;
		other.mp_data = nullptr;
	}


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

	T& Front()
	{
		return mp_data;
	}

	const T& Front() const
	{
		return mp_data;
	}

	T& Back()
	{
		return mp_data + m_size - 1;
	}

	const T& Back() const
	{
		return mp_data + m_size - 1;
	} 

	Iterator begin()
	{
		return Iterator(mp_data);
	}

	Iterator end()
	{
		return Iterator(mp_data + m_size);
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
		if (newCapacity <= m_size)
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

	void PushFront(const T& value)
	{
		if (m_size >= m_capacity)
			Reserve(static_cast<uint64>(m_size * 1.5f));
		m_size++;

		for (uint64 i = m_size - 1; i > 0; --i)
		{
			mp_data[i] = std::move(mp_data[i - 1]);
		}
		mp_data[0] = value;

		return;
	};

	void Assign(uint64 count, const T& value)
	{
		if (count > m_size)
			count = m_size;

		for (uint64 i = 0; i < count; ++i)
		{
			mp_data[i] = value;
		}

	};

	void Assign(std::initializer_list<T> list)
	{
		uint64 size = list.size();
		if (size > m_size)
			size = m_size;

		uint64 index = 0;
		for (auto l : list)
		{
			mp_data[index++] = l; 
		}
	}

	void Assign(uint64 startIndex, uint64 count, const T& value)
	{
		uint64 newCount = startIndex + count;
		TNGINE_ASSERT(startIndex <= m_size, "StartIndex must be in the range of the array"); 
		if (newCount > m_size)
		{
			uint64 over = newCount - m_size;
			newCount = m_size - over;
		}

		for (uint64 i = startIndex; i < newCount; ++i)
		{
			mp_data[i] = value;
		}

	};

	void Assign(uint64 startIndex, std::initializer_list<T> list)
	{
		TNGINE_ASSERT(startIndex <= m_size, "StartIndex must be in the range of the array");
		uint64 index = startIndex;
		for (auto l : list)
		{
			if (index >= m_size)
				break;

			mp_data[index++] = l;
		}
	}

	T& At(uint64 index)
	{
		TNGINE_ASSERT(index < m_size, "Out of bounds");
		return mp_data[index];
	}

	bool Empty() const
	{
		return m_size == 0;
	}

	void Erase(uint64 index)
	{
		for (uint64 i = index; i < m_size - 1; ++i)
		{
			mp_data[i] = std::move(mp_data[i + 1]);
		}

		--m_size;
	}
	
	void Erase(uint64 startIndex, uint64 endIndex)
	{
		TNGINE_ASSERT(startIndex <= endIndex, "Invalid range");
		TNGINE_ASSERT(endIndex <= m_size, "Out of bounds");

		uint64 count = endIndex - startIndex;

		for (uint64 i = startIndex; i < m_size - count; ++i)
		{
			mp_data[i] = std::move(mp_data[i + count]);
		}

		m_size -= count;
	}

	void Insert(uint64 index, const T& value)
	{
		TNGINE_ASSERT(index <= m_size, "Index out of bounds");

		if (m_size >= m_capacity)
		{
			uint64 newCapacity = (m_capacity == 0) ? 1 : m_capacity * 2;
			Reserve(newCapacity);
		}

		for (uint64 i = m_size; i > index; --i)
		{
			mp_data[i] = std::move(mp_data[i - 1]);
		}

		mp_data[index] = value;

		++m_size;
	}

	void Insert(uint64 index, T&& value)
	{
		TNGINE_ASSERT(index <= m_size, "Index out of bounds");

		if (m_size >= m_capacity)
		{
			uint64 newCapacity = (m_capacity == 0) ? 1 : m_capacity * 2;
			Reserve(newCapacity);
		}

		for (uint64 i = m_size; i > index; --i)
		{
			mp_data[i] = std::move(mp_data[i - 1]);
		}

		mp_data[index] = std::move(value);

		++m_size;
	}

	void Insert(uint64 index, std::initializer_list<T> list)
	{
		TNGINE_ASSERT(index <= m_size, "Index out of bounds");

		uint64 count = list.size();

		if (m_size + count > m_capacity)
		{
			uint64 newCapacity = std::max(m_capacity * 2, m_size + count);

			if (newCapacity == 0)
				newCapacity = count;

			Reserve(newCapacity);
		}
		 
		for (uint64 i = m_size; i > index; --i)
		{
			mp_data[i + count - 1] = std::move(mp_data[i - 1]);
		}
		 
		uint64 current = index;

		for (const auto& element : list)
		{
			mp_data[current++] = element;
		}

		m_size += count;
	}

	void Clear()
	{
		Erase(0, m_size);
	}

	T PopBack()
	{
		T element = std::move(mp_data[m_size - 1]);
		Erase(m_size - 1);
		return element;
	}

	T PopFront()
	{
		T element = std::move(mp_data[0]);
		Erase(0);
		return element;
	}

	void Swap(DynArray& array)
	{
		std::swap(m_capacity, array.m_capacity);
		std::swap(m_size, array.m_size);
		std::swap(mp_data, array.mp_data);
	}

	void ShrinkToFit()
	{
		if (m_capacity == m_size)
			return;

		T* pNew = new T[m_size];

		for (uint64 i = 0; i < m_size; ++i)
		{
			pNew[i] = std::move(mp_data[i]);
		}

		delete[] mp_data;

		mp_data = pNew;
		m_capacity = m_size;
	}

	bool Contains(const T& value) const
	{
		for (uint64 i = 0; i < m_size; ++i)
		{
			if (mp_data[i] == value)
				return true;
		}

		return false;
	}

	int64 Find(const T& value) const
	{
		for (uint64 i = 0; i < m_size; ++i)
		{
			if (mp_data[i] == value)
				return static_cast<int64>(i);
		}

		return -1;
	}

	bool Remove(const T& value)
	{
		int64 index = Find(value);

		if (index == -1)
			return false;

		Erase(index);

		return true;
	}

	void RemoveAll(const T& value)
	{
		uint64 write = 0;

		for (uint64 read = 0; read < m_size; ++read)
		{
			if (!(mp_data[read] == value))
			{
				mp_data[write++] = std::move(mp_data[read]);
			}
		}

		uint64 removed = m_size - write;
		m_size = write;
	}

	T& operator[](uint64 index)
	{
		return mp_data[index];
	}

	const T& operator[](uint64 index) const
	{
		return mp_data[index];
	}

	DynArray& operator=(const DynArray& other)
	{
		if (this == &other)
			return *this;

		delete[] mp_data;

		m_size = other.m_size;
		m_capacity = other.m_capacity;

		mp_data = new T[m_capacity];

		for (uint64 i = 0; i < m_size; ++i)
			mp_data[i] = other.mp_data[i];

		return *this;
	}

	bool operator==(const DynArray& array)
	{
		if (array.m_size != m_size)
			return false;

		for (uint64 i = 0; i < m_size; ++i)
		{
			if (array[i] != mp_data[i])
				return false;
		}

		return true;
	}

	bool operator!=(const DynArray& array)
	{
		if (array.m_size != m_size)
			return true;

		for (uint64 i = 0; i < m_size; ++i)
		{
			if (array[i] != mp_data[i])
				return true;
		}

		return false;
	}

private:
	uint64 m_size = 0;
	uint64 m_capacity = 0;
	T* mp_data = nullptr;
};
#pragma pop(pack)

#endif // !DYN_ARRAY_H__INCLUDED
