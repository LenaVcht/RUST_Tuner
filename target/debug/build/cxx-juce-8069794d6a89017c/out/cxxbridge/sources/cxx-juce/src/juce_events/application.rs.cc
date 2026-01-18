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
  using JUCEApplicationBase = ::juce::JUCEApplicationBase;
}
namespace cxx_juce {
  struct JuceApplicationBaseImpl;
}

namespace cxx_juce {
#ifndef CXXBRIDGE1_STRUCT_cxx_juce$JuceApplicationBaseImpl
#define CXXBRIDGE1_STRUCT_cxx_juce$JuceApplicationBaseImpl
struct JuceApplicationBaseImpl final : public ::rust::Opaque {
  static void drop(::cxx_juce::BoxDynJuceApplicationBase *app) noexcept;
  static ::juce::JuceString getApplicationName(::cxx_juce::BoxDynJuceApplicationBase const &app) noexcept;
  static ::juce::JuceString getApplicationVersion(::cxx_juce::BoxDynJuceApplicationBase const &app) noexcept;
  static void initialise(::cxx_juce::BoxDynJuceApplicationBase &app, ::juce::JuceString const &command_line) noexcept;
  static void shutdown(::cxx_juce::BoxDynJuceApplicationBase &app) noexcept;
  static void systemRequestedQuit(::cxx_juce::BoxDynJuceApplicationBase &app) noexcept;
  static bool moreThanOneInstanceAllowed(::cxx_juce::BoxDynJuceApplicationBase const &app) noexcept;
  static void anotherInstanceStarted(::cxx_juce::BoxDynJuceApplicationBase &app, ::juce::JuceString const &command_line) noexcept;
  static void suspended(::cxx_juce::BoxDynJuceApplicationBase &app) noexcept;
  static void resumed(::cxx_juce::BoxDynJuceApplicationBase &app) noexcept;
  static void unhandledException(::cxx_juce::BoxDynJuceApplicationBase &app) noexcept;
  static void timerCallback(::cxx_juce::BoxDynJuceApplicationBase &app, ::std::int32_t timer_id) noexcept;
  ~JuceApplicationBaseImpl() = delete;

private:
  friend ::rust::layout;
  struct layout {
    static ::std::size_t size() noexcept;
    static ::std::size_t align() noexcept;
  };
};
#endif // CXXBRIDGE1_STRUCT_cxx_juce$JuceApplicationBaseImpl
} // namespace cxx_juce

static_assert(
    ::rust::IsRelocatable<::juce::JuceString>::value,
    "type juce::JuceString should be trivially move constructible and trivially destructible in C++ to be used as a return value of `get_application_name`, `get_application_version` in Rust");
static_assert(
    ::rust::IsRelocatable<::cxx_juce::BoxDynJuceApplicationBase>::value,
    "type cxx_juce::BoxDynJuceApplicationBase should be trivially move constructible and trivially destructible in C++ to be used as an argument of `wrap_juce_application` in Rust");

namespace cxx_juce {
extern "C" {
::juce::JUCEApplicationBase *cxx_juce$cxxbridge1$wrap_juce_application(::cxx_juce::BoxDynJuceApplicationBase *app) noexcept {
  ::std::unique_ptr<::juce::JUCEApplicationBase> (*wrap_juce_application$)(::cxx_juce::BoxDynJuceApplicationBase) = ::cxx_juce::wrap;
  return wrap_juce_application$(::std::move(*app)).release();
}

::cxx_juce::BoxDynJuceApplicationBase *cxx_juce$cxxbridge1$cast_app_instance() noexcept {
  ::cxx_juce::BoxDynJuceApplicationBase *(*cast_app_instance$)() = ::cxx_juce::castAppInstance;
  return cast_app_instance$();
}

::std::int32_t cxx_juce$cxxbridge1$run_app() noexcept {
  ::std::int32_t (*run_app$)() = ::cxx_juce::runApp;
  return run_app$();
}

void cxx_juce$cxxbridge1$start_app_timer(::std::int32_t id, ::std::int32_t interval) noexcept {
  void (*start_app_timer$)(::std::int32_t, ::std::int32_t) = ::cxx_juce::startAppTimer;
  start_app_timer$(id, interval);
}

void cxx_juce$cxxbridge1$stop_app_timer(::std::int32_t id) noexcept {
  void (*stop_app_timer$)(::std::int32_t) = ::cxx_juce::stopAppTimer;
  stop_app_timer$(id);
}
} // extern "C"
} // namespace cxx_juce

