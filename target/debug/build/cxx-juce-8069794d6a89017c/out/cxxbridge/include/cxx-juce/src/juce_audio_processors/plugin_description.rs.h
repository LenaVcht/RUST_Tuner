#pragma once
#include "cxx_juce.h"
#include <cstdint>
#include <memory>

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
#endif // __clang__

namespace juce {
  enum class PluginDescriptionLayout : ::std::uint8_t;
}

namespace juce {
#ifndef CXXBRIDGE1_ENUM_juce$PluginDescriptionLayout
#define CXXBRIDGE1_ENUM_juce$PluginDescriptionLayout
enum class PluginDescriptionLayout : ::std::uint8_t {
  Size = 96,
  Alignment = 8,
  NameOffset = 0,
  DescriptiveNameOffset = 8,
  PluginFormatNameOffset = 16,
  CategoryOffset = 24,
  ManufacturerNameOffset = 32,
  VersionOffset = 40,
  FileOrIdentifierOffset = 48,
  LastFileModTimeOffset = 56,
  LastInfoUpdateTimeOffset = 64,
  DeprecatedUidOffset = 72,
  UniqueIdOffset = 76,
  IsInstrumentOffset = 80,
  NumInputChannelsOffset = 84,
  NumOutputChannelsOffset = 88,
  HasSharedContainerOffset = 92,
  HasAraExtensionOffset = 93,
};
#endif // CXXBRIDGE1_ENUM_juce$PluginDescriptionLayout
} // namespace juce

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__
