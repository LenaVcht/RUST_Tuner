#include "cxx_juce.h"
#include <cstdint>
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
  enum class ArrayLayout : ::std::uint8_t;
  enum class StringArrayLayout : ::std::uint8_t;
}

namespace juce {
#ifndef CXXBRIDGE1_ENUM_juce$ArrayLayout
#define CXXBRIDGE1_ENUM_juce$ArrayLayout
enum class ArrayLayout : ::std::uint8_t {
  Size = 16,
  Alignment = 8,
};
#endif // CXXBRIDGE1_ENUM_juce$ArrayLayout

#ifndef CXXBRIDGE1_ENUM_juce$StringArrayLayout
#define CXXBRIDGE1_ENUM_juce$StringArrayLayout
enum class StringArrayLayout : ::std::uint8_t {
  Size = 16,
  Alignment = 8,
};
#endif // CXXBRIDGE1_ENUM_juce$StringArrayLayout
} // namespace juce

static_assert(
    ::rust::IsRelocatable<::juce::JuceString>::value,
    "type juce::JuceString should be trivially move constructible and trivially destructible in C++ to be used as an argument of `add` in Rust");
static_assert(
    ::rust::IsRelocatable<::juce::IntArray>::value,
    "type juce::IntArray should be trivially move constructible and trivially destructible in C++ to be used as a return value of `int_array_new`, `int_array_new_from_slice` in Rust");
static_assert(
    ::rust::IsRelocatable<::juce::FloatArray>::value,
    "type juce::FloatArray should be trivially move constructible and trivially destructible in C++ to be used as a return value of `float_array_new`, `float_array_new_from_slice` in Rust");
static_assert(
    ::rust::IsRelocatable<::juce::DoubleArray>::value,
    "type juce::DoubleArray should be trivially move constructible and trivially destructible in C++ to be used as a return value of `double_array_new`, `double_array_new_from_slice` in Rust");
static_assert(
    ::rust::IsRelocatable<::juce::StringArray>::value,
    "type juce::StringArray should be trivially move constructible and trivially destructible in C++ to be used as a return value of `string_array_new`, `string_array_clone` in Rust");

namespace cxx_juce {
extern "C" {
void cxx_juce$cxxbridge1$int_array_new(::juce::IntArray *return$) noexcept {
  ::juce::IntArray (*int_array_new$)() = ::cxx_juce::construct;
  new (return$) ::juce::IntArray(int_array_new$());
}

void cxx_juce$cxxbridge1$int_array_new_from_slice(::std::int32_t const *ptr, ::std::int32_t size, ::juce::IntArray *return$) noexcept {
  ::juce::IntArray (*int_array_new_from_slice$)(::std::int32_t const *, ::std::int32_t) = ::cxx_juce::construct;
  new (return$) ::juce::IntArray(int_array_new_from_slice$(ptr, size));
}

void cxx_juce$cxxbridge1$int_array_drop(::juce::IntArray &value) noexcept {
  void (*int_array_drop$)(::juce::IntArray &) = ::cxx_juce::drop;
  int_array_drop$(value);
}
} // extern "C"
} // namespace cxx_juce

namespace juce {
extern "C" {
::std::int32_t const *juce$cxxbridge1$IntArray$data(::juce::IntArray const &self) noexcept {
  ::std::int32_t const *(::juce::IntArray::*data$)() const = &::juce::IntArray::getRawDataPointer;
  return (self.*data$)();
}

::std::int32_t juce$cxxbridge1$IntArray$len(::juce::IntArray const &self) noexcept {
  ::std::int32_t (::juce::IntArray::*len$)() const = &::juce::IntArray::size;
  return (self.*len$)();
}

void juce$cxxbridge1$IntArray$add(::juce::IntArray &self, ::std::int32_t const &value) noexcept {
  void (::juce::IntArray::*add$)(::std::int32_t const &) = &::juce::IntArray::add;
  (self.*add$)(value);
}
} // extern "C"
} // namespace juce

namespace cxx_juce {
extern "C" {
void cxx_juce$cxxbridge1$float_array_new(::juce::FloatArray *return$) noexcept {
  ::juce::FloatArray (*float_array_new$)() = ::cxx_juce::construct;
  new (return$) ::juce::FloatArray(float_array_new$());
}

void cxx_juce$cxxbridge1$float_array_new_from_slice(float const *ptr, ::std::int32_t size, ::juce::FloatArray *return$) noexcept {
  ::juce::FloatArray (*float_array_new_from_slice$)(float const *, ::std::int32_t) = ::cxx_juce::construct;
  new (return$) ::juce::FloatArray(float_array_new_from_slice$(ptr, size));
}

void cxx_juce$cxxbridge1$float_array_drop(::juce::FloatArray &value) noexcept {
  void (*float_array_drop$)(::juce::FloatArray &) = ::cxx_juce::drop;
  float_array_drop$(value);
}
} // extern "C"
} // namespace cxx_juce

