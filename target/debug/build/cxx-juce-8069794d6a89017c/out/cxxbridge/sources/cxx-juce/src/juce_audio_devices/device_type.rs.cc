#include "cxx_juce.h"
#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <new>
#include <string>
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

struct unsafe_bitcopy_t;

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
  using AudioIODeviceType = ::juce::AudioIODeviceType;
}
namespace cxx_juce {
  struct AudioDeviceTypeImpl;
}

namespace cxx_juce {
#ifndef CXXBRIDGE1_STRUCT_cxx_juce$AudioDeviceTypeImpl
#define CXXBRIDGE1_STRUCT_cxx_juce$AudioDeviceTypeImpl
struct AudioDeviceTypeImpl final : public ::rust::Opaque {
  static void drop(::cxx_juce::BoxDynAudioDeviceType *device) noexcept;
  static ::rust::String name(::cxx_juce::BoxDynAudioDeviceType const &device_type) noexcept;
  static void scan_for_devices(::cxx_juce::BoxDynAudioDeviceType &device_type) noexcept;
  static ::juce::StringArray input_devices(::cxx_juce::BoxDynAudioDeviceType const &device_type) noexcept;
  static ::juce::StringArray output_devices(::cxx_juce::BoxDynAudioDeviceType const &device_type) noexcept;
  static ::std::unique_ptr<::juce::AudioIODevice> create_device(::cxx_juce::BoxDynAudioDeviceType &device_type, ::juce::JuceString const &input_device_name, ::juce::JuceString const &output_device_name) noexcept;
  static ::std::int32_t default_device_index(::cxx_juce::BoxDynAudioDeviceType const &device_type, bool for_input) noexcept;
  static bool has_separate_inputs_and_outputs(::cxx_juce::BoxDynAudioDeviceType const &device_type) noexcept;
  ~AudioDeviceTypeImpl() = delete;

private:
  friend ::rust::layout;
  struct layout {
    static ::std::size_t size() noexcept;
    static ::std::size_t align() noexcept;
  };
};
#endif // CXXBRIDGE1_STRUCT_cxx_juce$AudioDeviceTypeImpl
} // namespace cxx_juce

static_assert(
    ::rust::IsRelocatable<::juce::StringArray>::value,
    "type juce::StringArray should be trivially move constructible and trivially destructible in C++ to be used as a return value of `get_device_names`, `input_devices`, `output_devices` in Rust");
static_assert(
    ::rust::IsRelocatable<::cxx_juce::BoxDynAudioDeviceType>::value,
    "type cxx_juce::BoxDynAudioDeviceType should be trivially move constructible and trivially destructible in C++ to be used as an argument of `wrap_audio_device_type` in Rust");

namespace cxx_juce {
extern "C" {
::juce::AudioIODeviceType *cxx_juce$cxxbridge1$wrap_audio_device_type(::cxx_juce::BoxDynAudioDeviceType *device_type) noexcept {
  ::std::unique_ptr<::juce::AudioIODeviceType> (*wrap_audio_device_type$)(::cxx_juce::BoxDynAudioDeviceType) = ::cxx_juce::wrap;
  return wrap_audio_device_type$(::std::move(*device_type)).release();
}
} // extern "C"
} // namespace cxx_juce

namespace juce {
extern "C" {
void juce$cxxbridge1$AudioIODeviceType$get_type_name(::juce::AudioIODeviceType const &self, ::juce::JuceString const **return$) noexcept {
  ::juce::JuceString const &(::juce::AudioIODeviceType::*get_type_name$)() const = &::juce::AudioIODeviceType::getTypeName;
  new (return$) ::juce::JuceString const *(&(self.*get_type_name$)());
}

void juce$cxxbridge1$AudioIODeviceType$scan_for_devices(::juce::AudioIODeviceType &self) noexcept {
  void (::juce::AudioIODeviceType::*scan_for_devices$)() = &::juce::AudioIODeviceType::scanForDevices;
  (self.*scan_for_devices$)();
}

void juce$cxxbridge1$AudioIODeviceType$get_device_names(::juce::AudioIODeviceType const &self, bool inputs, ::juce::StringArray *return$) noexcept {
  ::juce::StringArray (::juce::AudioIODeviceType::*get_device_names$)(bool) const = &::juce::AudioIODeviceType::getDeviceNames;
  new (return$) ::juce::StringArray((self.*get_device_names$)(inputs));
}

::juce::AudioIODevice *juce$cxxbridge1$AudioIODeviceType$create_device_raw(::juce::AudioIODeviceType &self, ::juce::JuceString const &input_device_name, ::juce::JuceString const &output_device_name) noexcept {
  ::juce::AudioIODevice *(::juce::AudioIODeviceType::*create_device_raw$)(::juce::JuceString const &, ::juce::JuceString const &) = &::juce::AudioIODeviceType::createDevice;
  return (self.*create_device_raw$)(input_device_name, output_device_name);
}
} // extern "C"
} // namespace juce

