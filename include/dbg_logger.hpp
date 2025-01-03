#pragma once

#include <fmt/format.h>
#include <string.h>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <ctime>

static constexpr const char *RESET = "\033[1m\033[0m";
static constexpr const char *GREEN = "\033[1m\033[32m";
static constexpr const char *YELLOW = "\033[1m\033[33m";
static constexpr const char *RED = "\033[1m\033[31m";

inline const char* getFileName(const char *fName)
{
    return strrchr(fName, '/') ? strrchr(fName, '/') + 1 : 
           strrchr(fName, '\\') ? strrchr(fName, '\\') + 1 : fName;
};

inline std::string getTimestamp()
{
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::ostringstream os;
    os << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    return os.str();
};

template <typename... Args>
void logStub(const char *lvl, const char *color, const char *fName, uint32_t fLine, const char *fmt, Args &&...msg)
{
#ifndef NDEBUG
    fmt::print("[{}] [{}{}{}] [{}:{}]: ", getTimestamp(), color, lvl, RESET, fName, fLine);
    fmt::println(fmt, std::forward<Args>(msg)...);
#endif
}

template <typename... Args>
inline void dbglog_info(const char *fName, uint32_t line, const char *fmt, Args &&...msg)
{
    logStub("INFO", GREEN, getFileName(fName), line, fmt, std::forward<Args>(msg)...);
}

template <typename... Args>
inline void dbglog_warn(const char *fName, uint32_t line, const char *fmt, Args &&...msg)
{
    logStub("WARN", YELLOW, getFileName(fName), line, fmt, std::forward<Args>(msg)...);
}

template <typename... Args>
inline void dbglog_error(const char *fName, uint32_t line, const char *fmt, Args &&...msg)
{
    logStub("ERROR", RED, getFileName(fName), line, fmt, std::forward<Args>(msg)...);
}

#define dbglog_info(fmt, ...) dbglog_info(__FILE__, __LINE__, fmt, __VA_ARGS__)
#define dbglog_warn(fmt, ...) dbglog_warn(__FILE__, __LINE__, fmt, __VA_ARGS__)
#define dbglog_error(fmt, ...) dbglog_error(__FILE__, __LINE__, fmt, __VA_ARGS__)