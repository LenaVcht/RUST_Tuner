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
  enum class TimeLayout : ::std::uint8_t;
}

namespace juce {
#ifndef CXXBRIDGE1_ENUM_juce$TimeLayout
#define CXXBRIDGE1_ENUM_juce$TimeLayout
enum class TimeLayout : ::std::uint8_t {
  Size = 8,
  Alignment = 8,
};
#endif // CXXBRIDGE1_ENUM_juce$TimeLayout
} // namespace juce

static_assert(
    ::rust::IsRelocatable<::juce::Time>::value,
    "type juce::Time should be trivially move constructible and trivially destructible in C++ to be used as a return value of `time_new` in Rust");

namespace cxx_juce {
extern "C" {
void cxx_juce$cxxbridge1$time_new(::std::int64_t milliseconds_since_epoch, ::juce::Time *return$) noexcept {
  ::juce::Time (*time_new$)(::std::int64_t) = ::cxx_juce::construct;
  new (return$) ::juce::Time(time_new$(milliseconds_since_epoch));
}
} // extern "C"
} // namespace cxx_juce

namespace juce {
extern "C" {
::std::int64_t juce$cxxbridge1$to_milliseconds(::juce::Time const &self_) noexcept {
  ::std::int64_t (*to_milliseconds$)(::juce::Time const &) = ::juce::toMilliseconds;
  return to_milliseconds$(self_);
}
} // extern "C"
} // namespace juce
