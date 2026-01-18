#pragma once
#include "cxx_juce.h"
#include <cstdint>

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
#endif // __clang__

namespace juce {
  enum class MidiDeviceInfoLayout : ::std::uint8_t;
}

namespace juce {
#ifndef CXXBRIDGE1_ENUM_juce$MidiDeviceInfoLayout
#define CXXBRIDGE1_ENUM_juce$MidiDeviceInfoLayout
enum class MidiDeviceInfoLayout : ::std::uint8_t {
  Size = 16,
  Alignment = 8,
  NameOffset = 0,
  IdentifierOffset = 8,
};
#endif // CXXBRIDGE1_ENUM_juce$MidiDeviceInfoLayout
} // namespace juce

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__
