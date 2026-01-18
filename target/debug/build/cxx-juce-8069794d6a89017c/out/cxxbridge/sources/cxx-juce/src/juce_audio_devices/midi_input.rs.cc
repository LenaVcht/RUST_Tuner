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
  using MidiInput = ::juce::MidiInput;
  using MidiInputCallback = ::juce::MidiInputCallback;
}
namespace cxx_juce {
  struct MidiInputCallbackImpl;
}

namespace cxx_juce {
#ifndef CXXBRIDGE1_STRUCT_cxx_juce$MidiInputCallbackImpl
#define CXXBRIDGE1_STRUCT_cxx_juce$MidiInputCallbackImpl
struct MidiInputCallbackImpl final : public ::rust::Opaque {
  static void drop(::cxx_juce::BoxDynMidiInputCallback *callback) noexcept;
  static void handle_incoming_midi_message(::cxx_juce::BoxDynMidiInputCallback &callback, ::juce::MidiMessage const &message) noexcept;
  ~MidiInputCallbackImpl() = delete;

private:
  friend ::rust::layout;
  struct layout {
    static ::std::size_t size() noexcept;
    static ::std::size_t align() noexcept;
  };
};
#endif // CXXBRIDGE1_STRUCT_cxx_juce$MidiInputCallbackImpl
} // namespace cxx_juce

static_assert(
    ::rust::IsRelocatable<::juce::MidiDeviceInfo>::value,
    "type juce::MidiDeviceInfo should be trivially move constructible and trivially destructible in C++ to be used as a return value of `get_default_device`, `get_device_info` in Rust");
static_assert(
    ::rust::IsRelocatable<::juce::MidiDeviceInfoArray>::value,
    "type juce::MidiDeviceInfoArray should be trivially move constructible and trivially destructible in C++ to be used as a return value of `get_available_devices` in Rust");
static_assert(
    ::rust::IsRelocatable<::cxx_juce::BoxDynMidiInputCallback>::value,
    "type cxx_juce::BoxDynMidiInputCallback should be trivially move constructible and trivially destructible in C++ to be used as an argument of `wrap_midi_input_callback` in Rust");

namespace cxx_juce {
extern "C" {
::juce::MidiInputCallback *cxx_juce$cxxbridge1$wrap_midi_input_callback(::cxx_juce::BoxDynMidiInputCallback *callback) noexcept {
  ::std::unique_ptr<::juce::MidiInputCallback> (*wrap_midi_input_callback$)(::cxx_juce::BoxDynMidiInputCallback) = ::cxx_juce::wrap;
  return wrap_midi_input_callback$(::std::move(*callback)).release();
}
} // extern "C"
} // namespace cxx_juce

namespace juce {
extern "C" {
void juce$cxxbridge1$MidiInput$get_available_devices(::juce::MidiDeviceInfoArray *return$) noexcept {
  ::juce::MidiDeviceInfoArray (*get_available_devices$)() = &::juce::MidiInput::getAvailableDevices;
  new (return$) ::juce::MidiDeviceInfoArray(get_available_devices$());
}

void juce$cxxbridge1$MidiInput$get_default_device(::juce::MidiDeviceInfo *return$) noexcept {
  ::juce::MidiDeviceInfo (*get_default_device$)() = &::juce::MidiInput::getDefaultDevice;
  new (return$) ::juce::MidiDeviceInfo(get_default_device$());
}

::juce::MidiInput *juce$cxxbridge1$MidiInput$open_device(::juce::JuceString const &device_identifier, ::juce::MidiInputCallback *callback) noexcept {
  ::std::unique_ptr<::juce::MidiInput> (*open_device$)(::juce::JuceString const &, ::juce::MidiInputCallback *) = &::juce::MidiInput::openDevice;
  return open_device$(device_identifier, callback).release();
}

void juce$cxxbridge1$MidiInput$get_device_info(::juce::MidiInput const &self, ::juce::MidiDeviceInfo *return$) noexcept {
  ::juce::MidiDeviceInfo (::juce::MidiInput::*get_device_info$)() const = &::juce::MidiInput::getDeviceInfo;
  new (return$) ::juce::MidiDeviceInfo((self.*get_device_info$)());
}

void juce$cxxbridge1$MidiInput$start(::juce::MidiInput &self) noexcept {
  void (::juce::MidiInput::*start$)() = &::juce::MidiInput::start;
  (self.*start$)();
}

void juce$cxxbridge1$MidiInput$stop(::juce::MidiInput &self) noexcept {
  void (::juce::MidiInput::*stop$)() = &::juce::MidiInput::stop;
  (self.*stop$)();
}
} // extern "C"
} // namespace juce

