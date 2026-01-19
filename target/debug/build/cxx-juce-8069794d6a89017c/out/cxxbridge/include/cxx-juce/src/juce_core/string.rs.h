#pragma once
#include "cxx_juce.h"
#include <cstddef>
#include <cstdint>

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
#endif // __clang__

namespace juce {
  enum class StringLayout : ::std::uint8_t;
  enum class CharPointer_UTF8Layout : ::std::uint8_t;
}

namespace juce {
#ifndef CXXBRIDGE1_ENUM_juce$StringLayout
#define CXXBRIDGE1_ENUM_juce$StringLayout
enum class StringLayout : ::std::uint8_t {
  Size = 8,
  Alignment = 8,
};
#endif // CXXBRIDGE1_ENUM_juce$StringLayout

#ifndef CXXBRIDGE1_ENUM_juce$CharPointer_UTF8Layout
#define CXXBRIDGE1_ENUM_juce$CharPointer_UTF8Layout
enum class CharPointer_UTF8Layout : ::std::uint8_t {
  Size = 8,
  Alignment = 8,
};
#endif // CXXBRIDGE1_ENUM_juce$CharPointer_UTF8Layout
} // namespace juce

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__
