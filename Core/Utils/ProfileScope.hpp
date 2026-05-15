#pragma once

#include <chrono>

#include "Utils.hpp"

class ProfileScope
{
public:
    using Clock = std::chrono::steady_clock;

    explicit ProfileScope(const char* name) : m_name(name), m_start(Clock::now()), m_last(m_start)
    {
    }

    ~ProfileScope()
    {
        const double total = std::chrono::duration<double, std::milli>(Clock::now() - m_start).count();

        CLOG_INFO("[{}] Total : {:.3f} ms", m_name, total);
    }

    inline void TimePoint(const char* label)
    {
        const auto now = Clock::now();

        const double total = std::chrono::duration<double, std::milli>(now - m_start).count();

        const double delta = std::chrono::duration<double, std::milli>(now - m_last).count();

        CLOG_INFO("[{}] {} : {:.3f} ms (delta: {:.3f} ms)", m_name, label, total, delta);

        m_last = now;
    }

private:
    const char* m_name;
    Clock::time_point m_start;
    Clock::time_point m_last;
};