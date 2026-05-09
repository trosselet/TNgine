#include "Logging.h"

#include <vector>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h> 

void TNgine::Core::Log::Create(const std::string& filename)
{
	std::vector<spdlog::sink_ptr> sinks;

	{
		sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());

		m_ConsoleLogger = std::make_shared<spdlog::logger>("console_logger", sinks.begin(), sinks.end());

		spdlog::register_logger(m_ConsoleLogger);
		sinks.clear();
	}

	{
		sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(filename, true));

		m_FileLogger = std::make_shared<spdlog::logger>("file_logger", sinks.begin(), sinks.end());

		spdlog::register_logger(m_FileLogger);
		sinks.clear();
	}

	{
		sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(filename, true));

		m_ConsoleFileLogger = std::make_shared<spdlog::logger>("consolefile_logger", sinks.begin(), sinks.end());

		spdlog::register_logger(m_ConsoleFileLogger);
	}

}

void TNgine::Core::Log::Info(LogTarget target, const std::string& msg)
{ 

	switch (target)
	{
		case LogTarget::CONSOLE_LOG:
		{ 
			m_ConsoleLogger->info(msg);
			break;
		}
		case LogTarget::FILE_LOG:
		{
			m_FileLogger->info(msg);
			break;
		}
		case LogTarget::CONSOLE_FILE_LOG:
		{
			m_ConsoleFileLogger->info(msg);
			break;
		}
	}
}

void TNgine::Core::Log::Warn(LogTarget target, const std::string& msg)
{ 

	switch (target)
	{
	case LogTarget::CONSOLE_LOG:
	{
		m_ConsoleLogger->warn(msg);
		break;
	}
	case LogTarget::FILE_LOG:
	{
		m_FileLogger->warn(msg);
		break;
	}
	case LogTarget::CONSOLE_FILE_LOG:
	{
		m_ConsoleFileLogger->warn(msg);
		break;
	}
	}
}

void TNgine::Core::Log::Error(LogTarget target, const std::string& msg)
{ 

	switch (target)
	{
	case LogTarget::CONSOLE_LOG:
	{
		m_ConsoleLogger->error(msg);
		break;
	}
	case LogTarget::FILE_LOG:
	{
		m_FileLogger->error(msg);
		break;
	}
	case LogTarget::CONSOLE_FILE_LOG:
	{
		m_ConsoleFileLogger->error(msg);
		break;
	}
	}
}

TNgine::Core::Log& TNgine::Core::Log::Instance()
{
	static Log instance;
	return instance;
}
