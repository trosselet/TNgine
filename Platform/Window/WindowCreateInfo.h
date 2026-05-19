#ifndef WINDOW_CREATE_INFO_H__INCLUDED
#define WINDOW_CREATE_INFO_H__INCLUDED

#include <Core/include.h>

namespace TNgine
{
	struct WindowCreateInfo
	{
		WindowCreateInfo(const char* title = "TNgine Window", uint32 width = 800, uint32 height = 600, bool vSync = true, bool fullScreen = false, bool resizable = true, uint32 monitorIndex = 0, const char* iconPath = "")
			: Title(title), Width(width), Height(height), VSync(vSync), FullScreen(fullScreen), Resizable(resizable), MonitorIndex(monitorIndex), IconPath(iconPath)
		{
		}
		const char* Title;
		uint32 Width;
		uint32 Height;
		bool VSync;
		bool FullScreen;
		bool Resizable;
		uint32 MonitorIndex;
		const char* IconPath;
	};
}



#endif // !WINDOW_CREATE_INFO_H__INCLUDED