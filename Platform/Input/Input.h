#ifndef INPUT_H__INCLUDED
#define INPUT_H__INCLUDED

#include "KeyCode.h"

namespace TNgine
{
	class Input
	{
	public:

		static bool IsKeyPressed(Key key);
		static bool IsKeyDown(Key key);

		static void SetKey(Key key, bool pressed);

		static void Update();

	private:

		static bool s_CurrentKeys[512];
		static bool s_PreviousKeys[512];
	};
}

#endif // !INPUT_H__INCLUDED