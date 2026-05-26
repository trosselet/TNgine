#ifndef ATOMIC_H__INCLUDED
#define ATOMIC_H__INCLUDED

#include <atomic>

namespace TNgine
{
	template<typename T>
	using Atomic = std::atomic<T>;
}


#endif //!ATOMIC_H__INCLUDED