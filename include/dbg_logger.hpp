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

constexpr auto getFileName = [](const char *fName)
{
    return strrchr(fName, '/') ? strrchr(fName, '/') + 1 : fName;
};

constexpr auto getTimestamp = []()
{
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::ostringstream os;
    os << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
    return os.str();
};

template <typename T>
void logStub(const char *lvl, const char *fName, uint32_t fLine, T &&msg)
{
#ifndef NDEBUG
    fmt::println("[{}] [{}{}{}] [{}:{}]: {}", getTimestamp(), GREEN, lvl, RESET, fName, fLine, msg);
#endif
}

constexpr auto dbglog_info = [](auto &&msg, const char *fName)
{
    logStub("INFO", getFileName(fName), __LINE__, std::forward<decltype(msg)>(msg));
};

constexpr auto dbglog_warn = [](auto &&msg, const char *fName)
{
    logStub("WARN", getFileName(fName), __LINE__, std::forward<decltype(msg)>(msg));
};

constexpr auto dbglog_error = [](auto &&msg, const char *fName)
{
    logStub("ERROR", getFileName(fName), __LINE__, std::forward<decltype(msg)>(msg));
};

#define dbglog_info(msg) dbglog_info(msg, __FILE__)
#define dbglog_warn(msg) dbglog_warn(msg, __FILE__)
#define dbglog_error(msg) dbglog_error(msg, __FILE__)