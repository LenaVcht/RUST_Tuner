#include "cxx_juce.h"
#include <cstddef>
#include <cstdint>
#include <memory>
#include <new>
#include <type_traits>
#include <utility>

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#ifdef __clang__
#pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
#endif // __clang__
#endif // __GNUC__

namespace rust {
inline namespace cxxbridge1 {
// #include "rust/cxx.h"

#ifndef CXXBRIDGE1_IS_COMPLETE
#define CXXBRIDGE1_IS_COMPLETE
namespace detail {
namespace {
template <typename T, typename = std::size_t>
struct is_complete : std::false_type {};
template <typename T>
struct is_complete<T, decltype(sizeof(T))> : std::true_type {};
} // namespace
} // namespace detail
#endif // CXXBRIDGE1_IS_COMPLETE

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

namespace {
template <bool> struct deleter_if {
  template <typename T> void operator()(T *) {}
};
template <> struct deleter_if<true> {
  template <typename T> void operator()(T *ptr) { ptr->~T(); }
};
} // namespace
} // namespace cxxbridge1
} // namespace rust

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

static_assert(
    ::rust::IsRelocatable<::juce::JuceString>::value,
    "type juce::JuceString should be trivially move constructible and trivially destructible in C++ to be used as a return value of `initialise`, `set_audio_device_setup` in Rust");
static_assert(
    ::rust::IsRelocatable<::juce::AudioDeviceSetup>::value,
    "type juce::AudioDeviceSetup should be trivially move constructible and trivially destructible in C++ to be used as a return value of `audio_device_setup_new`, `get_audio_device_setup` in Rust");

namespace cxx_juce {
extern "C" {
void cxx_juce$cxxbridge1$audio_device_setup_new(::juce::AudioDeviceSetup *return$) noexcept {
  ::juce::AudioDeviceSetup (*audio_device_setup_new$)() = ::cxx_juce::construct;
  new (return$) ::juce::AudioDeviceSetup(audio_device_setup_new$());
}

::juce::AudioDeviceManager *cxx_juce$cxxbridge1$make_audio_device_manager() noexcept {
  ::std::unique_ptr<::juce::AudioDeviceManager> (*make_audio_device_manager$)() = ::cxx_juce::makeUnique;
  return make_audio_device_manager$().release();
}
} // extern "C"
} // namespace cxx_juce

