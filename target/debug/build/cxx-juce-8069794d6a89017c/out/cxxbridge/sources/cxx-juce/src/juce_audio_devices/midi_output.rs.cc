#include "cxx_juce.h"
#include <cstddef>
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
  using MidiOutput = ::juce::MidiOutput;
}

static_assert(
    ::rust::IsRelocatable<::juce::MidiDeviceInfo>::value,
    "type juce::MidiDeviceInfo should be trivially move constructible and trivially destructible in C++ to be used as a return value of `get_default_device`, `get_device_info` in Rust");
static_assert(
    ::rust::IsRelocatable<::juce::MidiDeviceInfoArray>::value,
    "type juce::MidiDeviceInfoArray should be trivially move constructible and trivially destructible in C++ to be used as a return value of `get_available_devices` in Rust");

namespace juce {
extern "C" {
void juce$cxxbridge1$MidiOutput$get_available_devices(::juce::MidiDeviceInfoArray *return$) noexcept {
  ::juce::MidiDeviceInfoArray (*get_available_devices$)() = &::juce::MidiOutput::getAvailableDevices;
  new (return$) ::juce::MidiDeviceInfoArray(get_available_devices$());
}

void juce$cxxbridge1$MidiOutput$get_default_device(::juce::MidiDeviceInfo *return$) noexcept {
  ::juce::MidiDeviceInfo (*get_default_device$)() = &::juce::MidiOutput::getDefaultDevice;
  new (return$) ::juce::MidiDeviceInfo(get_default_device$());
}

::juce::MidiOutput *juce$cxxbridge1$MidiOutput$open_device(::juce::JuceString const &device_identifier) noexcept {
  ::std::unique_ptr<::juce::MidiOutput> (*open_device$)(::juce::JuceString const &) = &::juce::MidiOutput::openDevice;
  return open_device$(device_identifier).release();
}

void juce$cxxbridge1$MidiOutput$get_device_info(::juce::MidiOutput const &self, ::juce::MidiDeviceInfo *return$) noexcept {
  ::juce::MidiDeviceInfo (::juce::MidiOutput::*get_device_info$)() const = &::juce::MidiOutput::getDeviceInfo;
  new (return$) ::juce::MidiDeviceInfo((self.*get_device_info$)());
}

void juce$cxxbridge1$MidiOutput$set_name(::juce::MidiOutput &self, ::juce::JuceString const &new_name) noexcept {
  void (::juce::MidiOutput::*set_name$)(::juce::JuceString const &) = &::juce::MidiOutput::setName;
  (self.*set_name$)(new_name);
}

void juce$cxxbridge1$MidiOutput$send_message_now(::juce::MidiOutput &self, ::juce::MidiMessage const &message) noexcept {
  void (::juce::MidiOutput::*send_message_now$)(::juce::MidiMessage const &) = &::juce::MidiOutput::sendMessageNow;
  (self.*send_message_now$)(message);
}

void juce$cxxbridge1$MidiOutput$send_block_of_messages_now(::juce::MidiOutput &self, ::juce::MidiBuffer const &buffer) noexcept {
  void (::juce::MidiOutput::*send_block_of_messages_now$)(::juce::MidiBuffer const &) = &::juce::MidiOutput::sendBlockOfMessagesNow;
  (self.*send_block_of_messages_now$)(buffer);
}

void juce$cxxbridge1$MidiOutput$send_block_of_messages(::juce::MidiOutput &self, ::juce::MidiBuffer const &buffer, double millisecond_counter_to_start_at, double samples_per_second_for_buffer) noexcept {
  void (::juce::MidiOutput::*send_block_of_messages$)(::juce::MidiBuffer const &, double, double) = &::juce::MidiOutput::sendBlockOfMessages;
  (self.*send_block_of_messages$)(buffer, millisecond_counter_to_start_at, samples_per_second_for_buffer);
}

void juce$cxxbridge1$MidiOutput$clear_all_pending_messages(::juce::MidiOutput &self) noexcept {
  void (::juce::MidiOutput::*clear_all_pending_messages$)() = &::juce::MidiOutput::clearAllPendingMessages;
  (self.*clear_all_pending_messages$)();
}

void juce$cxxbridge1$MidiOutput$start_background_thread(::juce::MidiOutput &self) noexcept {
  void (::juce::MidiOutput::*start_background_thread$)() = &::juce::MidiOutput::startBackgroundThread;
  (self.*start_background_thread$)();
}

void juce$cxxbridge1$MidiOutput$stop_background_thread(::juce::MidiOutput &self) noexcept {
  void (::juce::MidiOutput::*stop_background_thread$)() = &::juce::MidiOutput::stopBackgroundThread;
  (self.*stop_background_thread$)();
}

bool juce$cxxbridge1$MidiOutput$is_background_thread_running(::juce::MidiOutput const &self) noexcept {
  bool (::juce::MidiOutput::*is_background_thread_running$)() const = &::juce::MidiOutput::isBackgroundThreadRunning;
  return (self.*is_background_thread_running$)();
}
} // extern "C"
} // namespace juce

extern "C" {
static_assert(::rust::detail::is_complete<::std::remove_extent<::juce::MidiOutput>::type>::value, "definition of `::juce::MidiOutput` is required");
static_assert(sizeof(::std::unique_ptr<::juce::MidiOutput>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::juce::MidiOutput>) == alignof(void *), "");
void cxxbridge1$unique_ptr$juce$MidiOutput$null(::std::unique_ptr<::juce::MidiOutput> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::juce::MidiOutput>();
}
void cxxbridge1$unique_ptr$juce$MidiOutput$raw(::std::unique_ptr<::juce::MidiOutput> *ptr, ::std::unique_ptr<::juce::MidiOutput>::pointer raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::juce::MidiOutput>(raw);
}
::std::unique_ptr<::juce::MidiOutput>::element_type const *cxxbridge1$unique_ptr$juce$MidiOutput$get(::std::unique_ptr<::juce::MidiOutput> const &ptr) noexcept {
  return ptr.get();
}
::std::unique_ptr<::juce::MidiOutput>::pointer cxxbridge1$unique_ptr$juce$MidiOutput$release(::std::unique_ptr<::juce::MidiOutput> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$juce$MidiOutput$drop(::std::unique_ptr<::juce::MidiOutput> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::juce::MidiOutput>::value>{}(ptr);
}
} // extern "C"
