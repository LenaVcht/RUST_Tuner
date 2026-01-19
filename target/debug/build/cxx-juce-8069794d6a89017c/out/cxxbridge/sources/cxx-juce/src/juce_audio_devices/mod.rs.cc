#include "cxx_juce.h"

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#ifdef __clang__
#pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
#endif // __clang__
#endif // __GNUC__

namespace juce {
  using SystemAudioVolume = ::juce::SystemAudioVolume;
}

namespace juce {
extern "C" {
bool juce$cxxbridge1$SystemAudioVolume$set_muted(bool muted) noexcept {
  bool (*set_muted$)(bool) = &::juce::SystemAudioVolume::setMuted;
  return set_muted$(muted);
}

bool juce$cxxbridge1$SystemAudioVolume$is_muted() noexcept {
  bool (*is_muted$)() = &::juce::SystemAudioVolume::isMuted;
  return is_muted$();
}

bool juce$cxxbridge1$SystemAudioVolume$set_gain(float gain) noexcept {
  bool (*set_gain$)(float) = &::juce::SystemAudioVolume::setGain;
  return set_gain$(gain);
}

float juce$cxxbridge1$SystemAudioVolume$get_gain() noexcept {
  float (*get_gain$)() = &::juce::SystemAudioVolume::getGain;
  return get_gain$();
}
} // extern "C"
} // namespace juce
