#pragma once

#ifdef _DEBUG
#define LOGGING
#define ASSERTING
#define TNGINE_ENABLE_PROFILING
#endif // _DEBUG


#ifdef LOGGING

#include "../Logging/Logging.h" 

#define CLOG_INFO(...) TNgine::Core::Log::Instance().Info(LogTarget::CONSOLE_LOG, __VA_ARGS__)
#define CLOG_WARN(...) TNgine::Core::Log::Instance().Warn(LogTarget::CONSOLE_LOG, __VA_ARGS__)
#define CLOG_ERROR(...) TNgine::Core::Log::Instance().Error(LogTarget::CONSOLE_LOG, __VA_ARGS__)

#define FLOG_INFO(...) TNgine::Core::Log::Instance().Info(LogTarget::FILE_LOG, __VA_ARGS__)
#define FLOG_WARN(...) TNgine::Core::Log::Instance().Warn(LogTarget::FILE_LOG, __VA_ARGS__)
#define FLOG_ERROR(...) TNgine::Core::Log::Instance().Error(LogTarget::FILE_LOG, __VA_ARGS__)

#define CFLOG_INFO(...) TNgine::Core::Log::Instance().Info(LogTarget::CONSOLE_FILE_LOG, __VA_ARGS__)
#define CFLOG_WARN(...) TNgine::Core::Log::Instance().Warn(LogTarget::CONSOLE_FILE_LOG, __VA_ARGS__)
#define CFLOG_ERROR(...) TNgine::Core::Log::Instance().Error(LogTarget::CONSOLE_FILE_LOG, __VA_ARGS__)

#define TNGINE_ERROR(msg) CFLOG_ERROR(msg)

#else

#define CLOG_INFO(...)
#define CLOG_WARN(...)
#define CLOG_ERROR(...)

#define FLOG_INFO(msg)
#define FLOG_WARN(msg)
#define FLOG_ERROR(msg)

#define CFLOG_INFO(msg)
#define CFLOG_WARN(msg)
#define CFLOG_ERROR(msg)

#define TNGINE_ERROR(msg)

#endif // LOGGING

#ifdef ASSERTING

#define TNGINE_ASSERT(condition, msg) \
	do { \
		if (!(condition)) { \
			TNGINE_ERROR("Assertion failed: " msg); \
			std::abort(); \
		} \
	} while (false)

#define TNGINE_STATIC_ASSERT(condition, msg) static_assert(condition, "Static assertion failed: " msg)

#else

#define TNGINE_ASSERT(condition, msg)
#define TNGINE_STATIC_ASSERT(condition, msg)

#endif // ASSERTING

#ifdef TNGINE_ENABLE_PROFILING

#define PROFILE_SCOPE(name) \
    ProfileScope __profile_scope(name)

#define PROFILE_TIMEPOINT(label) \
    __profile_scope.TimePoint(label)

#else

#define PROFILE_SCOPE(name)
#define PROFILE_TIMEPOINT(label)

#endif