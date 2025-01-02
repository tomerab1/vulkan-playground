#pragma once

#include <fmt/format.h>
#include <string.h>
#include <chrono>
#include <ctime>

#define RESET "\033[1m\033[0m"
#define GREEN "\033[1m\033[32m"
#define YELLOW "\033[1m\033[33m"
#define RED "\033[1m\033[31m"

#define GET_FILENAME (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define GET_TIMESTAMP []() {                                                 \
    auto now = std::chrono::system_clock::now();                             \
    auto time = std::chrono::system_clock::to_time_t(now);                   \
    char buffer[20];                                                         \
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&time)); \
    return std::string(buffer);                                              \
}()

#define APP_INFO(msg) fmt::println("[{}] [{}INFO{}] [{}:{}]: {}", GET_TIMESTAMP, GREEN, RESET, GET_FILENAME, __LINE__, msg)

#define APP_WARN(msg) fmt::println("[{}] [{}WARN{}] [{}:{}]: {}", GET_TIMESTAMP, YELLOW, RESET, GET_FILENAME, __LINE__, msg)
#define APP_ERROR(msg) fmt::println("[{}] [{}ERROR{}] [{}:{}]: {}", GET_TIMESTAMP, RED, RESET, GET_FILENAME, __LINE__, msg)