namespace cxx_juce {
extern "C" {
::std::size_t cxx_juce$cxxbridge1$MidiInputCallbackImpl$operator$sizeof() noexcept;
::std::size_t cxx_juce$cxxbridge1$MidiInputCallbackImpl$operator$alignof() noexcept;

void cxx_juce$cxxbridge1$MidiInputCallbackImpl$drop(::cxx_juce::BoxDynMidiInputCallback *callback) noexcept;

void cxx_juce$cxxbridge1$MidiInputCallbackImpl$handle_incoming_midi_message(::cxx_juce::BoxDynMidiInputCallback &callback, ::juce::MidiMessage const &message) noexcept;
} // extern "C"

::std::size_t MidiInputCallbackImpl::layout::size() noexcept {
  return cxx_juce$cxxbridge1$MidiInputCallbackImpl$operator$sizeof();
}

::std::size_t MidiInputCallbackImpl::layout::align() noexcept {
  return cxx_juce$cxxbridge1$MidiInputCallbackImpl$operator$alignof();
}

void MidiInputCallbackImpl::drop(::cxx_juce::BoxDynMidiInputCallback *callback) noexcept {
  cxx_juce$cxxbridge1$MidiInputCallbackImpl$drop(callback);
}

void MidiInputCallbackImpl::handle_incoming_midi_message(::cxx_juce::BoxDynMidiInputCallback &callback, ::juce::MidiMessage const &message) noexcept {
  cxx_juce$cxxbridge1$MidiInputCallbackImpl$handle_incoming_midi_message(callback, message);
}
} // namespace cxx_juce

extern "C" {
static_assert(::rust::detail::is_complete<::std::remove_extent<::juce::MidiInputCallback>::type>::value, "definition of `::juce::MidiInputCallback` is required");
static_assert(sizeof(::std::unique_ptr<::juce::MidiInputCallback>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::juce::MidiInputCallback>) == alignof(void *), "");
void cxxbridge1$unique_ptr$juce$MidiInputCallback$null(::std::unique_ptr<::juce::MidiInputCallback> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::juce::MidiInputCallback>();
}
void cxxbridge1$unique_ptr$juce$MidiInputCallback$raw(::std::unique_ptr<::juce::MidiInputCallback> *ptr, ::std::unique_ptr<::juce::MidiInputCallback>::pointer raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::juce::MidiInputCallback>(raw);
}
::std::unique_ptr<::juce::MidiInputCallback>::element_type const *cxxbridge1$unique_ptr$juce$MidiInputCallback$get(::std::unique_ptr<::juce::MidiInputCallback> const &ptr) noexcept {
  return ptr.get();
}
::std::unique_ptr<::juce::MidiInputCallback>::pointer cxxbridge1$unique_ptr$juce$MidiInputCallback$release(::std::unique_ptr<::juce::MidiInputCallback> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$juce$MidiInputCallback$drop(::std::unique_ptr<::juce::MidiInputCallback> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::juce::MidiInputCallback>::value>{}(ptr);
}

static_assert(::rust::detail::is_complete<::std::remove_extent<::juce::MidiInput>::type>::value, "definition of `::juce::MidiInput` is required");
static_assert(sizeof(::std::unique_ptr<::juce::MidiInput>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::juce::MidiInput>) == alignof(void *), "");
void cxxbridge1$unique_ptr$juce$MidiInput$null(::std::unique_ptr<::juce::MidiInput> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::juce::MidiInput>();
}
void cxxbridge1$unique_ptr$juce$MidiInput$raw(::std::unique_ptr<::juce::MidiInput> *ptr, ::std::unique_ptr<::juce::MidiInput>::pointer raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::juce::MidiInput>(raw);
}
::std::unique_ptr<::juce::MidiInput>::element_type const *cxxbridge1$unique_ptr$juce$MidiInput$get(::std::unique_ptr<::juce::MidiInput> const &ptr) noexcept {
  return ptr.get();
}
::std::unique_ptr<::juce::MidiInput>::pointer cxxbridge1$unique_ptr$juce$MidiInput$release(::std::unique_ptr<::juce::MidiInput> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$juce$MidiInput$drop(::std::unique_ptr<::juce::MidiInput> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::juce::MidiInput>::value>{}(ptr);
}
} // extern "C"
