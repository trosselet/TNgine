#ifndef LOGGING_H__INCLUDED
#define LOGGING_H__INCLUDED

#include <memory>

#include <spdlog/spdlog.h>

enum class LogTarget
{
    CONSOLE_LOG,
    FILE_LOG,
    CONSOLE_FILE_LOG
};

namespace TNgine::Core
{
    class Log
    {
    public:

        void Create(const std::string& filename = "TNgine.log");

        template<typename... Args>
        void Info(LogTarget target, spdlog::format_string_t<Args...> fmt, Args&&... args);

        template<typename... Args>
        void Warn(LogTarget target, spdlog::format_string_t<Args...> fmt, Args&&... args);

        template<typename... Args>
        void Error(LogTarget target, spdlog::format_string_t<Args...> fmt, Args&&... args);

        static Log& Instance();

    private:

        std::shared_ptr<spdlog::logger> m_ConsoleLogger;
        std::shared_ptr<spdlog::logger> m_FileLogger;
        std::shared_ptr<spdlog::logger> m_ConsoleFileLogger;
    };
}

namespace TNgine::Core
{
    template<typename... Args>
    void Log::Info(LogTarget target, spdlog::format_string_t<Args...> fmt, Args&&... args)
    {
        switch (target)
        {
        case LogTarget::CONSOLE_LOG:
            m_ConsoleLogger->info(fmt, std::forward<Args>(args)...);
            break;

        case LogTarget::FILE_LOG:
            m_FileLogger->info(fmt, std::forward<Args>(args)...);
            break;

        case LogTarget::CONSOLE_FILE_LOG:
            m_ConsoleFileLogger->info(fmt, std::forward<Args>(args)...);
            break;
        }
    }

    template<typename... Args>
    void Log::Warn(LogTarget target, spdlog::format_string_t<Args...> fmt, Args&&... args)
    {
        switch (target)
        {
        case LogTarget::CONSOLE_LOG:
            m_ConsoleLogger->warn(fmt, std::forward<Args>(args)...);
            break;

        case LogTarget::FILE_LOG:
            m_FileLogger->warn(fmt, std::forward<Args>(args)...);
            break;

        case LogTarget::CONSOLE_FILE_LOG:
            m_ConsoleFileLogger->warn(fmt, std::forward<Args>(args)...);
            break;
        }
    }

    template<typename... Args>
    void Log::Error(LogTarget target, spdlog::format_string_t<Args...> fmt, Args&&... args)
    {
        switch (target)
        {
        case LogTarget::CONSOLE_LOG:
            m_ConsoleLogger->error(fmt, std::forward<Args>(args)...);
            break;

        case LogTarget::FILE_LOG:
            m_FileLogger->error(fmt, std::forward<Args>(args)...);
            break;

        case LogTarget::CONSOLE_FILE_LOG:
            m_ConsoleFileLogger->error(fmt, std::forward<Args>(args)...);
            break;
        }
    }
}


#endif // !LOGGING_H__INCLUDED
