#pragma once
#include "cxx_juce.h"
#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <type_traits>
#if __cplusplus >= 201703L
#include <string_view>
#endif

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
#endif // __clang__

namespace rust {
inline namespace cxxbridge1 {
// #include "rust/cxx.h"

struct unsafe_bitcopy_t;

namespace {
template <typename T>
class impl;
} // namespace

#ifndef CXXBRIDGE1_RUST_STRING
#define CXXBRIDGE1_RUST_STRING
class String final {
public:
  String() noexcept;
  String(const String &) noexcept;
  String(String &&) noexcept;
  ~String() noexcept;

  String(const std::string &);
  String(const char *);
  String(const char *, std::size_t);
  String(const char16_t *);
  String(const char16_t *, std::size_t);
#ifdef __cpp_char8_t
  String(const char8_t *s);
  String(const char8_t *s, std::size_t len);
#endif

  static String lossy(const std::string &) noexcept;
  static String lossy(const char *) noexcept;
  static String lossy(const char *, std::size_t) noexcept;
  static String lossy(const char16_t *) noexcept;
  static String lossy(const char16_t *, std::size_t) noexcept;

  String &operator=(const String &) & noexcept;
  String &operator=(String &&) & noexcept;

  explicit operator std::string() const;

  const char *data() const noexcept;
  std::size_t size() const noexcept;
  std::size_t length() const noexcept;
  bool empty() const noexcept;

  const char *c_str() noexcept;

  std::size_t capacity() const noexcept;
  void reserve(size_t new_cap) noexcept;

  using iterator = char *;
  iterator begin() noexcept;
  iterator end() noexcept;

  using const_iterator = const char *;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  bool operator==(const String &) const noexcept;
  bool operator!=(const String &) const noexcept;
  bool operator<(const String &) const noexcept;
  bool operator<=(const String &) const noexcept;
  bool operator>(const String &) const noexcept;
  bool operator>=(const String &) const noexcept;

  void swap(String &) noexcept;

  String(unsafe_bitcopy_t, const String &) noexcept;

private:
  struct lossy_t;
  String(lossy_t, const char *, std::size_t) noexcept;
  String(lossy_t, const char16_t *, std::size_t) noexcept;
  friend void swap(String &lhs, String &rhs) noexcept { lhs.swap(rhs); }

  std::array<std::uintptr_t, 3> repr;
};
#endif // CXXBRIDGE1_RUST_STRING

#ifndef CXXBRIDGE1_RUST_STR
#define CXXBRIDGE1_RUST_STR
class Str final {
public:
  Str() noexcept;
  Str(const String &) noexcept;
  Str(const std::string &);
  Str(const char *);
  Str(const char *, std::size_t);

  Str &operator=(const Str &) & noexcept = default;

  explicit operator std::string() const;
#if __cplusplus >= 201703L
  explicit operator std::string_view() const;
#endif

  const char *data() const noexcept;
  std::size_t size() const noexcept;
  std::size_t length() const noexcept;
  bool empty() const noexcept;

  Str(const Str &) noexcept = default;
  ~Str() noexcept = default;

  using iterator = const char *;
  using const_iterator = const char *;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  bool operator==(const Str &) const noexcept;
  bool operator!=(const Str &) const noexcept;
  bool operator<(const Str &) const noexcept;
  bool operator<=(const Str &) const noexcept;
  bool operator>(const Str &) const noexcept;
  bool operator>=(const Str &) const noexcept;

  void swap(Str &) noexcept;

private:
  class uninit;
  Str(uninit) noexcept;
  friend impl<Str>;

  std::array<std::uintptr_t, 2> repr;
};
#endif // CXXBRIDGE1_RUST_STR

#ifndef CXXBRIDGE1_RUST_OPAQUE
#define CXXBRIDGE1_RUST_OPAQUE
class Opaque {
public:
  Opaque() = delete;
  Opaque(const Opaque &) = delete;
  ~Opaque() = delete;
};
#endif // CXXBRIDGE1_RUST_OPAQUE

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

#ifndef CXXBRIDGE1_LAYOUT
#define CXXBRIDGE1_LAYOUT
class layout {
  template <typename T>
  friend std::size_t size_of();
  template <typename T>
  friend std::size_t align_of();
  template <typename T>
  static typename std::enable_if<std::is_base_of<Opaque, T>::value,
                                 std::size_t>::type
  do_size_of() {
    return T::layout::size();
  }
  template <typename T>
  static typename std::enable_if<!std::is_base_of<Opaque, T>::value,
                                 std::size_t>::type
  do_size_of() {
    return sizeof(T);
  }
  template <typename T>
  static
      typename std::enable_if<detail::is_complete<T>::value, std::size_t>::type
      size_of() {
    return do_size_of<T>();
  }
  template <typename T>
  static typename std::enable_if<std::is_base_of<Opaque, T>::value,
                                 std::size_t>::type
  do_align_of() {
    return T::layout::align();
  }
  template <typename T>
  static typename std::enable_if<!std::is_base_of<Opaque, T>::value,
                                 std::size_t>::type
  do_align_of() {
    return alignof(T);
  }
  template <typename T>
  static
      typename std::enable_if<detail::is_complete<T>::value, std::size_t>::type
      align_of() {
    return do_align_of<T>();
  }
};

template <typename T>
std::size_t size_of() {
  return layout::size_of<T>();
}

template <typename T>
std::size_t align_of() {
  return layout::align_of<T>();
}
#endif // CXXBRIDGE1_LAYOUT
} // namespace cxxbridge1
} // namespace rust

