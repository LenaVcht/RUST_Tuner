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
  using AudioIODeviceCallback = ::juce::AudioIODeviceCallback;
}
namespace cxx_juce {
  struct AudioDeviceCallbackImpl;
}

namespace cxx_juce {
#ifndef CXXBRIDGE1_STRUCT_cxx_juce$AudioDeviceCallbackImpl
#define CXXBRIDGE1_STRUCT_cxx_juce$AudioDeviceCallbackImpl
struct AudioDeviceCallbackImpl final : public ::rust::Opaque {
  static void drop(::cxx_juce::BoxDynAudioDeviceCallback *callback) noexcept;
  static void about_to_start(::cxx_juce::BoxDynAudioDeviceCallback &callback, ::juce::AudioIODevice &device) noexcept;
  static void process_block(::cxx_juce::BoxDynAudioDeviceCallback &callback, ::juce::AudioSampleBuffer const &input, ::juce::AudioSampleBuffer &output) noexcept;
  static void stopped(::cxx_juce::BoxDynAudioDeviceCallback &callback) noexcept;
  ~AudioDeviceCallbackImpl() = delete;

private:
  friend ::rust::layout;
  struct layout {
    static ::std::size_t size() noexcept;
    static ::std::size_t align() noexcept;
  };
};
#endif // CXXBRIDGE1_STRUCT_cxx_juce$AudioDeviceCallbackImpl
} // namespace cxx_juce

static_assert(
    ::rust::IsRelocatable<::cxx_juce::BoxDynAudioDeviceCallback>::value,
    "type cxx_juce::BoxDynAudioDeviceCallback should be trivially move constructible and trivially destructible in C++ to be used as an argument of `wrap_audio_device_callback` in Rust");

namespace cxx_juce {
extern "C" {
::juce::AudioIODeviceCallback *cxx_juce$cxxbridge1$wrap_audio_device_callback(::cxx_juce::BoxDynAudioDeviceCallback *callback) noexcept {
  ::std::unique_ptr<::juce::AudioIODeviceCallback> (*wrap_audio_device_callback$)(::cxx_juce::BoxDynAudioDeviceCallback) = ::cxx_juce::wrap;
  return wrap_audio_device_callback$(::std::move(*callback)).release();
}
::std::size_t cxx_juce$cxxbridge1$AudioDeviceCallbackImpl$operator$sizeof() noexcept;
::std::size_t cxx_juce$cxxbridge1$AudioDeviceCallbackImpl$operator$alignof() noexcept;

void cxx_juce$cxxbridge1$AudioDeviceCallbackImpl$drop(::cxx_juce::BoxDynAudioDeviceCallback *callback) noexcept;

void cxx_juce$cxxbridge1$AudioDeviceCallbackImpl$about_to_start(::cxx_juce::BoxDynAudioDeviceCallback &callback, ::juce::AudioIODevice &device) noexcept;

void cxx_juce$cxxbridge1$AudioDeviceCallbackImpl$process_block(::cxx_juce::BoxDynAudioDeviceCallback &callback, ::juce::AudioSampleBuffer const &input, ::juce::AudioSampleBuffer &output) noexcept;

void cxx_juce$cxxbridge1$AudioDeviceCallbackImpl$stopped(::cxx_juce::BoxDynAudioDeviceCallback &callback) noexcept;
} // extern "C"

::std::size_t AudioDeviceCallbackImpl::layout::size() noexcept {
  return cxx_juce$cxxbridge1$AudioDeviceCallbackImpl$operator$sizeof();
}

::std::size_t AudioDeviceCallbackImpl::layout::align() noexcept {
  return cxx_juce$cxxbridge1$AudioDeviceCallbackImpl$operator$alignof();
}

void AudioDeviceCallbackImpl::drop(::cxx_juce::BoxDynAudioDeviceCallback *callback) noexcept {
  cxx_juce$cxxbridge1$AudioDeviceCallbackImpl$drop(callback);
}

void AudioDeviceCallbackImpl::about_to_start(::cxx_juce::BoxDynAudioDeviceCallback &callback, ::juce::AudioIODevice &device) noexcept {
  cxx_juce$cxxbridge1$AudioDeviceCallbackImpl$about_to_start(callback, device);
}

void AudioDeviceCallbackImpl::process_block(::cxx_juce::BoxDynAudioDeviceCallback &callback, ::juce::AudioSampleBuffer const &input, ::juce::AudioSampleBuffer &output) noexcept {
  cxx_juce$cxxbridge1$AudioDeviceCallbackImpl$process_block(callback, input, output);
}

void AudioDeviceCallbackImpl::stopped(::cxx_juce::BoxDynAudioDeviceCallback &callback) noexcept {
  cxx_juce$cxxbridge1$AudioDeviceCallbackImpl$stopped(callback);
}
} // namespace cxx_juce

extern "C" {
static_assert(::rust::detail::is_complete<::std::remove_extent<::juce::AudioIODeviceCallback>::type>::value, "definition of `::juce::AudioIODeviceCallback` is required");
static_assert(sizeof(::std::unique_ptr<::juce::AudioIODeviceCallback>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::juce::AudioIODeviceCallback>) == alignof(void *), "");
void cxxbridge1$unique_ptr$juce$AudioIODeviceCallback$null(::std::unique_ptr<::juce::AudioIODeviceCallback> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::juce::AudioIODeviceCallback>();
}
void cxxbridge1$unique_ptr$juce$AudioIODeviceCallback$raw(::std::unique_ptr<::juce::AudioIODeviceCallback> *ptr, ::std::unique_ptr<::juce::AudioIODeviceCallback>::pointer raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::juce::AudioIODeviceCallback>(raw);
}
::std::unique_ptr<::juce::AudioIODeviceCallback>::element_type const *cxxbridge1$unique_ptr$juce$AudioIODeviceCallback$get(::std::unique_ptr<::juce::AudioIODeviceCallback> const &ptr) noexcept {
  return ptr.get();
}
::std::unique_ptr<::juce::AudioIODeviceCallback>::pointer cxxbridge1$unique_ptr$juce$AudioIODeviceCallback$release(::std::unique_ptr<::juce::AudioIODeviceCallback> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$juce$AudioIODeviceCallback$drop(::std::unique_ptr<::juce::AudioIODeviceCallback> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::juce::AudioIODeviceCallback>::value>{}(ptr);
}
} // extern "C"
