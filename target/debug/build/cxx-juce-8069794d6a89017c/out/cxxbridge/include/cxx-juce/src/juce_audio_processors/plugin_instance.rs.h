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
  using AudioPluginInstance = ::juce::AudioPluginInstance;
  using AudioProcessor = ::juce::AudioProcessor;
}
namespace cxx_juce {
  struct AudioPluginImpl;
}

namespace cxx_juce {
#ifndef CXXBRIDGE1_STRUCT_cxx_juce$AudioPluginImpl
#define CXXBRIDGE1_STRUCT_cxx_juce$AudioPluginImpl
struct AudioPluginImpl final : public ::rust::Opaque {
  static void drop(::cxx_juce::BoxDynAudioPlugin *self_) noexcept;
  static ::juce::JuceString get_name(::cxx_juce::BoxDynAudioPlugin const &self_) noexcept;
  static void prepare_to_play(::cxx_juce::BoxDynAudioPlugin &self_, double sample_rate, ::std::int32_t samples_per_block) noexcept;
  static void release_resources(::cxx_juce::BoxDynAudioPlugin &self_) noexcept;
  static void process_block(::cxx_juce::BoxDynAudioPlugin &self_, ::juce::AudioSampleBuffer &audio, ::juce::MidiBuffer &midi) noexcept;
  static double get_tail_length_seconds(::cxx_juce::BoxDynAudioPlugin const &self_) noexcept;
  static bool accepts_midi(::cxx_juce::BoxDynAudioPlugin const &self_) noexcept;
  static bool produces_midi(::cxx_juce::BoxDynAudioPlugin const &self_) noexcept;
  static bool has_editor(::cxx_juce::BoxDynAudioPlugin const &self_) noexcept;
  static ::std::int32_t get_num_programs(::cxx_juce::BoxDynAudioPlugin &self_) noexcept;
  static ::std::int32_t get_current_program(::cxx_juce::BoxDynAudioPlugin &self_) noexcept;
  static void set_current_program(::cxx_juce::BoxDynAudioPlugin &self_, ::std::int32_t index) noexcept;
  static ::juce::JuceString get_program_name(::cxx_juce::BoxDynAudioPlugin &self_, ::std::int32_t index) noexcept;
  static void change_program_name(::cxx_juce::BoxDynAudioPlugin &self_, ::std::int32_t index, ::juce::JuceString const &new_name) noexcept;
  static void fill_in_plugin_description(::cxx_juce::BoxDynAudioPlugin const &self_, ::juce::PluginDescription &description) noexcept;
  ~AudioPluginImpl() = delete;

private:
  friend ::rust::layout;
  struct layout {
    static ::std::size_t size() noexcept;
    static ::std::size_t align() noexcept;
  };
};
#endif // CXXBRIDGE1_STRUCT_cxx_juce$AudioPluginImpl
} // namespace cxx_juce

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__