namespace cxx_juce {
extern "C" {
::std::size_t cxx_juce$cxxbridge1$AudioDeviceTypeImpl$operator$sizeof() noexcept;
::std::size_t cxx_juce$cxxbridge1$AudioDeviceTypeImpl$operator$alignof() noexcept;

void cxx_juce$cxxbridge1$AudioDeviceTypeImpl$drop(::cxx_juce::BoxDynAudioDeviceType *device) noexcept;

void cxx_juce$cxxbridge1$AudioDeviceTypeImpl$name(::cxx_juce::BoxDynAudioDeviceType const &device_type, ::rust::String *return$) noexcept;

void cxx_juce$cxxbridge1$AudioDeviceTypeImpl$scan_for_devices(::cxx_juce::BoxDynAudioDeviceType &device_type) noexcept;

void cxx_juce$cxxbridge1$AudioDeviceTypeImpl$input_devices(::cxx_juce::BoxDynAudioDeviceType const &device_type, ::juce::StringArray *return$) noexcept;

void cxx_juce$cxxbridge1$AudioDeviceTypeImpl$output_devices(::cxx_juce::BoxDynAudioDeviceType const &device_type, ::juce::StringArray *return$) noexcept;

::juce::AudioIODevice *cxx_juce$cxxbridge1$AudioDeviceTypeImpl$create_device(::cxx_juce::BoxDynAudioDeviceType &device_type, ::juce::JuceString const &input_device_name, ::juce::JuceString const &output_device_name) noexcept;

::std::int32_t cxx_juce$cxxbridge1$AudioDeviceTypeImpl$default_device_index(::cxx_juce::BoxDynAudioDeviceType const &device_type, bool for_input) noexcept;

bool cxx_juce$cxxbridge1$AudioDeviceTypeImpl$has_separate_inputs_and_outputs(::cxx_juce::BoxDynAudioDeviceType const &device_type) noexcept;
} // extern "C"

::std::size_t AudioDeviceTypeImpl::layout::size() noexcept {
  return cxx_juce$cxxbridge1$AudioDeviceTypeImpl$operator$sizeof();
}

::std::size_t AudioDeviceTypeImpl::layout::align() noexcept {
  return cxx_juce$cxxbridge1$AudioDeviceTypeImpl$operator$alignof();
}

void AudioDeviceTypeImpl::drop(::cxx_juce::BoxDynAudioDeviceType *device) noexcept {
  cxx_juce$cxxbridge1$AudioDeviceTypeImpl$drop(device);
}

::rust::String AudioDeviceTypeImpl::name(::cxx_juce::BoxDynAudioDeviceType const &device_type) noexcept {
  ::rust::MaybeUninit<::rust::String> return$;
  cxx_juce$cxxbridge1$AudioDeviceTypeImpl$name(device_type, &return$.value);
  return ::std::move(return$.value);
}

void AudioDeviceTypeImpl::scan_for_devices(::cxx_juce::BoxDynAudioDeviceType &device_type) noexcept {
  cxx_juce$cxxbridge1$AudioDeviceTypeImpl$scan_for_devices(device_type);
}

::juce::StringArray AudioDeviceTypeImpl::input_devices(::cxx_juce::BoxDynAudioDeviceType const &device_type) noexcept {
  ::rust::MaybeUninit<::juce::StringArray> return$;
  cxx_juce$cxxbridge1$AudioDeviceTypeImpl$input_devices(device_type, &return$.value);
  return ::std::move(return$.value);
}

::juce::StringArray AudioDeviceTypeImpl::output_devices(::cxx_juce::BoxDynAudioDeviceType const &device_type) noexcept {
  ::rust::MaybeUninit<::juce::StringArray> return$;
  cxx_juce$cxxbridge1$AudioDeviceTypeImpl$output_devices(device_type, &return$.value);
  return ::std::move(return$.value);
}

::std::unique_ptr<::juce::AudioIODevice> AudioDeviceTypeImpl::create_device(::cxx_juce::BoxDynAudioDeviceType &device_type, ::juce::JuceString const &input_device_name, ::juce::JuceString const &output_device_name) noexcept {
  return ::std::unique_ptr<::juce::AudioIODevice>(cxx_juce$cxxbridge1$AudioDeviceTypeImpl$create_device(device_type, input_device_name, output_device_name));
}

::std::int32_t AudioDeviceTypeImpl::default_device_index(::cxx_juce::BoxDynAudioDeviceType const &device_type, bool for_input) noexcept {
  return cxx_juce$cxxbridge1$AudioDeviceTypeImpl$default_device_index(device_type, for_input);
}

bool AudioDeviceTypeImpl::has_separate_inputs_and_outputs(::cxx_juce::BoxDynAudioDeviceType const &device_type) noexcept {
  return cxx_juce$cxxbridge1$AudioDeviceTypeImpl$has_separate_inputs_and_outputs(device_type);
}
} // namespace cxx_juce

extern "C" {
static_assert(::rust::detail::is_complete<::std::remove_extent<::juce::AudioIODeviceType>::type>::value, "definition of `::juce::AudioIODeviceType` is required");
static_assert(sizeof(::std::unique_ptr<::juce::AudioIODeviceType>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::juce::AudioIODeviceType>) == alignof(void *), "");
void cxxbridge1$unique_ptr$juce$AudioIODeviceType$null(::std::unique_ptr<::juce::AudioIODeviceType> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::juce::AudioIODeviceType>();
}
void cxxbridge1$unique_ptr$juce$AudioIODeviceType$raw(::std::unique_ptr<::juce::AudioIODeviceType> *ptr, ::std::unique_ptr<::juce::AudioIODeviceType>::pointer raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::juce::AudioIODeviceType>(raw);
}
::std::unique_ptr<::juce::AudioIODeviceType>::element_type const *cxxbridge1$unique_ptr$juce$AudioIODeviceType$get(::std::unique_ptr<::juce::AudioIODeviceType> const &ptr) noexcept {
  return ptr.get();
}
::std::unique_ptr<::juce::AudioIODeviceType>::pointer cxxbridge1$unique_ptr$juce$AudioIODeviceType$release(::std::unique_ptr<::juce::AudioIODeviceType> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$juce$AudioIODeviceType$drop(::std::unique_ptr<::juce::AudioIODeviceType> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::juce::AudioIODeviceType>::value>{}(ptr);
}
} // extern "C"
