#include "UUID.h"
#include <random>

static std::random_device s_RandomDevice;
static std::mt19937_64 s_Engine(s_RandomDevice());
static std::uniform_int_distribution<uint64_t> s_Distribution;


TNgine::Core::UUID::UUID() : m_ID(s_Distribution(s_Engine))
{
}

TNgine::Core::UUID::UUID(uint64 id) m_ID(id)
{

}

uint64 TNgine::Core::UUID::GetID() const
{
	return m_ID;
}

bool TNgine::Core::UUID::operator==(const UUID& other) const
{
	return m_ID == other;
}

bool TNgine::Core::UUID::operator!=(const UUID& other) const
{
	return m_ID != other;
}

TNgine::Core::UUID::operator uint64() const
{
	return m_ID
}
