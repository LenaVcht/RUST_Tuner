#pragma once
#include "cxx_juce.h"
#include <cstddef>
#include <cstdint>
#include <memory>
#include <type_traits>

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
#endif // __clang__

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

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__
