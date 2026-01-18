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
  enum class AudioPluginFormatManagerLayout : ::std::uint8_t;
  using AudioPluginFormat = ::juce::AudioPluginFormat;
}
namespace cxx_juce {
  struct AudioPluginFormatImpl;
}

namespace juce {
#ifndef CXXBRIDGE1_ENUM_juce$AudioPluginFormatManagerLayout
#define CXXBRIDGE1_ENUM_juce$AudioPluginFormatManagerLayout
enum class AudioPluginFormatManagerLayout : ::std::uint8_t {
  Size = 16,
  Alignment = 8,
};
#endif // CXXBRIDGE1_ENUM_juce$AudioPluginFormatManagerLayout
} // namespace juce

namespace cxx_juce {
#ifndef CXXBRIDGE1_STRUCT_cxx_juce$AudioPluginFormatImpl
#define CXXBRIDGE1_STRUCT_cxx_juce$AudioPluginFormatImpl
struct AudioPluginFormatImpl final : public ::rust::Opaque {
  static void drop(::cxx_juce::BoxDynAudioPluginFormat *format) noexcept;
  static ::juce::JuceString name(::cxx_juce::BoxDynAudioPluginFormat const &format) noexcept;
  static void find_all_types_for_file(::cxx_juce::BoxDynAudioPluginFormat &format, ::juce::OwnedArrayPluginDescription &results, ::juce::JuceString const &file) noexcept;
  static ::std::unique_ptr<::juce::AudioPluginInstance> create_plugin_instance(::cxx_juce::BoxDynAudioPluginFormat &format, ::juce::PluginDescription const &description, double sample_rate, ::std::int32_t buffer_size) noexcept;
  static bool file_might_contain_this_plugin_type(::cxx_juce::BoxDynAudioPluginFormat const &format, ::juce::JuceString const &file_or_identifier) noexcept;
  static ::juce::JuceString get_name_of_plugin_from_identifier(::cxx_juce::BoxDynAudioPluginFormat const &format, ::juce::JuceString const &file_or_identifier) noexcept;
  static bool plugin_needs_rescanning(::cxx_juce::BoxDynAudioPluginFormat const &format, ::juce::PluginDescription const &plugin) noexcept;
  static bool does_plugin_still_exist(::cxx_juce::BoxDynAudioPluginFormat const &format, ::juce::PluginDescription const &plugin) noexcept;
  static bool can_scan_for_plugins(::cxx_juce::BoxDynAudioPluginFormat const &format) noexcept;
  static bool is_trivial_to_scan(::cxx_juce::BoxDynAudioPluginFormat const &format) noexcept;
  static ::juce::StringArray search_paths_for_plugins(::cxx_juce::BoxDynAudioPluginFormat &format, ::juce::FileSearchPath const &directories_to_search, bool recursive, bool allow_async_plugins) noexcept;
  static ::juce::FileSearchPath get_default_locations_to_search(::cxx_juce::BoxDynAudioPluginFormat &format) noexcept;
  static bool requires_unblocked_message_thread_during_creation(::cxx_juce::BoxDynAudioPluginFormat const &format, ::juce::PluginDescription const &description) noexcept;
  ~AudioPluginFormatImpl() = delete;

private:
  friend ::rust::layout;
  struct layout {
    static ::std::size_t size() noexcept;
    static ::std::size_t align() noexcept;
  };
};
#endif // CXXBRIDGE1_STRUCT_cxx_juce$AudioPluginFormatImpl
} // namespace cxx_juce

static_assert(
    ::rust::IsRelocatable<::juce::JuceString>::value,
    "type juce::JuceString should be trivially move constructible and trivially destructible in C++ to be used as a return value of `get_name`, `get_name_of_plugin_from_identifier`, `name` in Rust");
static_assert(
    ::rust::IsRelocatable<::juce::AudioPluginFormatManager>::value,
    "type juce::AudioPluginFormatManager should be trivially move constructible and trivially destructible in C++ to be used as a return value of `audio_plugin_format_manager_new` in Rust");
static_assert(
    ::rust::IsRelocatable<::juce::FileSearchPath>::value,
    "type juce::FileSearchPath should be trivially move constructible and trivially destructible in C++ to be used as a return value of `get_default_locations_to_search` in Rust");
static_assert(
    ::rust::IsRelocatable<::juce::StringArray>::value,
    "type juce::StringArray should be trivially move constructible and trivially destructible in C++ to be used as a return value of `search_paths_for_plugins` in Rust");
