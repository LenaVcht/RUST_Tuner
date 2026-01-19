#pragma once
#include "cxx_juce.h"
#include <cstdint>

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
#endif // __clang__

namespace juce {
  enum class MidiBufferLayout : ::std::uint8_t;
  enum class MidiMessageLayout : ::std::uint8_t;
  enum class MidiFileLayout : ::std::uint8_t;
}

namespace juce {
#ifndef CXXBRIDGE1_ENUM_juce$MidiBufferLayout
#define CXXBRIDGE1_ENUM_juce$MidiBufferLayout
enum class MidiBufferLayout : ::std::uint8_t {
  Size = 16,
  Alignment = 8,
};
#endif // CXXBRIDGE1_ENUM_juce$MidiBufferLayout

#ifndef CXXBRIDGE1_ENUM_juce$MidiMessageLayout
#define CXXBRIDGE1_ENUM_juce$MidiMessageLayout
enum class MidiMessageLayout : ::std::uint8_t {
  Size = 24,
  Alignment = 8,
};
#endif // CXXBRIDGE1_ENUM_juce$MidiMessageLayout

#ifndef CXXBRIDGE1_ENUM_juce$MidiFileLayout
#define CXXBRIDGE1_ENUM_juce$MidiFileLayout
enum class MidiFileLayout : ::std::uint8_t {
  Size = 24,
  Alignment = 8,
};
#endif // CXXBRIDGE1_ENUM_juce$MidiFileLayout
} // namespace juce

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__