namespace juce {
extern "C" {
void juce$cxxbridge1$JUCEApplicationBase$quit() noexcept {
  void (*quit$)() = &::juce::JUCEApplicationBase::quit;
  quit$();
}
} // extern "C"
} // namespace juce

namespace cxx_juce {
extern "C" {
::juce::JUCEApplicationBase *cxx_juce$cxxbridge1$create_instance() noexcept;
::std::size_t cxx_juce$cxxbridge1$JuceApplicationBaseImpl$operator$sizeof() noexcept;
::std::size_t cxx_juce$cxxbridge1$JuceApplicationBaseImpl$operator$alignof() noexcept;

void cxx_juce$cxxbridge1$JuceApplicationBaseImpl$drop(::cxx_juce::BoxDynJuceApplicationBase *app) noexcept;

void cxx_juce$cxxbridge1$JuceApplicationBaseImpl$get_application_name(::cxx_juce::BoxDynJuceApplicationBase const &app, ::juce::JuceString *return$) noexcept;

void cxx_juce$cxxbridge1$JuceApplicationBaseImpl$get_application_version(::cxx_juce::BoxDynJuceApplicationBase const &app, ::juce::JuceString *return$) noexcept;

void cxx_juce$cxxbridge1$JuceApplicationBaseImpl$initialise(::cxx_juce::BoxDynJuceApplicationBase &app, ::juce::JuceString const &command_line) noexcept;

void cxx_juce$cxxbridge1$JuceApplicationBaseImpl$shutdown(::cxx_juce::BoxDynJuceApplicationBase &app) noexcept;

void cxx_juce$cxxbridge1$JuceApplicationBaseImpl$system_requested_quit(::cxx_juce::BoxDynJuceApplicationBase &app) noexcept;

bool cxx_juce$cxxbridge1$JuceApplicationBaseImpl$more_than_one_instance_allowed(::cxx_juce::BoxDynJuceApplicationBase const &app) noexcept;

void cxx_juce$cxxbridge1$JuceApplicationBaseImpl$another_instance_started(::cxx_juce::BoxDynJuceApplicationBase &app, ::juce::JuceString const &command_line) noexcept;

void cxx_juce$cxxbridge1$JuceApplicationBaseImpl$suspended(::cxx_juce::BoxDynJuceApplicationBase &app) noexcept;

void cxx_juce$cxxbridge1$JuceApplicationBaseImpl$resumed(::cxx_juce::BoxDynJuceApplicationBase &app) noexcept;

void cxx_juce$cxxbridge1$JuceApplicationBaseImpl$unhandled_exception(::cxx_juce::BoxDynJuceApplicationBase &app) noexcept;

void cxx_juce$cxxbridge1$JuceApplicationBaseImpl$timer_callback(::cxx_juce::BoxDynJuceApplicationBase &app, ::std::int32_t timer_id) noexcept;
} // extern "C"

::std::unique_ptr<::juce::JUCEApplicationBase> createInstance() noexcept {
  return ::std::unique_ptr<::juce::JUCEApplicationBase>(cxx_juce$cxxbridge1$create_instance());
}

::std::size_t JuceApplicationBaseImpl::layout::size() noexcept {
  return cxx_juce$cxxbridge1$JuceApplicationBaseImpl$operator$sizeof();
}

::std::size_t JuceApplicationBaseImpl::layout::align() noexcept {
  return cxx_juce$cxxbridge1$JuceApplicationBaseImpl$operator$alignof();
}

void JuceApplicationBaseImpl::drop(::cxx_juce::BoxDynJuceApplicationBase *app) noexcept {
  cxx_juce$cxxbridge1$JuceApplicationBaseImpl$drop(app);
}

::juce::JuceString JuceApplicationBaseImpl::getApplicationName(::cxx_juce::BoxDynJuceApplicationBase const &app) noexcept {
  ::rust::MaybeUninit<::juce::JuceString> return$;
  cxx_juce$cxxbridge1$JuceApplicationBaseImpl$get_application_name(app, &return$.value);
  return ::std::move(return$.value);
}

::juce::JuceString JuceApplicationBaseImpl::getApplicationVersion(::cxx_juce::BoxDynJuceApplicationBase const &app) noexcept {
  ::rust::MaybeUninit<::juce::JuceString> return$;
  cxx_juce$cxxbridge1$JuceApplicationBaseImpl$get_application_version(app, &return$.value);
  return ::std::move(return$.value);
}

void JuceApplicationBaseImpl::initialise(::cxx_juce::BoxDynJuceApplicationBase &app, ::juce::JuceString const &command_line) noexcept {
  cxx_juce$cxxbridge1$JuceApplicationBaseImpl$initialise(app, command_line);
}

void JuceApplicationBaseImpl::shutdown(::cxx_juce::BoxDynJuceApplicationBase &app) noexcept {
  cxx_juce$cxxbridge1$JuceApplicationBaseImpl$shutdown(app);
}

void JuceApplicationBaseImpl::systemRequestedQuit(::cxx_juce::BoxDynJuceApplicationBase &app) noexcept {
  cxx_juce$cxxbridge1$JuceApplicationBaseImpl$system_requested_quit(app);
}

bool JuceApplicationBaseImpl::moreThanOneInstanceAllowed(::cxx_juce::BoxDynJuceApplicationBase const &app) noexcept {
  return cxx_juce$cxxbridge1$JuceApplicationBaseImpl$more_than_one_instance_allowed(app);
}

void JuceApplicationBaseImpl::anotherInstanceStarted(::cxx_juce::BoxDynJuceApplicationBase &app, ::juce::JuceString const &command_line) noexcept {
  cxx_juce$cxxbridge1$JuceApplicationBaseImpl$another_instance_started(app, command_line);
}

void JuceApplicationBaseImpl::suspended(::cxx_juce::BoxDynJuceApplicationBase &app) noexcept {
  cxx_juce$cxxbridge1$JuceApplicationBaseImpl$suspended(app);
}

void JuceApplicationBaseImpl::resumed(::cxx_juce::BoxDynJuceApplicationBase &app) noexcept {
  cxx_juce$cxxbridge1$JuceApplicationBaseImpl$resumed(app);
}

void JuceApplicationBaseImpl::unhandledException(::cxx_juce::BoxDynJuceApplicationBase &app) noexcept {
  cxx_juce$cxxbridge1$JuceApplicationBaseImpl$unhandled_exception(app);
}

void JuceApplicationBaseImpl::timerCallback(::cxx_juce::BoxDynJuceApplicationBase &app, ::std::int32_t timer_id) noexcept {
  cxx_juce$cxxbridge1$JuceApplicationBaseImpl$timer_callback(app, timer_id);
}
} // namespace cxx_juce