static_assert(
    ::rust::IsRelocatable<::cxx_juce::BoxDynAudioPluginFormat>::value,
    "type cxx_juce::BoxDynAudioPluginFormat should be trivially move constructible and trivially destructible in C++ to be used as an argument of `wrap_audio_plugin_format` in Rust");

namespace cxx_juce {
extern "C" {
::juce::AudioPluginFormat *cxx_juce$cxxbridge1$wrap_audio_plugin_format(::cxx_juce::BoxDynAudioPluginFormat *format) noexcept {
  ::std::unique_ptr<::juce::AudioPluginFormat> (*wrap_audio_plugin_format$)(::cxx_juce::BoxDynAudioPluginFormat) = ::cxx_juce::wrap;
  return wrap_audio_plugin_format$(::std::move(*format)).release();
}

void cxx_juce$cxxbridge1$audio_plugin_format_manager_new(::juce::AudioPluginFormatManager *return$) noexcept {
  ::juce::AudioPluginFormatManager (*audio_plugin_format_manager_new$)() = ::cxx_juce::construct;
  new (return$) ::juce::AudioPluginFormatManager(audio_plugin_format_manager_new$());
}

void cxx_juce$cxxbridge1$audio_plugin_format_manager_drop(::juce::AudioPluginFormatManager &self_) noexcept {
  void (*audio_plugin_format_manager_drop$)(::juce::AudioPluginFormatManager &) = ::cxx_juce::drop;
  audio_plugin_format_manager_drop$(self_);
}
} // extern "C"
} // namespace cxx_juce

