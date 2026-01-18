#pragma once
#include "cxx_juce.h"
#include <cstdint>
#include <memory>

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
#endif // __clang__

namespace juce {
  enum class AudioDeviceSetupLayout : ::std::uint8_t;
  using AudioDeviceManager = ::juce::AudioDeviceManager;
  using XmlElement = ::juce::XmlElement;
  using AudioIODeviceTypeArray = ::juce::AudioIODeviceTypeArray;
}

namespace juce {
#ifndef CXXBRIDGE1_ENUM_juce$AudioDeviceSetupLayout
#define CXXBRIDGE1_ENUM_juce$AudioDeviceSetupLayout
enum class AudioDeviceSetupLayout : ::std::uint8_t {
  Size = 128,
  Alignment = 8,
  OutputDeviceNameOffset = 0,
  InputDeviceNameOffset = 8,
  SampleRateOffset = 16,
  BufferSizeOffset = 24,
  InputChannelsOffset = 32,
  UseDefaultInputChannelsOffset = 72,
  OutputChannelsOffset = 80,
  UseDefaultOutputChannelsOffset = 120,
};
#endif // CXXBRIDGE1_ENUM_juce$AudioDeviceSetupLayout
} // namespace juce

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__