extern "C" {
static_assert(::rust::detail::is_complete<::std::remove_extent<::juce::JUCEApplicationBase>::type>::value, "definition of `::juce::JUCEApplicationBase` is required");
static_assert(sizeof(::std::unique_ptr<::juce::JUCEApplicationBase>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::juce::JUCEApplicationBase>) == alignof(void *), "");
void cxxbridge1$unique_ptr$juce$JUCEApplicationBase$null(::std::unique_ptr<::juce::JUCEApplicationBase> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::juce::JUCEApplicationBase>();
}
void cxxbridge1$unique_ptr$juce$JUCEApplicationBase$raw(::std::unique_ptr<::juce::JUCEApplicationBase> *ptr, ::std::unique_ptr<::juce::JUCEApplicationBase>::pointer raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::juce::JUCEApplicationBase>(raw);
}
::std::unique_ptr<::juce::JUCEApplicationBase>::element_type const *cxxbridge1$unique_ptr$juce$JUCEApplicationBase$get(::std::unique_ptr<::juce::JUCEApplicationBase> const &ptr) noexcept {
  return ptr.get();
}
::std::unique_ptr<::juce::JUCEApplicationBase>::pointer cxxbridge1$unique_ptr$juce$JUCEApplicationBase$release(::std::unique_ptr<::juce::JUCEApplicationBase> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$juce$JUCEApplicationBase$drop(::std::unique_ptr<::juce::JUCEApplicationBase> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::juce::JUCEApplicationBase>::value>{}(ptr);
}
} // extern "C"
