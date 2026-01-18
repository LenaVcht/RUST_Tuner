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
  enum class FileLayout : ::std::uint8_t;
  enum class FileSearchPathLayout : ::std::uint8_t;
}

namespace juce {
#ifndef CXXBRIDGE1_ENUM_juce$FileLayout
#define CXXBRIDGE1_ENUM_juce$FileLayout
enum class FileLayout : ::std::uint8_t {
  Size = 8,
  Alignment = 8,
};
#endif // CXXBRIDGE1_ENUM_juce$FileLayout

#ifndef CXXBRIDGE1_ENUM_juce$FileSearchPathLayout
#define CXXBRIDGE1_ENUM_juce$FileSearchPathLayout
enum class FileSearchPathLayout : ::std::uint8_t {
  Size = 16,
  Alignment = 8,
};
#endif // CXXBRIDGE1_ENUM_juce$FileSearchPathLayout
} // namespace juce

static_assert(
    ::rust::IsRelocatable<::juce::File>::value,
    "type juce::File should be trivially move constructible and trivially destructible in C++ to be used as a return value of `file_new`, `file_clone`, `from_absolute_path` in Rust");
static_assert(
    ::rust::IsRelocatable<::juce::FileSearchPath>::value,
    "type juce::FileSearchPath should be trivially move constructible and trivially destructible in C++ to be used as a return value of `file_search_path_new` in Rust");
static_assert(
    ::rust::IsRelocatable<::juce::JuceString>::value,
    "type juce::JuceString should be trivially move constructible and trivially destructible in C++ to be used as a return value of `to_string` in Rust");

namespace cxx_juce {
extern "C" {
void cxx_juce$cxxbridge1$file_new(::juce::File *return$) noexcept {
  ::juce::File (*file_new$)() = ::cxx_juce::construct;
  new (return$) ::juce::File(file_new$());
}

void cxx_juce$cxxbridge1$file_drop(::juce::File &self_) noexcept {
  void (*file_drop$)(::juce::File &) = ::cxx_juce::drop;
  file_drop$(self_);
}

bool cxx_juce$cxxbridge1$file_equality(::juce::File const &self_, ::juce::File const &other) noexcept {
  bool (*file_equality$)(::juce::File const &, ::juce::File const &) = ::cxx_juce::eq;
  return file_equality$(self_, other);
}

void cxx_juce$cxxbridge1$file_clone(::juce::File const &other, ::juce::File *return$) noexcept {
  ::juce::File (*file_clone$)(::juce::File const &) = ::cxx_juce::construct;
  new (return$) ::juce::File(file_clone$(other));
}

void cxx_juce$cxxbridge1$from_absolute_path(::juce::JuceString const &path, ::juce::File *return$) noexcept {
  ::juce::File (*from_absolute_path$)(::juce::JuceString const &) = ::cxx_juce::construct;
  new (return$) ::juce::File(from_absolute_path$(path));
}
} // extern "C"
} // namespace cxx_juce

namespace juce {
extern "C" {
void juce$cxxbridge1$File$get_full_path_name(::juce::File const &self, ::juce::JuceString const **return$) noexcept {
  ::juce::JuceString const &(::juce::File::*get_full_path_name$)() const = &::juce::File::getFullPathName;
  new (return$) ::juce::JuceString const *(&(self.*get_full_path_name$)());
}
} // extern "C"
} // namespace juce

namespace cxx_juce {
extern "C" {
void cxx_juce$cxxbridge1$file_search_path_new(::juce::FileSearchPath *return$) noexcept {
  ::juce::FileSearchPath (*file_search_path_new$)() = ::cxx_juce::construct;
  new (return$) ::juce::FileSearchPath(file_search_path_new$());
}

void cxx_juce$cxxbridge1$file_search_path_drop(::juce::FileSearchPath &self_) noexcept {
  void (*file_search_path_drop$)(::juce::FileSearchPath &) = ::cxx_juce::drop;
  file_search_path_drop$(self_);
}
} // extern "C"
} // namespace cxx_juce

namespace juce {
extern "C" {
::std::int32_t juce$cxxbridge1$FileSearchPath$len(::juce::FileSearchPath const &self) noexcept {
  ::std::int32_t (::juce::FileSearchPath::*len$)() const = &::juce::FileSearchPath::getNumPaths;
  return (self.*len$)();
}
} // extern "C"
} // namespace juce

namespace cxx_juce {
extern "C" {
void cxx_juce$cxxbridge1$file_search_path_get(::juce::FileSearchPath const &self_, ::std::int32_t index, ::juce::File *return$) noexcept {
  ::juce::File (*file_search_path_get$)(::juce::FileSearchPath const &, ::std::int32_t) = ::cxx_juce::index;
  new (return$) ::juce::File(file_search_path_get$(self_, index));
}
} // extern "C"
} // namespace cxx_juce

namespace juce {
extern "C" {
bool juce$cxxbridge1$FileSearchPath$add(::juce::FileSearchPath &self, ::juce::File const &file) noexcept {
  bool (::juce::FileSearchPath::*add$)(::juce::File const &) = &::juce::FileSearchPath::addIfNotAlreadyThere;
  return (self.*add$)(file);
}

void juce$cxxbridge1$FileSearchPath$to_string(::juce::FileSearchPath const &self, ::juce::JuceString *return$) noexcept {
  ::juce::JuceString (::juce::FileSearchPath::*to_string$)() const = &::juce::FileSearchPath::toString;
  new (return$) ::juce::JuceString((self.*to_string$)());
}
} // extern "C"
} // namespace juce
