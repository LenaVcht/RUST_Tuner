#pragma once
#include "cxx_juce.h"
#include <cstdint>

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
#endif // __clang__

namespace juce {
  enum class TimeLayout : ::std::uint8_t;
}

namespace juce {
#ifndef CXXBRIDGE1_ENUM_juce$TimeLayout
#define CXXBRIDGE1_ENUM_juce$TimeLayout
enum class TimeLayout : ::std::uint8_t {
  Size = 8,
  Alignment = 8,
};
#endif // CXXBRIDGE1_ENUM_juce$TimeLayout
} // namespace juce

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__