namespace juce {
  using AudioIODevice = ::juce::AudioIODevice;
}
namespace cxx_juce {
  struct AudioDeviceImpl;
}

namespace cxx_juce {
#ifndef CXXBRIDGE1_STRUCT_cxx_juce$AudioDeviceImpl
#define CXXBRIDGE1_STRUCT_cxx_juce$AudioDeviceImpl
struct AudioDeviceImpl final : public ::rust::Opaque {
  static void drop(::cxx_juce::BoxDynAudioDevice *device) noexcept;
  static ::rust::Str name(::cxx_juce::BoxDynAudioDevice const &device) noexcept;
  static ::rust::Str type_name(::cxx_juce::BoxDynAudioDevice const &device) noexcept;
  static double sample_rate(::cxx_juce::BoxDynAudioDevice &device) noexcept;
  static ::std::int32_t buffer_size(::cxx_juce::BoxDynAudioDevice &device) noexcept;
  static ::juce::DoubleArray available_sample_rates(::cxx_juce::BoxDynAudioDevice &device) noexcept;
  static ::juce::IntArray available_buffer_sizes(::cxx_juce::BoxDynAudioDevice &device) noexcept;
  static ::juce::JuceString open(::cxx_juce::BoxDynAudioDevice &device, double sample_rate, ::std::int32_t buffer_size) noexcept;
  static void close(::cxx_juce::BoxDynAudioDevice &device) noexcept;
  static ::std::int32_t input_channels(::cxx_juce::BoxDynAudioDevice const &device) noexcept;
  static ::std::int32_t output_channels(::cxx_juce::BoxDynAudioDevice const &device) noexcept;
  static ::juce::StringArray output_channel_names(::cxx_juce::BoxDynAudioDevice const &device) noexcept;
  static ::juce::StringArray input_channel_names(::cxx_juce::BoxDynAudioDevice const &device) noexcept;
  static ::std::int32_t default_buffer_size(::cxx_juce::BoxDynAudioDevice const &device) noexcept;
  static bool is_open(::cxx_juce::BoxDynAudioDevice const &device) noexcept;
  static bool is_playing(::cxx_juce::BoxDynAudioDevice const &device) noexcept;
  static ::rust::String last_error(::cxx_juce::BoxDynAudioDevice const &device) noexcept;
  static ::std::int32_t bit_depth(::cxx_juce::BoxDynAudioDevice const &device) noexcept;
  static ::std::int32_t output_latency(::cxx_juce::BoxDynAudioDevice const &device) noexcept;
  static ::std::int32_t input_latency(::cxx_juce::BoxDynAudioDevice const &device) noexcept;
  static bool has_control_panel(::cxx_juce::BoxDynAudioDevice const &device) noexcept;
  static bool show_control_panel(::cxx_juce::BoxDynAudioDevice &device) noexcept;
  static bool set_audio_preprocessing_enabled(::cxx_juce::BoxDynAudioDevice &device, bool enabled) noexcept;
  static ::std::int32_t xrun_count(::cxx_juce::BoxDynAudioDevice const &device) noexcept;
  static void start(::cxx_juce::BoxDynAudioDevice &device) noexcept;
  static void stop(::cxx_juce::BoxDynAudioDevice &device) noexcept;
  ~AudioDeviceImpl() = delete;

private:
  friend ::rust::layout;
  struct layout {
    static ::std::size_t size() noexcept;
    static ::std::size_t align() noexcept;
  };
};
#endif // CXXBRIDGE1_STRUCT_cxx_juce$AudioDeviceImpl
} // namespace cxx_juce

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__
