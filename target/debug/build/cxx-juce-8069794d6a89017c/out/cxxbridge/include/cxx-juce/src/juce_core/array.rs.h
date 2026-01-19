#pragma once
#include "cxx_juce.h"
#include <cstdint>

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
#endif // __clang__

namespace juce {
  enum class ArrayLayout : ::std::uint8_t;
  enum class StringArrayLayout : ::std::uint8_t;
}

namespace juce {
#ifndef CXXBRIDGE1_ENUM_juce$ArrayLayout
#define CXXBRIDGE1_ENUM_juce$ArrayLayout
enum class ArrayLayout : ::std::uint8_t {
  Size = 16,
  Alignment = 8,
};
#endif // CXXBRIDGE1_ENUM_juce$ArrayLayout

#ifndef CXXBRIDGE1_ENUM_juce$StringArrayLayout
#define CXXBRIDGE1_ENUM_juce$StringArrayLayout
enum class StringArrayLayout : ::std::uint8_t {
  Size = 16,
  Alignment = 8,
};
#endif // CXXBRIDGE1_ENUM_juce$StringArrayLayout
} // namespace juce

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__
