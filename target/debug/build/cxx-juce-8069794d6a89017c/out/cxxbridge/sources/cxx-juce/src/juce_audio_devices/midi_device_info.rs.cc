#include "cxx_juce.h"
#include <cstdint>
#include <new>
#include <type_traits>

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#ifdef __clang__
#pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
#endif // __clang__
#endif // __GNUC__

namespace rust {
inline namespace cxxbridge1 {
// #include "rust/cxx.h"

#ifndef CXXBRIDGE1_RELOCATABLE
#define CXXBRIDGE1_RELOCATABLE
namespace detail {
template <typename... Ts>
struct make_void {
  using type = void;
};

template <typename... Ts>
using void_t = typename make_void<Ts...>::type;

template <typename Void, template <typename...> class, typename...>
struct detect : std::false_type {};
template <template <typename...> class T, typename... A>
struct detect<void_t<T<A...>>, T, A...> : std::true_type {};

template <template <typename...> class T, typename... A>
using is_detected = detect<void, T, A...>;

template <typename T>
using detect_IsRelocatable = typename T::IsRelocatable;

template <typename T>
struct get_IsRelocatable
    : std::is_same<typename T::IsRelocatable, std::true_type> {};
} // namespace detail

template <typename T>
struct IsRelocatable
    : std::conditional<
          detail::is_detected<detail::detect_IsRelocatable, T>::value,
          detail::get_IsRelocatable<T>,
          std::integral_constant<
              bool, std::is_trivially_move_constructible<T>::value &&
                        std::is_trivially_destructible<T>::value>>::type {};
#endif // CXXBRIDGE1_RELOCATABLE
} // namespace cxxbridge1
} // namespace rust

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

static_assert(
    ::rust::IsRelocatable<::juce::MidiDeviceInfo>::value,
    "type juce::MidiDeviceInfo should be trivially move constructible and trivially destructible in C++ to be used as a return value of `midi_device_info_new`, `midi_device_info_clone` in Rust");

namespace cxx_juce {
extern "C" {
void cxx_juce$cxxbridge1$midi_device_info_new(::juce::MidiDeviceInfo *return$) noexcept {
  ::juce::MidiDeviceInfo (*midi_device_info_new$)() = ::cxx_juce::construct;
  new (return$) ::juce::MidiDeviceInfo(midi_device_info_new$());
}

void cxx_juce$cxxbridge1$midi_device_info_clone(::juce::MidiDeviceInfo const &info, ::juce::MidiDeviceInfo *return$) noexcept {
  ::juce::MidiDeviceInfo (*midi_device_info_clone$)(::juce::MidiDeviceInfo const &) = ::cxx_juce::construct;
  new (return$) ::juce::MidiDeviceInfo(midi_device_info_clone$(info));
}

void cxx_juce$cxxbridge1$midi_device_info_array_drop(::juce::MidiDeviceInfoArray &self_) noexcept {
  void (*midi_device_info_array_drop$)(::juce::MidiDeviceInfoArray &) = ::cxx_juce::drop;
  midi_device_info_array_drop$(self_);
}
} // extern "C"
} // namespace cxx_juce

namespace juce {
extern "C" {
::juce::MidiDeviceInfo const *juce$cxxbridge1$MidiDeviceInfoArray$data(::juce::MidiDeviceInfoArray const &self) noexcept {
  ::juce::MidiDeviceInfo const *(::juce::MidiDeviceInfoArray::*data$)() const = &::juce::MidiDeviceInfoArray::getRawDataPointer;
  return (self.*data$)();
}

::std::int32_t juce$cxxbridge1$MidiDeviceInfoArray$len(::juce::MidiDeviceInfoArray const &self) noexcept {
  ::std::int32_t (::juce::MidiDeviceInfoArray::*len$)() const = &::juce::MidiDeviceInfoArray::size;
  return (self.*len$)();
}
} // extern "C"
} // namespace juce
