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
  enum class BigIntegerLayout : ::std::uint8_t;
}

namespace juce {
#ifndef CXXBRIDGE1_ENUM_juce$BigIntegerLayout
#define CXXBRIDGE1_ENUM_juce$BigIntegerLayout
enum class BigIntegerLayout : ::std::uint8_t {
  Size = 40,
  Alignment = 8,
};
#endif // CXXBRIDGE1_ENUM_juce$BigIntegerLayout
} // namespace juce

static_assert(
    ::rust::IsRelocatable<::juce::BigInteger>::value,
    "type juce::BigInteger should be trivially move constructible and trivially destructible in C++ to be used as a return value of `big_integer_new` in Rust");

namespace cxx_juce {
extern "C" {
void cxx_juce$cxxbridge1$big_integer_new(::juce::BigInteger *return$) noexcept {
  ::juce::BigInteger (*big_integer_new$)() = ::cxx_juce::construct;
  new (return$) ::juce::BigInteger(big_integer_new$());
}

void cxx_juce$cxxbridge1$big_integer_drop(::juce::BigInteger &self_) noexcept {
  void (*big_integer_drop$)(::juce::BigInteger &) = ::cxx_juce::drop;
  big_integer_drop$(self_);
}
} // extern "C"
} // namespace cxx_juce

namespace juce {
extern "C" {
::std::int32_t juce$cxxbridge1$BigInteger$count_number_of_set_bits(::juce::BigInteger const &self) noexcept {
  ::std::int32_t (::juce::BigInteger::*count_number_of_set_bits$)() const = &::juce::BigInteger::countNumberOfSetBits;
  return (self.*count_number_of_set_bits$)();
}

void juce$cxxbridge1$BigInteger$clear(::juce::BigInteger &self, ::juce::BigInteger **return$) noexcept {
  ::juce::BigInteger &(::juce::BigInteger::*clear$)() = &::juce::BigInteger::clear;
  new (return$) ::juce::BigInteger *(&(self.*clear$)());
}

void juce$cxxbridge1$BigInteger$set_range(::juce::BigInteger &self, ::std::int32_t start_bit, ::std::int32_t num_bits, bool should_be_set, ::juce::BigInteger **return$) noexcept {
  ::juce::BigInteger &(::juce::BigInteger::*set_range$)(::std::int32_t, ::std::int32_t, bool) = &::juce::BigInteger::setRange;
  new (return$) ::juce::BigInteger *(&(self.*set_range$)(start_bit, num_bits, should_be_set));
}
} // extern "C"
} // namespace juce