namespace juce {
extern "C" {
float const *juce$cxxbridge1$FloatArray$data(::juce::FloatArray const &self) noexcept {
  float const *(::juce::FloatArray::*data$)() const = &::juce::FloatArray::getRawDataPointer;
  return (self.*data$)();
}

::std::int32_t juce$cxxbridge1$FloatArray$len(::juce::FloatArray const &self) noexcept {
  ::std::int32_t (::juce::FloatArray::*len$)() const = &::juce::FloatArray::size;
  return (self.*len$)();
}

void juce$cxxbridge1$FloatArray$add(::juce::FloatArray &self, float const &value) noexcept {
  void (::juce::FloatArray::*add$)(float const &) = &::juce::FloatArray::add;
  (self.*add$)(value);
}
} // extern "C"
} // namespace juce

namespace cxx_juce {
extern "C" {
void cxx_juce$cxxbridge1$double_array_new(::juce::DoubleArray *return$) noexcept {
  ::juce::DoubleArray (*double_array_new$)() = ::cxx_juce::construct;
  new (return$) ::juce::DoubleArray(double_array_new$());
}

void cxx_juce$cxxbridge1$double_array_new_from_slice(double const *ptr, ::std::int32_t size, ::juce::DoubleArray *return$) noexcept {
  ::juce::DoubleArray (*double_array_new_from_slice$)(double const *, ::std::int32_t) = ::cxx_juce::construct;
  new (return$) ::juce::DoubleArray(double_array_new_from_slice$(ptr, size));
}

void cxx_juce$cxxbridge1$double_array_drop(::juce::DoubleArray &value) noexcept {
  void (*double_array_drop$)(::juce::DoubleArray &) = ::cxx_juce::drop;
  double_array_drop$(value);
}
} // extern "C"
} // namespace cxx_juce

namespace juce {
extern "C" {
double const *juce$cxxbridge1$DoubleArray$data(::juce::DoubleArray const &self) noexcept {
  double const *(::juce::DoubleArray::*data$)() const = &::juce::DoubleArray::getRawDataPointer;
  return (self.*data$)();
}

::std::int32_t juce$cxxbridge1$DoubleArray$len(::juce::DoubleArray const &self) noexcept {
  ::std::int32_t (::juce::DoubleArray::*len$)() const = &::juce::DoubleArray::size;
  return (self.*len$)();
}

void juce$cxxbridge1$DoubleArray$add(::juce::DoubleArray &self, double const &value) noexcept {
  void (::juce::DoubleArray::*add$)(double const &) = &::juce::DoubleArray::add;
  (self.*add$)(value);
}
} // extern "C"
} // namespace juce

namespace cxx_juce {
extern "C" {
void cxx_juce$cxxbridge1$string_array_new(::juce::StringArray *return$) noexcept {
  ::juce::StringArray (*string_array_new$)() = ::cxx_juce::construct;
  new (return$) ::juce::StringArray(string_array_new$());
}

void cxx_juce$cxxbridge1$string_array_drop(::juce::StringArray &value) noexcept {
  void (*string_array_drop$)(::juce::StringArray &) = ::cxx_juce::drop;
  string_array_drop$(value);
}

void cxx_juce$cxxbridge1$string_array_clone(::juce::StringArray const &value, ::juce::StringArray *return$) noexcept {
  ::juce::StringArray (*string_array_clone$)(::juce::StringArray const &) = ::cxx_juce::construct;
  new (return$) ::juce::StringArray(string_array_clone$(value));
}

bool cxx_juce$cxxbridge1$string_array_equality(::juce::StringArray const &value, ::juce::StringArray const &other) noexcept {
  bool (*string_array_equality$)(::juce::StringArray const &, ::juce::StringArray const &) = ::cxx_juce::eq;
  return string_array_equality$(value, other);
}

::juce::JuceString const *cxx_juce$cxxbridge1$StringArray$data(::juce::StringArray const &self) noexcept {
  ::juce::JuceString const *(::juce::StringArray::*data$)() const = &::juce::StringArray::begin;
  return (self.*data$)();
}
} // extern "C"
} // namespace cxx_juce

namespace juce {
extern "C" {
void juce$cxxbridge1$StringArray$add(::juce::StringArray &self, ::juce::JuceString *value) noexcept {
  void (::juce::StringArray::*add$)(::juce::JuceString) = &::juce::StringArray::add;
  (self.*add$)(::std::move(*value));
}

void juce$cxxbridge1$StringArray$get_reference(::juce::StringArray const &self, ::std::int32_t index, ::juce::JuceString const **return$) noexcept {
  ::juce::JuceString const &(::juce::StringArray::*get_reference$)(::std::int32_t) const = &::juce::StringArray::getReference;
  new (return$) ::juce::JuceString const *(&(self.*get_reference$)(index));
}

::std::int32_t juce$cxxbridge1$StringArray$len(::juce::StringArray const &self) noexcept {
  ::std::int32_t (::juce::StringArray::*len$)() const = &::juce::StringArray::size;
  return (self.*len$)();
}
} // extern "C"
} // namespace juce
