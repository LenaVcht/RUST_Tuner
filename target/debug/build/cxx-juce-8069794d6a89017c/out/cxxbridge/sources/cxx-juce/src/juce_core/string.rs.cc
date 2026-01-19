#include "cxx_juce.h"
#include <cstddef>
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
  enum class StringLayout : ::std::uint8_t;
  enum class CharPointer_UTF8Layout : ::std::uint8_t;
}

namespace juce {
#ifndef CXXBRIDGE1_ENUM_juce$StringLayout
#define CXXBRIDGE1_ENUM_juce$StringLayout
enum class StringLayout : ::std::uint8_t {
  Size = 8,
  Alignment = 8,
};
#endif // CXXBRIDGE1_ENUM_juce$StringLayout

#ifndef CXXBRIDGE1_ENUM_juce$CharPointer_UTF8Layout
#define CXXBRIDGE1_ENUM_juce$CharPointer_UTF8Layout
enum class CharPointer_UTF8Layout : ::std::uint8_t {
  Size = 8,
  Alignment = 8,
};
#endif // CXXBRIDGE1_ENUM_juce$CharPointer_UTF8Layout
} // namespace juce

static_assert(
    ::rust::IsRelocatable<::juce::JuceString>::value,
    "type juce::JuceString should be trivially move constructible and trivially destructible in C++ to be used as a return value of `string_new`, `string_clone`, `from_utf8` in Rust");
static_assert(
    ::rust::IsRelocatable<::juce::CharPointer_UTF8>::value,
    "type juce::CharPointer_UTF8 should be trivially move constructible and trivially destructible in C++ to be used as a return value of `to_utf8` in Rust");

namespace cxx_juce {
extern "C" {
void cxx_juce$cxxbridge1$string_new(::juce::JuceString *return$) noexcept {
  ::juce::JuceString (*string_new$)() = ::cxx_juce::construct;
  new (return$) ::juce::JuceString(string_new$());
}

void cxx_juce$cxxbridge1$string_drop(::juce::JuceString &self_) noexcept {
  void (*string_drop$)(::juce::JuceString &) = ::cxx_juce::drop;
  string_drop$(self_);
}

void cxx_juce$cxxbridge1$string_clone(::juce::JuceString const &self_, ::juce::JuceString *return$) noexcept {
  ::juce::JuceString (*string_clone$)(::juce::JuceString const &) = ::cxx_juce::construct;
  new (return$) ::juce::JuceString(string_clone$(self_));
}
} // extern "C"
} // namespace cxx_juce

namespace juce {
extern "C" {
void juce$cxxbridge1$JuceString$from_utf8(char const *data, ::std::int32_t len, ::juce::JuceString *return$) noexcept {
  ::juce::JuceString (*from_utf8$)(char const *, ::std::int32_t) = &::juce::JuceString::fromUTF8;
  new (return$) ::juce::JuceString(from_utf8$(data, len));
}

bool juce$cxxbridge1$JuceString$is_empty(::juce::JuceString const &self) noexcept {
  bool (::juce::JuceString::*is_empty$)() const = &::juce::JuceString::isEmpty;
  return (self.*is_empty$)();
}
} // extern "C"
} // namespace juce

namespace cxx_juce {
extern "C" {
bool cxx_juce$cxxbridge1$eq_string(::juce::JuceString const &a, ::juce::JuceString const &b) noexcept {
  bool (*eq_string$)(::juce::JuceString const &, ::juce::JuceString const &) = ::cxx_juce::eq;
  return eq_string$(a, b);
}
} // extern "C"
} // namespace cxx_juce

namespace juce {
extern "C" {
void juce$cxxbridge1$JuceString$to_utf8(::juce::JuceString const &self, ::juce::CharPointer_UTF8 *return$) noexcept {
  ::juce::CharPointer_UTF8 (::juce::JuceString::*to_utf8$)() const = &::juce::JuceString::toUTF8;
  new (return$) ::juce::CharPointer_UTF8((self.*to_utf8$)());
}

::std::size_t juce$cxxbridge1$JuceString$get_num_bytes_as_utf8(::juce::JuceString const &self) noexcept {
  ::std::size_t (::juce::JuceString::*get_num_bytes_as_utf8$)() const = &::juce::JuceString::getNumBytesAsUTF8;
  return (self.*get_num_bytes_as_utf8$)();
}

char *juce$cxxbridge1$CharPointer_UTF8$get_address(::juce::CharPointer_UTF8 const &self) noexcept {
  char *(::juce::CharPointer_UTF8::*get_address$)() const = &::juce::CharPointer_UTF8::getAddress;
  return (self.*get_address$)();
}
} // extern "C"
} // namespace juce
