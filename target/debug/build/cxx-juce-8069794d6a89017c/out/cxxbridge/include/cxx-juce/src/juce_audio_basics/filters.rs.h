#pragma once
#include "cxx_juce.h"
#include <cstdint>

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
#endif // __clang__

namespace juce {
  enum class IIRCoefficientsLayout : ::std::uint8_t;
  enum class SingleThreadedIIRFilterLayout : ::std::uint8_t;
}

namespace juce {
#ifndef CXXBRIDGE1_ENUM_juce$IIRCoefficientsLayout
#define CXXBRIDGE1_ENUM_juce$IIRCoefficientsLayout
enum class IIRCoefficientsLayout : ::std::uint8_t {
  Size = 20,
  Alignment = 4,
};
#endif // CXXBRIDGE1_ENUM_juce$IIRCoefficientsLayout

#ifndef CXXBRIDGE1_ENUM_juce$SingleThreadedIIRFilterLayout
#define CXXBRIDGE1_ENUM_juce$SingleThreadedIIRFilterLayout
enum class SingleThreadedIIRFilterLayout : ::std::uint8_t {
  Size = 36,
  Alignment = 4,
};
#endif // CXXBRIDGE1_ENUM_juce$SingleThreadedIIRFilterLayout
} // namespace juce

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__
