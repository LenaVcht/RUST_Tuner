#include "cxx_juce.h"
#include <cstdint>

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#ifdef __clang__
#pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
#endif // __clang__
#endif // __GNUC__

namespace juce {
  using AudioSampleBuffer = ::juce::AudioSampleBuffer;
}

namespace cxx_juce {
extern "C" {
::std::int32_t cxx_juce$cxxbridge1$AudioSampleBuffer$get_num_channels(::juce::AudioSampleBuffer const &self) noexcept {
  ::std::int32_t (::juce::AudioSampleBuffer::*get_num_channels$)() const = &::juce::AudioSampleBuffer::getNumChannels;
  return (self.*get_num_channels$)();
}

::std::int32_t cxx_juce$cxxbridge1$AudioSampleBuffer$get_num_samples(::juce::AudioSampleBuffer const &self) noexcept {
  ::std::int32_t (::juce::AudioSampleBuffer::*get_num_samples$)() const = &::juce::AudioSampleBuffer::getNumSamples;
  return (self.*get_num_samples$)();
}

float const *cxx_juce$cxxbridge1$AudioSampleBuffer$get_read_pointer(::juce::AudioSampleBuffer const &self, ::std::int32_t channel) noexcept {
  float const *(::juce::AudioSampleBuffer::*get_read_pointer$)(::std::int32_t) const = &::juce::AudioSampleBuffer::getReadPointer;
  return (self.*get_read_pointer$)(channel);
}

float *cxx_juce$cxxbridge1$AudioSampleBuffer$get_write_pointer(::juce::AudioSampleBuffer &self, ::std::int32_t channel) noexcept {
  float *(::juce::AudioSampleBuffer::*get_write_pointer$)(::std::int32_t) = &::juce::AudioSampleBuffer::getWritePointer;
  return (self.*get_write_pointer$)(channel);
}

void cxx_juce$cxxbridge1$AudioSampleBuffer$clear(::juce::AudioSampleBuffer &self) noexcept {
  void (::juce::AudioSampleBuffer::*clear$)() = &::juce::AudioSampleBuffer::clear;
  (self.*clear$)();
}
} // extern "C"
} // namespace cxx_juce
