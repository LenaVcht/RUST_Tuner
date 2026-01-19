#pragma once
#include "cxx_juce.h"
#include <cstdint>

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
#endif // __clang__

namespace juce {
  enum class BigIntegerLayout : ::std::uint8_t;
}

namespace juce {
#ifndef CXXBRIDGE1_ENUM_juce$BigIntegerLayout
#define CXXBRIDGE1_ENUM_juce$BigIntegerLayout
enum class BigIntegerLayout : ::std::uint8_t {
  Size = 40,
  Alignment = 8,
};
#endif // CXXBRIDGE1_ENUM_juce$BigIntegerLayout
} // namespace juce

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__