namespace juce {
extern "C" {
void juce$cxxbridge1$AudioPluginFormatManager$add_default_formats(::juce::AudioPluginFormatManager &self) noexcept {
  void (::juce::AudioPluginFormatManager::*add_default_formats$)() = &::juce::AudioPluginFormatManager::addDefaultFormats;
  (self.*add_default_formats$)();
}

::std::int32_t juce$cxxbridge1$AudioPluginFormatManager$get_num_formats(::juce::AudioPluginFormatManager const &self) noexcept {
  ::std::int32_t (::juce::AudioPluginFormatManager::*get_num_formats$)() const = &::juce::AudioPluginFormatManager::getNumFormats;
  return (self.*get_num_formats$)();
}

::juce::AudioPluginFormat *juce$cxxbridge1$AudioPluginFormatManager$get_format_raw(::juce::AudioPluginFormatManager const &self, ::std::int32_t index) noexcept {
  ::juce::AudioPluginFormat *(::juce::AudioPluginFormatManager::*get_format_raw$)(::std::int32_t) const = &::juce::AudioPluginFormatManager::getFormat;
  return (self.*get_format_raw$)(index);
}

void juce$cxxbridge1$AudioPluginFormatManager$add_format_raw(::juce::AudioPluginFormatManager &self, ::juce::AudioPluginFormat *format) noexcept {
  void (::juce::AudioPluginFormatManager::*add_format_raw$)(::juce::AudioPluginFormat *) = &::juce::AudioPluginFormatManager::addFormat;
  (self.*add_format_raw$)(format);
}

void juce$cxxbridge1$AudioPluginFormat$get_name(::juce::AudioPluginFormat const &self, ::juce::JuceString *return$) noexcept {
  ::juce::JuceString (::juce::AudioPluginFormat::*get_name$)() const = &::juce::AudioPluginFormat::getName;
  new (return$) ::juce::JuceString((self.*get_name$)());
}

void juce$cxxbridge1$AudioPluginFormat$find_all_types_for_file(::juce::AudioPluginFormat &self, ::juce::OwnedArrayPluginDescription &result, ::juce::JuceString const &file) noexcept {
  void (::juce::AudioPluginFormat::*find_all_types_for_file$)(::juce::OwnedArrayPluginDescription &, ::juce::JuceString const &) = &::juce::AudioPluginFormat::findAllTypesForFile;
  (self.*find_all_types_for_file$)(result, file);
}

::juce::AudioPluginInstance *juce$cxxbridge1$AudioPluginFormat$create_instance_from_description(::juce::AudioPluginFormat &self, ::juce::PluginDescription const &description, double sample_rate, ::std::int32_t buffer_size, ::juce::JuceString &error) noexcept {
  ::std::unique_ptr<::juce::AudioPluginInstance> (::juce::AudioPluginFormat::*create_instance_from_description$)(::juce::PluginDescription const &, double, ::std::int32_t, ::juce::JuceString &) = &::juce::AudioPluginFormat::createInstanceFromDescription;
  return (self.*create_instance_from_description$)(description, sample_rate, buffer_size, error).release();
}

bool juce$cxxbridge1$AudioPluginFormat$file_might_contain_this_plugin_type(::juce::AudioPluginFormat &self, ::juce::JuceString const &file_or_identifier) noexcept {
  bool (::juce::AudioPluginFormat::*file_might_contain_this_plugin_type$)(::juce::JuceString const &) = &::juce::AudioPluginFormat::fileMightContainThisPluginType;
  return (self.*file_might_contain_this_plugin_type$)(file_or_identifier);
}

void juce$cxxbridge1$AudioPluginFormat$get_name_of_plugin_from_identifier(::juce::AudioPluginFormat &self, ::juce::JuceString const &file_or_identifier, ::juce::JuceString *return$) noexcept {
  ::juce::JuceString (::juce::AudioPluginFormat::*get_name_of_plugin_from_identifier$)(::juce::JuceString const &) = &::juce::AudioPluginFormat::getNameOfPluginFromIdentifier;
  new (return$) ::juce::JuceString((self.*get_name_of_plugin_from_identifier$)(file_or_identifier));
}

bool juce$cxxbridge1$AudioPluginFormat$plugin_need_rescanning(::juce::AudioPluginFormat &self, ::juce::PluginDescription const &plugin) noexcept {
  bool (::juce::AudioPluginFormat::*plugin_need_rescanning$)(::juce::PluginDescription const &) = &::juce::AudioPluginFormat::pluginNeedsRescanning;
  return (self.*plugin_need_rescanning$)(plugin);
}

bool juce$cxxbridge1$AudioPluginFormat$does_plugin_still_exist(::juce::AudioPluginFormat &self, ::juce::PluginDescription const &plugin) noexcept {
  bool (::juce::AudioPluginFormat::*does_plugin_still_exist$)(::juce::PluginDescription const &) = &::juce::AudioPluginFormat::doesPluginStillExist;
  return (self.*does_plugin_still_exist$)(plugin);
}

bool juce$cxxbridge1$AudioPluginFormat$can_scan_for_plugins(::juce::AudioPluginFormat const &self) noexcept {
  bool (::juce::AudioPluginFormat::*can_scan_for_plugins$)() const = &::juce::AudioPluginFormat::canScanForPlugins;
  return (self.*can_scan_for_plugins$)();
}

bool juce$cxxbridge1$AudioPluginFormat$is_trivial_to_scan(::juce::AudioPluginFormat const &self) noexcept {
  bool (::juce::AudioPluginFormat::*is_trivial_to_scan$)() const = &::juce::AudioPluginFormat::isTrivialToScan;
  return (self.*is_trivial_to_scan$)();
}

void juce$cxxbridge1$AudioPluginFormat$search_paths_for_plugins(::juce::AudioPluginFormat &self, ::juce::FileSearchPath const &directories_to_search, bool recursive, bool allow_async_plugins, ::juce::StringArray *return$) noexcept {
  ::juce::StringArray (::juce::AudioPluginFormat::*search_paths_for_plugins$)(::juce::FileSearchPath const &, bool, bool) = &::juce::AudioPluginFormat::searchPathsForPlugins;
  new (return$) ::juce::StringArray((self.*search_paths_for_plugins$)(directories_to_search, recursive, allow_async_plugins));
}

void juce$cxxbridge1$AudioPluginFormat$get_default_locations_to_search(::juce::AudioPluginFormat &self, ::juce::FileSearchPath *return$) noexcept {
  ::juce::FileSearchPath (::juce::AudioPluginFormat::*get_default_locations_to_search$)() = &::juce::AudioPluginFormat::getDefaultLocationsToSearch;
  new (return$) ::juce::FileSearchPath((self.*get_default_locations_to_search$)());
}
} // extern "C"
} // namespace juce

