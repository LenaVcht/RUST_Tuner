#include "cxx_juce.h"

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#ifdef __clang__
#pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
#endif // __clang__
#endif // __GNUC__

namespace juce {
extern "C" {
void juce$cxxbridge1$initialise_juce() noexcept {
  void (*initialise_juce$)() = ::juce::initialiseJuce_GUI;
  initialise_juce$();
}

void juce$cxxbridge1$shutdown_juce() noexcept {
  void (*shutdown_juce$)() = ::juce::shutdownJuce_GUI;
  shutdown_juce$();
}

void juce$cxxbridge1$initialise_ns_application() noexcept {
  void (*initialise_ns_application$)() = ::juce::initialiseNSApplication;
  initialise_ns_application$();
}
} // extern "C"
} // namespace juce
