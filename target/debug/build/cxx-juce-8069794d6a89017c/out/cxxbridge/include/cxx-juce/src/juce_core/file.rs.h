#pragma once
#include "cxx_juce.h"
#include <cstdint>

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
#endif // __clang__

namespace juce {
  enum class FileLayout : ::std::uint8_t;
  enum class FileSearchPathLayout : ::std::uint8_t;
}

namespace juce {
#ifndef CXXBRIDGE1_ENUM_juce$FileLayout
#define CXXBRIDGE1_ENUM_juce$FileLayout
enum class FileLayout : ::std::uint8_t {
  Size = 8,
  Alignment = 8,
};
#endif // CXXBRIDGE1_ENUM_juce$FileLayout

#ifndef CXXBRIDGE1_ENUM_juce$FileSearchPathLayout
#define CXXBRIDGE1_ENUM_juce$FileSearchPathLayout
enum class FileSearchPathLayout : ::std::uint8_t {
  Size = 16,
  Alignment = 8,
};
#endif // CXXBRIDGE1_ENUM_juce$FileSearchPathLayout
} // namespace juce

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__