namespace cxx_juce {
extern "C" {
::std::size_t cxx_juce$cxxbridge1$AudioPluginFormatImpl$operator$sizeof() noexcept;
::std::size_t cxx_juce$cxxbridge1$AudioPluginFormatImpl$operator$alignof() noexcept;

void cxx_juce$cxxbridge1$AudioPluginFormatImpl$drop(::cxx_juce::BoxDynAudioPluginFormat *format) noexcept;

void cxx_juce$cxxbridge1$AudioPluginFormatImpl$name(::cxx_juce::BoxDynAudioPluginFormat const &format, ::juce::JuceString *return$) noexcept;

void cxx_juce$cxxbridge1$AudioPluginFormatImpl$find_all_types_for_file(::cxx_juce::BoxDynAudioPluginFormat &format, ::juce::OwnedArrayPluginDescription &results, ::juce::JuceString const &file) noexcept;

::juce::AudioPluginInstance *cxx_juce$cxxbridge1$AudioPluginFormatImpl$create_plugin_instance(::cxx_juce::BoxDynAudioPluginFormat &format, ::juce::PluginDescription const &description, double sample_rate, ::std::int32_t buffer_size) noexcept;

bool cxx_juce$cxxbridge1$AudioPluginFormatImpl$file_might_contain_this_plugin_type(::cxx_juce::BoxDynAudioPluginFormat const &format, ::juce::JuceString const &file_or_identifier) noexcept;

void cxx_juce$cxxbridge1$AudioPluginFormatImpl$get_name_of_plugin_from_identifier(::cxx_juce::BoxDynAudioPluginFormat const &format, ::juce::JuceString const &file_or_identifier, ::juce::JuceString *return$) noexcept;

bool cxx_juce$cxxbridge1$AudioPluginFormatImpl$plugin_needs_rescanning(::cxx_juce::BoxDynAudioPluginFormat const &format, ::juce::PluginDescription const &plugin) noexcept;

bool cxx_juce$cxxbridge1$AudioPluginFormatImpl$does_plugin_still_exist(::cxx_juce::BoxDynAudioPluginFormat const &format, ::juce::PluginDescription const &plugin) noexcept;

bool cxx_juce$cxxbridge1$AudioPluginFormatImpl$can_scan_for_plugins(::cxx_juce::BoxDynAudioPluginFormat const &format) noexcept;

bool cxx_juce$cxxbridge1$AudioPluginFormatImpl$is_trivial_to_scan(::cxx_juce::BoxDynAudioPluginFormat const &format) noexcept;

void cxx_juce$cxxbridge1$AudioPluginFormatImpl$search_paths_for_plugins(::cxx_juce::BoxDynAudioPluginFormat &format, ::juce::FileSearchPath const &directories_to_search, bool recursive, bool allow_async_plugins, ::juce::StringArray *return$) noexcept;

void cxx_juce$cxxbridge1$AudioPluginFormatImpl$get_default_locations_to_search(::cxx_juce::BoxDynAudioPluginFormat &format, ::juce::FileSearchPath *return$) noexcept;

bool cxx_juce$cxxbridge1$AudioPluginFormatImpl$requires_unblocked_message_thread_during_creation(::cxx_juce::BoxDynAudioPluginFormat const &format, ::juce::PluginDescription const &description) noexcept;
} // extern "C"

::std::size_t AudioPluginFormatImpl::layout::size() noexcept {
  return cxx_juce$cxxbridge1$AudioPluginFormatImpl$operator$sizeof();
}

::std::size_t AudioPluginFormatImpl::layout::align() noexcept {
  return cxx_juce$cxxbridge1$AudioPluginFormatImpl$operator$alignof();
}

void AudioPluginFormatImpl::drop(::cxx_juce::BoxDynAudioPluginFormat *format) noexcept {
  cxx_juce$cxxbridge1$AudioPluginFormatImpl$drop(format);
}

::juce::JuceString AudioPluginFormatImpl::name(::cxx_juce::BoxDynAudioPluginFormat const &format) noexcept {
  ::rust::MaybeUninit<::juce::JuceString> return$;
  cxx_juce$cxxbridge1$AudioPluginFormatImpl$name(format, &return$.value);
  return ::std::move(return$.value);
}

void AudioPluginFormatImpl::find_all_types_for_file(::cxx_juce::BoxDynAudioPluginFormat &format, ::juce::OwnedArrayPluginDescription &results, ::juce::JuceString const &file) noexcept {
  cxx_juce$cxxbridge1$AudioPluginFormatImpl$find_all_types_for_file(format, results, file);
}

::std::unique_ptr<::juce::AudioPluginInstance> AudioPluginFormatImpl::create_plugin_instance(::cxx_juce::BoxDynAudioPluginFormat &format, ::juce::PluginDescription const &description, double sample_rate, ::std::int32_t buffer_size) noexcept {
  return ::std::unique_ptr<::juce::AudioPluginInstance>(cxx_juce$cxxbridge1$AudioPluginFormatImpl$create_plugin_instance(format, description, sample_rate, buffer_size));
}

bool AudioPluginFormatImpl::file_might_contain_this_plugin_type(::cxx_juce::BoxDynAudioPluginFormat const &format, ::juce::JuceString const &file_or_identifier) noexcept {
  return cxx_juce$cxxbridge1$AudioPluginFormatImpl$file_might_contain_this_plugin_type(format, file_or_identifier);
}

::juce::JuceString AudioPluginFormatImpl::get_name_of_plugin_from_identifier(::cxx_juce::BoxDynAudioPluginFormat const &format, ::juce::JuceString const &file_or_identifier) noexcept {
  ::rust::MaybeUninit<::juce::JuceString> return$;
  cxx_juce$cxxbridge1$AudioPluginFormatImpl$get_name_of_plugin_from_identifier(format, file_or_identifier, &return$.value);
  return ::std::move(return$.value);
}

bool AudioPluginFormatImpl::plugin_needs_rescanning(::cxx_juce::BoxDynAudioPluginFormat const &format, ::juce::PluginDescription const &plugin) noexcept {
  return cxx_juce$cxxbridge1$AudioPluginFormatImpl$plugin_needs_rescanning(format, plugin);
}

bool AudioPluginFormatImpl::does_plugin_still_exist(::cxx_juce::BoxDynAudioPluginFormat const &format, ::juce::PluginDescription const &plugin) noexcept {
  return cxx_juce$cxxbridge1$AudioPluginFormatImpl$does_plugin_still_exist(format, plugin);
}

bool AudioPluginFormatImpl::can_scan_for_plugins(::cxx_juce::BoxDynAudioPluginFormat const &format) noexcept {
  return cxx_juce$cxxbridge1$AudioPluginFormatImpl$can_scan_for_plugins(format);
}

bool AudioPluginFormatImpl::is_trivial_to_scan(::cxx_juce::BoxDynAudioPluginFormat const &format) noexcept {
  return cxx_juce$cxxbridge1$AudioPluginFormatImpl$is_trivial_to_scan(format);
}

::juce::StringArray AudioPluginFormatImpl::search_paths_for_plugins(::cxx_juce::BoxDynAudioPluginFormat &format, ::juce::FileSearchPath const &directories_to_search, bool recursive, bool allow_async_plugins) noexcept {
  ::rust::MaybeUninit<::juce::StringArray> return$;
  cxx_juce$cxxbridge1$AudioPluginFormatImpl$search_paths_for_plugins(format, directories_to_search, recursive, allow_async_plugins, &return$.value);
  return ::std::move(return$.value);
}

::juce::FileSearchPath AudioPluginFormatImpl::get_default_locations_to_search(::cxx_juce::BoxDynAudioPluginFormat &format) noexcept {
  ::rust::MaybeUninit<::juce::FileSearchPath> return$;
  cxx_juce$cxxbridge1$AudioPluginFormatImpl$get_default_locations_to_search(format, &return$.value);
  return ::std::move(return$.value);
}

bool AudioPluginFormatImpl::requires_unblocked_message_thread_during_creation(::cxx_juce::BoxDynAudioPluginFormat const &format, ::juce::PluginDescription const &description) noexcept {
  return cxx_juce$cxxbridge1$AudioPluginFormatImpl$requires_unblocked_message_thread_during_creation(format, description);
}
} // namespace cxx_juce

