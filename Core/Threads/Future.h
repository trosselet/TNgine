#ifndef FUTURE_H__INCLUDED
#define FUTURE_H__INCLUDED

#include <future>

namespace TNgine
{
	template<typename T>
	using Future = std::future<T>;
}

#endif // !FUTURE_H__INCLUDED