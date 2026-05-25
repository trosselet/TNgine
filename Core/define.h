#pragma once

/*------------------OS------------------*/
#ifdef __linux__
	#define TNGINE_OS_LINUX

#elif _WIN32
	#define TNGINE_OS_WINDOWS

#elif __APPLE__
	#define TNGINE_OS_MAC

#elif
	#error "Unsupported platform!"

#endif
/*--------------------------------------*/

/*-------------Windowing API------------*/
#define TNGINE_WINDOW_GLFW
/*--------------------------------------*/