extern "C" {
static_assert(::rust::detail::is_complete<::std::remove_extent<::juce::AudioPluginFormat>::type>::value, "definition of `::juce::AudioPluginFormat` is required");
static_assert(sizeof(::std::unique_ptr<::juce::AudioPluginFormat>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::juce::AudioPluginFormat>) == alignof(void *), "");
void cxxbridge1$unique_ptr$juce$AudioPluginFormat$null(::std::unique_ptr<::juce::AudioPluginFormat> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::juce::AudioPluginFormat>();
}
void cxxbridge1$unique_ptr$juce$AudioPluginFormat$raw(::std::unique_ptr<::juce::AudioPluginFormat> *ptr, ::std::unique_ptr<::juce::AudioPluginFormat>::pointer raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::juce::AudioPluginFormat>(raw);
}
::std::unique_ptr<::juce::AudioPluginFormat>::element_type const *cxxbridge1$unique_ptr$juce$AudioPluginFormat$get(::std::unique_ptr<::juce::AudioPluginFormat> const &ptr) noexcept {
  return ptr.get();
}
::std::unique_ptr<::juce::AudioPluginFormat>::pointer cxxbridge1$unique_ptr$juce$AudioPluginFormat$release(::std::unique_ptr<::juce::AudioPluginFormat> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$juce$AudioPluginFormat$drop(::std::unique_ptr<::juce::AudioPluginFormat> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::juce::AudioPluginFormat>::value>{}(ptr);
}
} // extern "C"
