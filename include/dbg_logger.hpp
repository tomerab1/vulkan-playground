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

#define GET_FILENAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define GET_TIMESTAMP []() {                                         \
    auto now = std::chrono::system_clock::now();                     \
    auto time = std::chrono::system_clock::to_time_t(now);           \
    std::ostringstream os;                                           \
    os << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S"); \
    return os.str();                                                 \
}()

template <typename T>
void logStub(const char *lvl, const char *fName, uint32_t fLine, T &&msg)
{
#ifndef NDEBUG
    fmt::println("[{}] [{}{}{}] [{}:{}]: {}", GET_TIMESTAMP, GREEN, lvl, RESET, fName, fLine, msg);
#endif
}

constexpr auto dbglog_info = [](auto &&msg)
{
    logStub("INFO", GET_FILENAME, __LINE__, std::forward<decltype(msg)>(msg));
};

constexpr auto dbglog_warn = [](auto &&msg)
{
    logStub("WARN", GET_FILENAME, __LINE__, std::forward<decltype(msg)>(msg));
};

constexpr auto dbglog_error = [](auto &&msg)
{
    logStub("ERROR", GET_FILENAME, __LINE__, std::forward<decltype(msg)>(msg));
};
