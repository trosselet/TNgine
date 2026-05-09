#ifndef LOGGING_H__INCLUDED
#define LOGGING_H__INCLUDED

#include <spdlog/spdlog.h>

enum LogTarget
{
	CONSOLE_LOG = 0,
	FILE_LOG = 1,
	CONSOLE_FILE_LOG = 2
};

namespace TNgine
{
	namespace Core
	{
		class Log
		{
		public:
			virtual ~Log() = default;
			void Create(const std::string& filename = "app.log");

			void Info(LogTarget target, const std::string& msg);
			void Warn(LogTarget target, const std::string& msg);
			void Error(LogTarget target, const std::string& msg);

			static Log& Instance();
		private:

			std::shared_ptr<spdlog::logger> m_FileLogger;
			std::shared_ptr<spdlog::logger> m_ConsoleLogger;
			std::shared_ptr<spdlog::logger> m_ConsoleFileLogger;
		};
	}
}


#endif // !LOGGING_H__INCLUDED
