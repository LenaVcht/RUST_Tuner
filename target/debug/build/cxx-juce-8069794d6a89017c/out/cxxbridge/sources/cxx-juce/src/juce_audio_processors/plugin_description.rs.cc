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
  enum class PluginDescriptionLayout : ::std::uint8_t;
}

namespace juce {
#ifndef CXXBRIDGE1_ENUM_juce$PluginDescriptionLayout
#define CXXBRIDGE1_ENUM_juce$PluginDescriptionLayout
enum class PluginDescriptionLayout : ::std::uint8_t {
  Size = 96,
  Alignment = 8,
  NameOffset = 0,
  DescriptiveNameOffset = 8,
  PluginFormatNameOffset = 16,
  CategoryOffset = 24,
  ManufacturerNameOffset = 32,
  VersionOffset = 40,
  FileOrIdentifierOffset = 48,
  LastFileModTimeOffset = 56,
  LastInfoUpdateTimeOffset = 64,
  DeprecatedUidOffset = 72,
  UniqueIdOffset = 76,
  IsInstrumentOffset = 80,
  NumInputChannelsOffset = 84,
  NumOutputChannelsOffset = 88,
  HasSharedContainerOffset = 92,
  HasAraExtensionOffset = 93,
};
#endif // CXXBRIDGE1_ENUM_juce$PluginDescriptionLayout
} // namespace juce

static_assert(
    ::rust::IsRelocatable<::juce::PluginDescription>::value,
    "type juce::PluginDescription should be trivially move constructible and trivially destructible in C++ to be used as a return value of `plugin_description_new`, `plugin_description_clone` in Rust");
static_assert(
    ::rust::IsRelocatable<::juce::OwnedArrayPluginDescription>::value,
    "type juce::OwnedArrayPluginDescription should be trivially move constructible and trivially destructible in C++ to be used as a return value of `owned_array_plugin_description_new` in Rust");
static_assert(
    ::rust::IsRelocatable<::juce::JuceString>::value,
    "type juce::JuceString should be trivially move constructible and trivially destructible in C++ to be used as a return value of `create_identifier_string` in Rust");

namespace cxx_juce {
extern "C" {
void cxx_juce$cxxbridge1$plugin_description_new(::juce::PluginDescription *return$) noexcept {
  ::juce::PluginDescription (*plugin_description_new$)() = ::cxx_juce::construct;
  new (return$) ::juce::PluginDescription(plugin_description_new$());
}

void cxx_juce$cxxbridge1$plugin_description_clone(::juce::PluginDescription const &plugin, ::juce::PluginDescription *return$) noexcept {
  ::juce::PluginDescription (*plugin_description_clone$)(::juce::PluginDescription const &) = ::cxx_juce::construct;
  new (return$) ::juce::PluginDescription(plugin_description_clone$(plugin));
}
} // extern "C"
} // namespace cxx_juce

namespace juce {
extern "C" {
void juce$cxxbridge1$PluginDescription$create_identifier_string(::juce::PluginDescription const &self, ::juce::JuceString *return$) noexcept {
  ::juce::JuceString (::juce::PluginDescription::*create_identifier_string$)() const = &::juce::PluginDescription::createIdentifierString;
  new (return$) ::juce::JuceString((self.*create_identifier_string$)());
}
} // extern "C"
} // namespace juce

namespace cxx_juce {
extern "C" {
void cxx_juce$cxxbridge1$owned_array_plugin_description_new(::juce::OwnedArrayPluginDescription *return$) noexcept {
  ::juce::OwnedArrayPluginDescription (*owned_array_plugin_description_new$)() = ::cxx_juce::construct;
  new (return$) ::juce::OwnedArrayPluginDescription(owned_array_plugin_description_new$());
}

void cxx_juce$cxxbridge1$owned_array_plugin_description_drop(::juce::OwnedArrayPluginDescription &self_) noexcept {
  void (*owned_array_plugin_description_drop$)(::juce::OwnedArrayPluginDescription &) = ::cxx_juce::drop;
  owned_array_plugin_description_drop$(self_);
}
} // extern "C"
} // namespace cxx_juce

namespace juce {
extern "C" {
::juce::PluginDescription *juce$cxxbridge1$OwnedArrayPluginDescription$add_raw(::juce::OwnedArrayPluginDescription &self, ::juce::PluginDescription *description) noexcept {
  ::juce::PluginDescription *(::juce::OwnedArrayPluginDescription::*add_raw$)(::juce::PluginDescription *) = &::juce::OwnedArrayPluginDescription::add;
  return (self.*add_raw$)(description);
}
} // extern "C"
} // namespace juce

namespace cxx_juce {
extern "C" {
::juce::PluginDescription *cxx_juce$cxxbridge1$owned_array_plugin_description_get(::juce::OwnedArrayPluginDescription const &self_, ::std::int32_t index) noexcept {
  ::juce::PluginDescription *(*owned_array_plugin_description_get$)(::juce::OwnedArrayPluginDescription const &, ::std::int32_t) = ::cxx_juce::index;
  return owned_array_plugin_description_get$(self_, index);
}
} // extern "C"
} // namespace cxx_juce

namespace juce {
extern "C" {
::std::int32_t juce$cxxbridge1$OwnedArrayPluginDescription$len(::juce::OwnedArrayPluginDescription const &self) noexcept {
  ::std::int32_t (::juce::OwnedArrayPluginDescription::*len$)() const = &::juce::OwnedArrayPluginDescription::size;
  return (self.*len$)();
}

::juce::PluginDescription *const *juce$cxxbridge1$OwnedArrayPluginDescription$data(::juce::OwnedArrayPluginDescription const &self) noexcept {
  ::juce::PluginDescription *const *(::juce::OwnedArrayPluginDescription::*data$)() const = &::juce::OwnedArrayPluginDescription::data;
  return (self.*data$)();
}
} // extern "C"
} // namespace juce

extern "C" {
static_assert(::rust::detail::is_complete<::std::remove_extent<::juce::PluginDescription>::type>::value, "definition of `::juce::PluginDescription` is required");
static_assert(sizeof(::std::unique_ptr<::juce::PluginDescription>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::juce::PluginDescription>) == alignof(void *), "");
void cxxbridge1$unique_ptr$juce$PluginDescription$null(::std::unique_ptr<::juce::PluginDescription> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::juce::PluginDescription>();
}
::juce::PluginDescription *cxxbridge1$unique_ptr$juce$PluginDescription$uninit(::std::unique_ptr<::juce::PluginDescription> *ptr) noexcept {
  ::juce::PluginDescription *uninit = reinterpret_cast<::juce::PluginDescription *>(new ::rust::MaybeUninit<::juce::PluginDescription>);
  ::new (ptr) ::std::unique_ptr<::juce::PluginDescription>(uninit);
  return uninit;
}
void cxxbridge1$unique_ptr$juce$PluginDescription$raw(::std::unique_ptr<::juce::PluginDescription> *ptr, ::std::unique_ptr<::juce::PluginDescription>::pointer raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::juce::PluginDescription>(raw);
}
::std::unique_ptr<::juce::PluginDescription>::element_type const *cxxbridge1$unique_ptr$juce$PluginDescription$get(::std::unique_ptr<::juce::PluginDescription> const &ptr) noexcept {
  return ptr.get();
}
::std::unique_ptr<::juce::PluginDescription>::pointer cxxbridge1$unique_ptr$juce$PluginDescription$release(::std::unique_ptr<::juce::PluginDescription> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$juce$PluginDescription$drop(::std::unique_ptr<::juce::PluginDescription> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::juce::PluginDescription>::value>{}(ptr);
}
} // extern "C"
