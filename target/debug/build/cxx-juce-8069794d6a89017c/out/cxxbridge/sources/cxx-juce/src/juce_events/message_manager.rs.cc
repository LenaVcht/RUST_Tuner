#include "cxx_juce.h"
#include <cstddef>
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
} // namespace cxxbridge1
} // namespace rust

namespace juce {
  using MessageManager = ::juce::MessageManager;
}
namespace cxx_juce {
  struct CallAsyncCallbackImpl;
}

namespace cxx_juce {
#ifndef CXXBRIDGE1_STRUCT_cxx_juce$CallAsyncCallbackImpl
#define CXXBRIDGE1_STRUCT_cxx_juce$CallAsyncCallbackImpl
struct CallAsyncCallbackImpl final : public ::rust::Opaque {
  static void drop(::cxx_juce::BoxDynCallAsyncCallback *callback) noexcept;
  static void call(::cxx_juce::BoxDynCallAsyncCallback &callback) noexcept;
  ~CallAsyncCallbackImpl() = delete;

private:
  friend ::rust::layout;
  struct layout {
    static ::std::size_t size() noexcept;
    static ::std::size_t align() noexcept;
  };
};
#endif // CXXBRIDGE1_STRUCT_cxx_juce$CallAsyncCallbackImpl
} // namespace cxx_juce

static_assert(
    ::rust::IsRelocatable<::cxx_juce::BoxDynCallAsyncCallback>::value,
    "type cxx_juce::BoxDynCallAsyncCallback should be trivially move constructible and trivially destructible in C++ to be used as an argument of `call_async` in Rust");

namespace cxx_juce {
extern "C" {
void cxx_juce$cxxbridge1$call_async(::cxx_juce::BoxDynCallAsyncCallback *callback) noexcept {
  void (*call_async$)(::cxx_juce::BoxDynCallAsyncCallback) = ::cxx_juce::callAsync;
  call_async$(::std::move(*callback));
}

bool cxx_juce$cxxbridge1$has_stop_message_been_sent() noexcept {
  bool (*has_stop_message_been_sent$)() = ::cxx_juce::hasStopMessageBeenSent;
  return has_stop_message_been_sent$();
}

void cxx_juce$cxxbridge1$run_dispatch_loop() noexcept {
  void (*run_dispatch_loop$)() = ::cxx_juce::runDispatchLoop;
  run_dispatch_loop$();
}

void cxx_juce$cxxbridge1$stop_dispatch_loop() noexcept {
  void (*stop_dispatch_loop$)() = ::cxx_juce::stopDispatchLoop;
  stop_dispatch_loop$();
}
::std::size_t cxx_juce$cxxbridge1$CallAsyncCallbackImpl$operator$sizeof() noexcept;
::std::size_t cxx_juce$cxxbridge1$CallAsyncCallbackImpl$operator$alignof() noexcept;

void cxx_juce$cxxbridge1$CallAsyncCallbackImpl$drop(::cxx_juce::BoxDynCallAsyncCallback *callback) noexcept;

void cxx_juce$cxxbridge1$CallAsyncCallbackImpl$call(::cxx_juce::BoxDynCallAsyncCallback &callback) noexcept;
} // extern "C"

::std::size_t CallAsyncCallbackImpl::layout::size() noexcept {
  return cxx_juce$cxxbridge1$CallAsyncCallbackImpl$operator$sizeof();
}

::std::size_t CallAsyncCallbackImpl::layout::align() noexcept {
  return cxx_juce$cxxbridge1$CallAsyncCallbackImpl$operator$alignof();
}

void CallAsyncCallbackImpl::drop(::cxx_juce::BoxDynCallAsyncCallback *callback) noexcept {
  cxx_juce$cxxbridge1$CallAsyncCallbackImpl$drop(callback);
}

void CallAsyncCallbackImpl::call(::cxx_juce::BoxDynCallAsyncCallback &callback) noexcept {
  cxx_juce$cxxbridge1$CallAsyncCallbackImpl$call(callback);
}
} // namespace cxx_juce
