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

TNgine::Core::Log& TNgine::Core::Log::Instance()
{
	static Log instance;
	return instance;
}
