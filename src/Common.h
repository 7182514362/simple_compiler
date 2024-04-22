#pragma once

#include <memory>
#include <source_location>
#include <stdexcept>
#include <string>

template <typename T> using UPtr = std::unique_ptr<T>;
template <typename T> using SPtr = std::shared_ptr<T>;

inline std::string black() { return "\033[30m"; }
inline std::string red() { return "\033[31m"; }
inline std::string green() { return "\033[32m"; }
inline std::string yellow() { return "\033[33m"; }
inline std::string blue() { return "\033[34m"; }
inline std::string magenta() { return "\033[35m"; }
inline std::string cyan() { return "\033[36m"; }
inline std::string white() { return "\033[37m"; }

inline void ThrowRuntimeError(
    const std::string &msg,
    const std::source_location location = std::source_location::current()) {
  throw std::runtime_error(yellow() + "[" + std::string(location.file_name()) +
                           ":" + std::to_string(location.line()) + "]: " + msg);
}

inline void
Assert(bool cond,
       const std::source_location location = std::source_location::current()) {
  if (!cond) {
    ThrowRuntimeError("Assertion Failed", location);
  }
}