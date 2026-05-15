#ifndef HASH_MAP_H__INCLUDED
#define HASH_MAP_H__INCLUDED

#include "DynArray.hpp"

namespace TNgine
{

	template<typename HashMap>
	class HashMapIterator
	{
	public:
		using ValueType = typename HashMap::ValueType;
		using PointerType = ValueType*;
		using ReferenceType = ValueType&;

	public:

		HashMapIterator(HashMap* pMap, uint64 bucketIndex, uint64 elementIndex) : mp_map(pMap), m_bucketIndex(bucketIndex), m_elementIndex(elementIndex)
		{
			_SkipEmptyBuckets();
		}

		ReferenceType operator*()
		{
			return mp_map->m_buckets[m_bucketIndex][m_elementIndex];
		}

		PointerType operator->()
		{
			return &mp_map->m_buckets[m_bucketIndex][m_elementIndex];
		}

		HashMapIterator& operator++()
		{
			++m_elementIndex;

			if (m_bucketIndex > mp_map->m_buckets.Size())
				return *this;

			auto& bucket = mp_map->m_buckets[m_bucketIndex];

			if (m_elementIndex >= bucket.Size())
			{
				++m_bucketIndex;
				m_elementIndex = 0;

				_SkipEmptyBuckets();
			}

			return *this;
		}

		HashMapIterator operator++(int)
		{
			HashMapIterator temp = *this;
			++(*this);
			return temp;
		}

		bool operator==(const HashMapIterator& other) const
		{
			return
				mp_map == other.mp_map &&
				m_bucketIndex == other.m_bucketIndex &&
				m_elementIndex == other.m_elementIndex;
		}

		bool operator!=(const HashMapIterator& other) const
		{
			return !(*this == other);
		}

	private:

		void _SkipEmptyBuckets()
		{
			while (m_bucketIndex < mp_map->m_buckets.Size() && mp_map->m_buckets[m_bucketIndex].Empty())
			{
				++m_bucketIndex;
			}
		}

	private:
		HashMap* mp_map = nullptr;

		uint64 m_bucketIndex = 0;
		uint64 m_elementIndex = 0;

	};



	template<typename KeyType, typename MappedType>
	struct Pair
	{
		KeyType first;
		MappedType second;

		Pair() = default;

		Pair(const KeyType& k, const MappedType& v) : first(k), second(v)
		{
		}
	};


	template<typename Key, typename T>
	class HashMap
	{
	public:
		using KeyType = Key;
		using MappedType = T;
		using ValueType = Pair<KeyType, MappedType>;
		using Iterator = HashMapIterator<HashMap<KeyType, MappedType>>;

	public:
		HashMap()
		{
			m_buckets.Resize(16);
		}

		HashMap(HashMap&& other) noexcept : m_buckets(std::move(other.m_buckets)), m_size(std::move(other.m_size))
		{ 
		}

		uint64 Size() const
		{
			return m_size;
		}

		uint64 BucketCount() const
		{
			return m_buckets.Size();
		}

		float LoadFactor() const
		{
			return static_cast<float>(m_size) / m_buckets.Size();
		}

		void Insert(const KeyType& key, const MappedType& value)
		{
			uint64 bucketNumber = _BaseHash(key);

			auto& bucket = m_buckets[bucketNumber];

			for (auto& pair : bucket)
			{
				if (pair.first == key)
				{
					pair.second = value;
					return;
				}
			}

			bucket.PushBack({ key, value });
			m_size++;

			_CheckReHash();
		}

		MappedType* Find(const KeyType& key)
		{
			uint64 bucketNumber = _BaseHash(key);

			auto& bucket = m_buckets[bucketNumber];

			for (auto& pair : bucket)
			{
				if (pair.first == key)
					return &pair.second;
			}

			return nullptr;
		}

		bool Remove(const KeyType& key)
		{
			uint64 bucketNumber = _BaseHash(key);

			auto& bucket = m_buckets[bucketNumber];

			for (uint64 i = 0; i < bucket.Size(); ++i)
			{
				if (bucket[i].first == key)
				{
					bucket.Erase(i);
					m_size--;
					return true;
				}
			}

			return false;
		}

		bool Contains(const KeyType& key)
		{ 
			uint64 bucketNumber = _BaseHash(key);

			auto& bucket = m_buckets[bucketNumber];

			for (const auto& pair : bucket)
			{
				if (pair.first == key)
					return true;
			}

			return false;
		}

		void Rehash(uint64 numberOfBucket)
		{
			auto tempBucket = m_buckets;

			m_buckets.Clear();
			m_size = 0;
			m_buckets.Resize(numberOfBucket);

			for (auto& bucket : tempBucket)
			{
				for (auto& pair : bucket)
				{
					Insert(pair.first, pair.second);
				}
			} 
		}

		Iterator begin()
		{
			return Iterator(this, 0, 0);
		}

		Iterator end()
		{
			return Iterator(this, m_buckets.Size(), 0);
		}

		MappedType& operator[](const KeyType& key)
		{
			MappedType* value = Find(key);

			if (value)
				return *value;

			Insert(key, MappedType{});

			return *Find(key);
		}

	private:
		uint64 _BaseHash(const KeyType& key) const 
		{
			uint64 hash = std::hash<KeyType>{}(key);
			uint64 bucketNumber = hash % m_buckets.Size();
			return bucketNumber;
		}

		void _CheckReHash()
		{
			if ((static_cast<float>(m_size) / m_buckets.Size()) > 0.75f)
			{
				Rehash(m_buckets.Size() * 2);
			}
		}

	private:
		DynArray<DynArray<ValueType>> m_buckets;
		uint64 m_size = 0;

	private:
		friend class HashMapIterator<HashMap<Key, T>>;
	};
}


#endif // !HASH_MAP_H__INCLUDED
