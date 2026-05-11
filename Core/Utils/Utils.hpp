#pragma once

#include "../Logging/Logging.h"

#define CLOG_INFO(msg) TNgine::Core::Log::Instance().Info(LogTarget::CONSOLE_LOG, msg)
#define CLOG_WARN(msg) TNgine::Core::Log::Instance().Warn(LogTarget::CONSOLE_LOG, msg)
#define CLOG_ERROR(msg) TNgine::Core::Log::Instance().Error(LogTarget::CONSOLE_LOG, msg)

#define FLOG_INFO(msg) TNgine::Core::Log::Instance().Info(LogTarget::FILE_LOG, msg)
#define FLOG_WARN(msg) TNgine::Core::Log::Instance().Warn(LogTarget::FILE_LOG, msg)
#define FLOG_ERROR(msg) TNgine::Core::Log::Instance().Error(LogTarget::FILE_LOG, msg)

#define CFLOG_INFO(msg) TNgine::Core::Log::Instance().Info(LogTarget::CONSOLE_FILE_LOG, msg)
#define CFLOG_WARN(msg) TNgine::Core::Log::Instance().Warn(LogTarget::CONSOLE_FILE_LOG, msg)
#define CFLOG_ERROR(msg) TNgine::Core::Log::Instance().Error(LogTarget::CONSOLE_FILE_LOG, msg)

#define TNGINE_ERROR(msg) CFLOG_ERROR(msg)

#define TNGINE_ASSERT(condition, msg) \
	do { \
		if (!(condition)) { \
			TNGINE_ERROR("Assertion failed: " msg); \
			std::abort(); \
		} \
	} while (false)

#define TNGINE_STATIC_ASSERT(condition, msg) static_assert(condition, "Static assertion failed: " msg)