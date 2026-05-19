#include "Input.h"

#include <cstring>

namespace TNgine
{
	bool Input::s_CurrentKeys[512] = {};
	bool Input::s_PreviousKeys[512] = {};
}

bool TNgine::Input::IsKeyPressed(Key key)
{
	return s_CurrentKeys[static_cast<int>(key)];
}

bool TNgine::Input::IsKeyDown(Key key)
{
	return s_CurrentKeys[(int)key] && !s_PreviousKeys[(int)key];
}

void TNgine::Input::SetKey(Key key, bool pressed)
{
	s_CurrentKeys[static_cast<int>(key)] = pressed;
}

void TNgine::Input::Update()
{
	memcpy(s_PreviousKeys, s_CurrentKeys, sizeof(s_CurrentKeys));
}