namespace juce {
extern "C" {
void juce$cxxbridge1$AudioDeviceManager$initialise(::juce::AudioDeviceManager &self, ::std::int32_t num_input_channels, ::std::int32_t num_output_channels, ::juce::XmlElement const *saved_state, bool select_default_device_on_failure, ::juce::JuceString const &preferred_default_device_name, ::juce::AudioDeviceSetup const *preferred_setup_options, ::juce::JuceString *return$) noexcept {
  ::juce::JuceString (::juce::AudioDeviceManager::*initialise$)(::std::int32_t, ::std::int32_t, ::juce::XmlElement const *, bool, ::juce::JuceString const &, ::juce::AudioDeviceSetup const *) = &::juce::AudioDeviceManager::initialise;
  new (return$) ::juce::JuceString((self.*initialise$)(num_input_channels, num_output_channels, saved_state, select_default_device_on_failure, preferred_default_device_name, preferred_setup_options));
}

void juce$cxxbridge1$AudioDeviceManager$get_audio_device_setup(::juce::AudioDeviceManager const &self, ::juce::AudioDeviceSetup *return$) noexcept {
  ::juce::AudioDeviceSetup (::juce::AudioDeviceManager::*get_audio_device_setup$)() const = &::juce::AudioDeviceManager::getAudioDeviceSetup;
  new (return$) ::juce::AudioDeviceSetup((self.*get_audio_device_setup$)());
}

void juce$cxxbridge1$AudioDeviceManager$set_audio_device_setup(::juce::AudioDeviceManager &self, ::juce::AudioDeviceSetup const &setup, bool treat_as_chosen_device, ::juce::JuceString *return$) noexcept {
  ::juce::JuceString (::juce::AudioDeviceManager::*set_audio_device_setup$)(::juce::AudioDeviceSetup const &, bool) = &::juce::AudioDeviceManager::setAudioDeviceSetup;
  new (return$) ::juce::JuceString((self.*set_audio_device_setup$)(setup, treat_as_chosen_device));
}

::juce::AudioIODevice *juce$cxxbridge1$AudioDeviceManager$get_current_audio_device(::juce::AudioDeviceManager const &self) noexcept {
  ::juce::AudioIODevice *(::juce::AudioDeviceManager::*get_current_audio_device$)() const = &::juce::AudioDeviceManager::getCurrentAudioDevice;
  return (self.*get_current_audio_device$)();
}

void juce$cxxbridge1$AudioDeviceManager$get_available_device_types(::juce::AudioDeviceManager &self, ::juce::AudioIODeviceTypeArray const **return$) noexcept {
  ::juce::AudioIODeviceTypeArray const &(::juce::AudioDeviceManager::*get_available_device_types$)() = &::juce::AudioDeviceManager::getAvailableDeviceTypes;
  new (return$) ::juce::AudioIODeviceTypeArray const *(&(self.*get_available_device_types$)());
}

::juce::AudioIODeviceType *juce$cxxbridge1$AudioDeviceManager$get_current_device_type_object(::juce::AudioDeviceManager const &self) noexcept {
  ::juce::AudioIODeviceType *(::juce::AudioDeviceManager::*get_current_device_type_object$)() const = &::juce::AudioDeviceManager::getCurrentDeviceTypeObject;
  return (self.*get_current_device_type_object$)();
}

void juce$cxxbridge1$AudioDeviceManager$play_test_sound(::juce::AudioDeviceManager &self) noexcept {
  void (::juce::AudioDeviceManager::*play_test_sound$)() = &::juce::AudioDeviceManager::playTestSound;
  (self.*play_test_sound$)();
}

void juce$cxxbridge1$AudioDeviceManager$add_audio_callback(::juce::AudioDeviceManager &self, ::juce::AudioIODeviceCallback *callback) noexcept {
  void (::juce::AudioDeviceManager::*add_audio_callback$)(::juce::AudioIODeviceCallback *) = &::juce::AudioDeviceManager::addAudioCallback;
  (self.*add_audio_callback$)(callback);
}

void juce$cxxbridge1$AudioDeviceManager$remove_audio_callback(::juce::AudioDeviceManager &self, ::juce::AudioIODeviceCallback *callback) noexcept {
  void (::juce::AudioDeviceManager::*remove_audio_callback$)(::juce::AudioIODeviceCallback *) = &::juce::AudioDeviceManager::removeAudioCallback;
  (self.*remove_audio_callback$)(callback);
}

void juce$cxxbridge1$AudioDeviceManager$add_audio_device_type(::juce::AudioDeviceManager &self, ::juce::AudioIODeviceType *device_type) noexcept {
  void (::juce::AudioDeviceManager::*add_audio_device_type$)(::std::unique_ptr<::juce::AudioIODeviceType>) = &::juce::AudioDeviceManager::addAudioDeviceType;
  (self.*add_audio_device_type$)(::std::unique_ptr<::juce::AudioIODeviceType>(device_type));
}

void juce$cxxbridge1$AudioDeviceManager$set_current_audio_device_type(::juce::AudioDeviceManager &self, ::juce::JuceString const &device_type, bool treat_as_chosen_device) noexcept {
  void (::juce::AudioDeviceManager::*set_current_audio_device_type$)(::juce::JuceString const &, bool) = &::juce::AudioDeviceManager::setCurrentAudioDeviceType;
  (self.*set_current_audio_device_type$)(device_type, treat_as_chosen_device);
}

::std::int32_t juce$cxxbridge1$AudioIODeviceTypeArray$size(::juce::AudioIODeviceTypeArray const &self) noexcept {
  ::std::int32_t (::juce::AudioIODeviceTypeArray::*size$)() const = &::juce::AudioIODeviceTypeArray::size;
  return (self.*size$)();
}

::juce::AudioIODeviceType *juce$cxxbridge1$AudioIODeviceTypeArray$get_unchecked(::juce::AudioIODeviceTypeArray const &self, ::std::int32_t index) noexcept {
  ::juce::AudioIODeviceType *(::juce::AudioIODeviceTypeArray::*get_unchecked$)(::std::int32_t) const = &::juce::AudioIODeviceTypeArray::getUnchecked;
  return (self.*get_unchecked$)(index);
}
} // extern "C"
} // namespace juce

extern "C" {
static_assert(::rust::detail::is_complete<::std::remove_extent<::juce::AudioDeviceManager>::type>::value, "definition of `::juce::AudioDeviceManager` is required");
static_assert(sizeof(::std::unique_ptr<::juce::AudioDeviceManager>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::juce::AudioDeviceManager>) == alignof(void *), "");
void cxxbridge1$unique_ptr$juce$AudioDeviceManager$null(::std::unique_ptr<::juce::AudioDeviceManager> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::juce::AudioDeviceManager>();
}
void cxxbridge1$unique_ptr$juce$AudioDeviceManager$raw(::std::unique_ptr<::juce::AudioDeviceManager> *ptr, ::std::unique_ptr<::juce::AudioDeviceManager>::pointer raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::juce::AudioDeviceManager>(raw);
}
::std::unique_ptr<::juce::AudioDeviceManager>::element_type const *cxxbridge1$unique_ptr$juce$AudioDeviceManager$get(::std::unique_ptr<::juce::AudioDeviceManager> const &ptr) noexcept {
  return ptr.get();
}
::std::unique_ptr<::juce::AudioDeviceManager>::pointer cxxbridge1$unique_ptr$juce$AudioDeviceManager$release(::std::unique_ptr<::juce::AudioDeviceManager> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$juce$AudioDeviceManager$drop(::std::unique_ptr<::juce::AudioDeviceManager> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::juce::AudioDeviceManager>::value>{}(ptr);
}
} // extern "C"
