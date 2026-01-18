#include "cxx_juce.h"
#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <new>
#include <string>
#include <type_traits>
#include <utility>
#if __cplusplus >= 201703L
#include <string_view>
#endif

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#ifdef __clang__
#pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
#endif // __clang__
#endif // __GNUC__

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

class Str::uninit {};
inline Str::Str(uninit) noexcept {}

namespace repr {
using Fat = ::std::array<::std::uintptr_t, 2>;
} // namespace repr

namespace detail {
template <typename T, typename = void *>
struct operator_new {
  void *operator()(::std::size_t sz) { return ::operator new(sz); }
};

template <typename T>
struct operator_new<T, decltype(T::operator new(sizeof(T)))> {
  void *operator()(::std::size_t sz) { return T::operator new(sz); }
};
} // namespace detail

template <typename T>
union MaybeUninit {
  T value;
  void *operator new(::std::size_t sz) { return detail::operator_new<T>{}(sz); }
  MaybeUninit() {}
  ~MaybeUninit() {}
};

namespace {
template <>
class impl<Str> final {
public:
  static Str new_unchecked(repr::Fat repr) noexcept {
    Str str = Str::uninit{};
    str.repr = repr;
    return str;
  }
};

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

static_assert(
    ::rust::IsRelocatable<::juce::BigInteger>::value,
    "type juce::BigInteger should be trivially move constructible and trivially destructible in C++ to be used as a return value of `get_active_input_channels`, `get_active_output_channels` in Rust");
static_assert(
    ::rust::IsRelocatable<::juce::IntArray>::value,
    "type juce::IntArray should be trivially move constructible and trivially destructible in C++ to be used as a return value of `get_available_buffer_sizes`, `available_buffer_sizes` in Rust");
static_assert(
    ::rust::IsRelocatable<::juce::DoubleArray>::value,
    "type juce::DoubleArray should be trivially move constructible and trivially destructible in C++ to be used as a return value of `get_available_sample_rates`, `available_sample_rates` in Rust");
static_assert(
    ::rust::IsRelocatable<::juce::JuceString>::value,
    "type juce::JuceString should be trivially move constructible and trivially destructible in C++ to be used as a return value of `open` in Rust");
static_assert(
    ::rust::IsRelocatable<::juce::StringArray>::value,
    "type juce::StringArray should be trivially move constructible and trivially destructible in C++ to be used as a return value of `output_channel_names`, `input_channel_names` in Rust");
static_assert(
    ::rust::IsRelocatable<::cxx_juce::BoxDynAudioDevice>::value,
    "type cxx_juce::BoxDynAudioDevice should be trivially move constructible and trivially destructible in C++ to be used as an argument of `wrap_audio_device` in Rust");

namespace cxx_juce {
extern "C" {
::juce::AudioIODevice *cxx_juce$cxxbridge1$wrap_audio_device(::cxx_juce::BoxDynAudioDevice *device) noexcept {
  ::std::unique_ptr<::juce::AudioIODevice> (*wrap_audio_device$)(::cxx_juce::BoxDynAudioDevice) = ::cxx_juce::wrap;
  return wrap_audio_device$(::std::move(*device)).release();
}
} // extern "C"
} // namespace cxx_juce

namespace juce {
extern "C" {
void juce$cxxbridge1$AudioIODevice$get_name(::juce::AudioIODevice const &self, ::juce::JuceString const **return$) noexcept {
  ::juce::JuceString const &(::juce::AudioIODevice::*get_name$)() const = &::juce::AudioIODevice::getName;
  new (return$) ::juce::JuceString const *(&(self.*get_name$)());
}

void juce$cxxbridge1$AudioIODevice$get_type_name(::juce::AudioIODevice const &self, ::juce::JuceString const **return$) noexcept {
  ::juce::JuceString const &(::juce::AudioIODevice::*get_type_name$)() const = &::juce::AudioIODevice::getTypeName;
  new (return$) ::juce::JuceString const *(&(self.*get_type_name$)());
}

double juce$cxxbridge1$AudioIODevice$get_current_sample_rate(::juce::AudioIODevice &self) noexcept {
  double (::juce::AudioIODevice::*get_current_sample_rate$)() = &::juce::AudioIODevice::getCurrentSampleRate;
  return (self.*get_current_sample_rate$)();
}

::std::int32_t juce$cxxbridge1$AudioIODevice$get_current_buffer_size_samples(::juce::AudioIODevice &self) noexcept {
  ::std::int32_t (::juce::AudioIODevice::*get_current_buffer_size_samples$)() = &::juce::AudioIODevice::getCurrentBufferSizeSamples;
  return (self.*get_current_buffer_size_samples$)();
}

void juce$cxxbridge1$AudioIODevice$get_available_sample_rates(::juce::AudioIODevice &self, ::juce::DoubleArray *return$) noexcept {
  ::juce::DoubleArray (::juce::AudioIODevice::*get_available_sample_rates$)() = &::juce::AudioIODevice::getAvailableSampleRates;
  new (return$) ::juce::DoubleArray((self.*get_available_sample_rates$)());
}

void juce$cxxbridge1$AudioIODevice$get_available_buffer_sizes(::juce::AudioIODevice &self, ::juce::IntArray *return$) noexcept {
  ::juce::IntArray (::juce::AudioIODevice::*get_available_buffer_sizes$)() = &::juce::AudioIODevice::getAvailableBufferSizes;
  new (return$) ::juce::IntArray((self.*get_available_buffer_sizes$)());
}

void juce$cxxbridge1$AudioIODevice$get_active_input_channels(::juce::AudioIODevice const &self, ::juce::BigInteger *return$) noexcept {
  ::juce::BigInteger (::juce::AudioIODevice::*get_active_input_channels$)() const = &::juce::AudioIODevice::getActiveInputChannels;
  new (return$) ::juce::BigInteger((self.*get_active_input_channels$)());
}

void juce$cxxbridge1$AudioIODevice$get_active_output_channels(::juce::AudioIODevice const &self, ::juce::BigInteger *return$) noexcept {
  ::juce::BigInteger (::juce::AudioIODevice::*get_active_output_channels$)() const = &::juce::AudioIODevice::getActiveOutputChannels;
  new (return$) ::juce::BigInteger((self.*get_active_output_channels$)());
}

void juce$cxxbridge1$AudioIODevice$open(::juce::AudioIODevice &self, ::juce::BigInteger const &input_channels, ::juce::BigInteger const &output_channels, double sample_rate, ::std::int32_t buffer_size, ::juce::JuceString *return$) noexcept {
  ::juce::JuceString (::juce::AudioIODevice::*open$)(::juce::BigInteger const &, ::juce::BigInteger const &, double, ::std::int32_t) = &::juce::AudioIODevice::open;
  new (return$) ::juce::JuceString((self.*open$)(input_channels, output_channels, sample_rate, buffer_size));
}

void juce$cxxbridge1$AudioIODevice$close(::juce::AudioIODevice &self) noexcept {
  void (::juce::AudioIODevice::*close$)() = &::juce::AudioIODevice::close;
  (self.*close$)();
}
} // extern "C"
} // namespace juce

namespace cxx_juce {
extern "C" {
::std::size_t cxx_juce$cxxbridge1$AudioDeviceImpl$operator$sizeof() noexcept;
::std::size_t cxx_juce$cxxbridge1$AudioDeviceImpl$operator$alignof() noexcept;

void cxx_juce$cxxbridge1$AudioDeviceImpl$drop(::cxx_juce::BoxDynAudioDevice *device) noexcept;

::rust::repr::Fat cxx_juce$cxxbridge1$AudioDeviceImpl$name(::cxx_juce::BoxDynAudioDevice const &device) noexcept;

::rust::repr::Fat cxx_juce$cxxbridge1$AudioDeviceImpl$type_name(::cxx_juce::BoxDynAudioDevice const &device) noexcept;

double cxx_juce$cxxbridge1$AudioDeviceImpl$sample_rate(::cxx_juce::BoxDynAudioDevice &device) noexcept;

::std::int32_t cxx_juce$cxxbridge1$AudioDeviceImpl$buffer_size(::cxx_juce::BoxDynAudioDevice &device) noexcept;

void cxx_juce$cxxbridge1$AudioDeviceImpl$available_sample_rates(::cxx_juce::BoxDynAudioDevice &device, ::juce::DoubleArray *return$) noexcept;

void cxx_juce$cxxbridge1$AudioDeviceImpl$available_buffer_sizes(::cxx_juce::BoxDynAudioDevice &device, ::juce::IntArray *return$) noexcept;

void cxx_juce$cxxbridge1$AudioDeviceImpl$open(::cxx_juce::BoxDynAudioDevice &device, double sample_rate, ::std::int32_t buffer_size, ::juce::JuceString *return$) noexcept;

void cxx_juce$cxxbridge1$AudioDeviceImpl$close(::cxx_juce::BoxDynAudioDevice &device) noexcept;

::std::int32_t cxx_juce$cxxbridge1$AudioDeviceImpl$input_channels(::cxx_juce::BoxDynAudioDevice const &device) noexcept;

::std::int32_t cxx_juce$cxxbridge1$AudioDeviceImpl$output_channels(::cxx_juce::BoxDynAudioDevice const &device) noexcept;

void cxx_juce$cxxbridge1$AudioDeviceImpl$output_channel_names(::cxx_juce::BoxDynAudioDevice const &device, ::juce::StringArray *return$) noexcept;

void cxx_juce$cxxbridge1$AudioDeviceImpl$input_channel_names(::cxx_juce::BoxDynAudioDevice const &device, ::juce::StringArray *return$) noexcept;

::std::int32_t cxx_juce$cxxbridge1$AudioDeviceImpl$default_buffer_size(::cxx_juce::BoxDynAudioDevice const &device) noexcept;

bool cxx_juce$cxxbridge1$AudioDeviceImpl$is_open(::cxx_juce::BoxDynAudioDevice const &device) noexcept;

bool cxx_juce$cxxbridge1$AudioDeviceImpl$is_playing(::cxx_juce::BoxDynAudioDevice const &device) noexcept;

void cxx_juce$cxxbridge1$AudioDeviceImpl$last_error(::cxx_juce::BoxDynAudioDevice const &device, ::rust::String *return$) noexcept;

::std::int32_t cxx_juce$cxxbridge1$AudioDeviceImpl$bit_depth(::cxx_juce::BoxDynAudioDevice const &device) noexcept;

::std::int32_t cxx_juce$cxxbridge1$AudioDeviceImpl$output_latency(::cxx_juce::BoxDynAudioDevice const &device) noexcept;

::std::int32_t cxx_juce$cxxbridge1$AudioDeviceImpl$input_latency(::cxx_juce::BoxDynAudioDevice const &device) noexcept;

bool cxx_juce$cxxbridge1$AudioDeviceImpl$has_control_panel(::cxx_juce::BoxDynAudioDevice const &device) noexcept;

bool cxx_juce$cxxbridge1$AudioDeviceImpl$show_control_panel(::cxx_juce::BoxDynAudioDevice &device) noexcept;

bool cxx_juce$cxxbridge1$AudioDeviceImpl$set_audio_preprocessing_enabled(::cxx_juce::BoxDynAudioDevice &device, bool enabled) noexcept;

::std::int32_t cxx_juce$cxxbridge1$AudioDeviceImpl$xrun_count(::cxx_juce::BoxDynAudioDevice const &device) noexcept;

void cxx_juce$cxxbridge1$AudioDeviceImpl$start(::cxx_juce::BoxDynAudioDevice &device) noexcept;

void cxx_juce$cxxbridge1$AudioDeviceImpl$stop(::cxx_juce::BoxDynAudioDevice &device) noexcept;
} // extern "C"

::std::size_t AudioDeviceImpl::layout::size() noexcept {
  return cxx_juce$cxxbridge1$AudioDeviceImpl$operator$sizeof();
}

::std::size_t AudioDeviceImpl::layout::align() noexcept {
  return cxx_juce$cxxbridge1$AudioDeviceImpl$operator$alignof();
}

void AudioDeviceImpl::drop(::cxx_juce::BoxDynAudioDevice *device) noexcept {
  cxx_juce$cxxbridge1$AudioDeviceImpl$drop(device);
}

::rust::Str AudioDeviceImpl::name(::cxx_juce::BoxDynAudioDevice const &device) noexcept {
  return ::rust::impl<::rust::Str>::new_unchecked(cxx_juce$cxxbridge1$AudioDeviceImpl$name(device));
}

::rust::Str AudioDeviceImpl::type_name(::cxx_juce::BoxDynAudioDevice const &device) noexcept {
  return ::rust::impl<::rust::Str>::new_unchecked(cxx_juce$cxxbridge1$AudioDeviceImpl$type_name(device));
}

double AudioDeviceImpl::sample_rate(::cxx_juce::BoxDynAudioDevice &device) noexcept {
  return cxx_juce$cxxbridge1$AudioDeviceImpl$sample_rate(device);
}

::std::int32_t AudioDeviceImpl::buffer_size(::cxx_juce::BoxDynAudioDevice &device) noexcept {
  return cxx_juce$cxxbridge1$AudioDeviceImpl$buffer_size(device);
}

::juce::DoubleArray AudioDeviceImpl::available_sample_rates(::cxx_juce::BoxDynAudioDevice &device) noexcept {
  ::rust::MaybeUninit<::juce::DoubleArray> return$;
  cxx_juce$cxxbridge1$AudioDeviceImpl$available_sample_rates(device, &return$.value);
  return ::std::move(return$.value);
}

::juce::IntArray AudioDeviceImpl::available_buffer_sizes(::cxx_juce::BoxDynAudioDevice &device) noexcept {
  ::rust::MaybeUninit<::juce::IntArray> return$;
  cxx_juce$cxxbridge1$AudioDeviceImpl$available_buffer_sizes(device, &return$.value);
  return ::std::move(return$.value);
}

::juce::JuceString AudioDeviceImpl::open(::cxx_juce::BoxDynAudioDevice &device, double sample_rate, ::std::int32_t buffer_size) noexcept {
  ::rust::MaybeUninit<::juce::JuceString> return$;
  cxx_juce$cxxbridge1$AudioDeviceImpl$open(device, sample_rate, buffer_size, &return$.value);
  return ::std::move(return$.value);
}

void AudioDeviceImpl::close(::cxx_juce::BoxDynAudioDevice &device) noexcept {
  cxx_juce$cxxbridge1$AudioDeviceImpl$close(device);
}

::std::int32_t AudioDeviceImpl::input_channels(::cxx_juce::BoxDynAudioDevice const &device) noexcept {
  return cxx_juce$cxxbridge1$AudioDeviceImpl$input_channels(device);
}

::std::int32_t AudioDeviceImpl::output_channels(::cxx_juce::BoxDynAudioDevice const &device) noexcept {
  return cxx_juce$cxxbridge1$AudioDeviceImpl$output_channels(device);
}

::juce::StringArray AudioDeviceImpl::output_channel_names(::cxx_juce::BoxDynAudioDevice const &device) noexcept {
  ::rust::MaybeUninit<::juce::StringArray> return$;
  cxx_juce$cxxbridge1$AudioDeviceImpl$output_channel_names(device, &return$.value);
  return ::std::move(return$.value);
}

::juce::StringArray AudioDeviceImpl::input_channel_names(::cxx_juce::BoxDynAudioDevice const &device) noexcept {
  ::rust::MaybeUninit<::juce::StringArray> return$;
  cxx_juce$cxxbridge1$AudioDeviceImpl$input_channel_names(device, &return$.value);
  return ::std::move(return$.value);
}

::std::int32_t AudioDeviceImpl::default_buffer_size(::cxx_juce::BoxDynAudioDevice const &device) noexcept {
  return cxx_juce$cxxbridge1$AudioDeviceImpl$default_buffer_size(device);
}

bool AudioDeviceImpl::is_open(::cxx_juce::BoxDynAudioDevice const &device) noexcept {
  return cxx_juce$cxxbridge1$AudioDeviceImpl$is_open(device);
}

bool AudioDeviceImpl::is_playing(::cxx_juce::BoxDynAudioDevice const &device) noexcept {
  return cxx_juce$cxxbridge1$AudioDeviceImpl$is_playing(device);
}

::rust::String AudioDeviceImpl::last_error(::cxx_juce::BoxDynAudioDevice const &device) noexcept {
  ::rust::MaybeUninit<::rust::String> return$;
  cxx_juce$cxxbridge1$AudioDeviceImpl$last_error(device, &return$.value);
  return ::std::move(return$.value);
}

::std::int32_t AudioDeviceImpl::bit_depth(::cxx_juce::BoxDynAudioDevice const &device) noexcept {
  return cxx_juce$cxxbridge1$AudioDeviceImpl$bit_depth(device);
}

::std::int32_t AudioDeviceImpl::output_latency(::cxx_juce::BoxDynAudioDevice const &device) noexcept {
  return cxx_juce$cxxbridge1$AudioDeviceImpl$output_latency(device);
}

::std::int32_t AudioDeviceImpl::input_latency(::cxx_juce::BoxDynAudioDevice const &device) noexcept {
  return cxx_juce$cxxbridge1$AudioDeviceImpl$input_latency(device);
}

bool AudioDeviceImpl::has_control_panel(::cxx_juce::BoxDynAudioDevice const &device) noexcept {
  return cxx_juce$cxxbridge1$AudioDeviceImpl$has_control_panel(device);
}

bool AudioDeviceImpl::show_control_panel(::cxx_juce::BoxDynAudioDevice &device) noexcept {
  return cxx_juce$cxxbridge1$AudioDeviceImpl$show_control_panel(device);
}

bool AudioDeviceImpl::set_audio_preprocessing_enabled(::cxx_juce::BoxDynAudioDevice &device, bool enabled) noexcept {
  return cxx_juce$cxxbridge1$AudioDeviceImpl$set_audio_preprocessing_enabled(device, enabled);
}

::std::int32_t AudioDeviceImpl::xrun_count(::cxx_juce::BoxDynAudioDevice const &device) noexcept {
  return cxx_juce$cxxbridge1$AudioDeviceImpl$xrun_count(device);
}

void AudioDeviceImpl::start(::cxx_juce::BoxDynAudioDevice &device) noexcept {
  cxx_juce$cxxbridge1$AudioDeviceImpl$start(device);
}

void AudioDeviceImpl::stop(::cxx_juce::BoxDynAudioDevice &device) noexcept {
  cxx_juce$cxxbridge1$AudioDeviceImpl$stop(device);
}
} // namespace cxx_juce

extern "C" {
static_assert(::rust::detail::is_complete<::std::remove_extent<::juce::AudioIODevice>::type>::value, "definition of `::juce::AudioIODevice` is required");
static_assert(sizeof(::std::unique_ptr<::juce::AudioIODevice>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::juce::AudioIODevice>) == alignof(void *), "");
void cxxbridge1$unique_ptr$juce$AudioIODevice$null(::std::unique_ptr<::juce::AudioIODevice> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::juce::AudioIODevice>();
}
void cxxbridge1$unique_ptr$juce$AudioIODevice$raw(::std::unique_ptr<::juce::AudioIODevice> *ptr, ::std::unique_ptr<::juce::AudioIODevice>::pointer raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::juce::AudioIODevice>(raw);
}
::std::unique_ptr<::juce::AudioIODevice>::element_type const *cxxbridge1$unique_ptr$juce$AudioIODevice$get(::std::unique_ptr<::juce::AudioIODevice> const &ptr) noexcept {
  return ptr.get();
}
::std::unique_ptr<::juce::AudioIODevice>::pointer cxxbridge1$unique_ptr$juce$AudioIODevice$release(::std::unique_ptr<::juce::AudioIODevice> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$juce$AudioIODevice$drop(::std::unique_ptr<::juce::AudioIODevice> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::juce::AudioIODevice>::value>{}(ptr);
}
} // extern "C"
