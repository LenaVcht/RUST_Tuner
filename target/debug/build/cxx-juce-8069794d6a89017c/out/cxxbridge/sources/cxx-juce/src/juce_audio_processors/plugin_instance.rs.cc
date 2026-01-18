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

static_assert(
    ::rust::IsRelocatable<::juce::JuceString>::value,
    "type juce::JuceString should be trivially move constructible and trivially destructible in C++ to be used as a return value of `audio_processor_get_name`, `get_name`, `get_program_name` in Rust");
static_assert(
    ::rust::IsRelocatable<::cxx_juce::BoxDynAudioPlugin>::value,
    "type cxx_juce::BoxDynAudioPlugin should be trivially move constructible and trivially destructible in C++ to be used as an argument of `wrap_plugin_instance` in Rust");

namespace cxx_juce {
extern "C" {
::juce::AudioPluginInstance *cxx_juce$cxxbridge1$wrap_plugin_instance(::cxx_juce::BoxDynAudioPlugin *plugin) noexcept {
  ::std::unique_ptr<::juce::AudioPluginInstance> (*wrap_plugin_instance$)(::cxx_juce::BoxDynAudioPlugin) = ::cxx_juce::wrap;
  return wrap_plugin_instance$(::std::move(*plugin)).release();
}

void cxx_juce$cxxbridge1$audio_plugin_to_processor(::juce::AudioPluginInstance const &plugin, ::juce::AudioProcessor const **return$) noexcept {
  ::juce::AudioProcessor const &(*audio_plugin_to_processor$)(::juce::AudioPluginInstance const &) = ::cxx_juce::derivedCast;
  new (return$) ::juce::AudioProcessor const *(&audio_plugin_to_processor$(plugin));
}

void cxx_juce$cxxbridge1$audio_plugin_to_processor_mut(::juce::AudioPluginInstance &plugin, ::juce::AudioProcessor **return$) noexcept {
  ::juce::AudioProcessor &(*audio_plugin_to_processor_mut$)(::juce::AudioPluginInstance &) = ::cxx_juce::derivedCastMut;
  new (return$) ::juce::AudioProcessor *(&audio_plugin_to_processor_mut$(plugin));
}

void cxx_juce$cxxbridge1$audio_processor_get_name(::juce::AudioProcessor const &self_, ::juce::JuceString *return$) noexcept {
  ::juce::JuceString (*audio_processor_get_name$)(::juce::AudioProcessor const &) = ::cxx_juce::audioProcessorGetName;
  new (return$) ::juce::JuceString(audio_processor_get_name$(self_));
}
} // extern "C"
} // namespace cxx_juce

namespace juce {
extern "C" {
void juce$cxxbridge1$AudioProcessor$prepare_to_play(::juce::AudioProcessor &self, double sample_rate, ::std::int32_t samples_per_block) noexcept {
  void (::juce::AudioProcessor::*prepare_to_play$)(double, ::std::int32_t) = &::juce::AudioProcessor::prepareToPlay;
  (self.*prepare_to_play$)(sample_rate, samples_per_block);
}

void juce$cxxbridge1$AudioProcessor$release_resources(::juce::AudioProcessor &self) noexcept {
  void (::juce::AudioProcessor::*release_resources$)() = &::juce::AudioProcessor::releaseResources;
  (self.*release_resources$)();
}

void juce$cxxbridge1$AudioProcessor$process_block(::juce::AudioProcessor &self, ::juce::AudioSampleBuffer &audio, ::juce::MidiBuffer &midi) noexcept {
  void (::juce::AudioProcessor::*process_block$)(::juce::AudioSampleBuffer &, ::juce::MidiBuffer &) = &::juce::AudioProcessor::processBlock;
  (self.*process_block$)(audio, midi);
}

void juce$cxxbridge1$AudioProcessor$process_block_bypassed(::juce::AudioProcessor &self, ::juce::AudioSampleBuffer &audio, ::juce::MidiBuffer &midi) noexcept {
  void (::juce::AudioProcessor::*process_block_bypassed$)(::juce::AudioSampleBuffer &, ::juce::MidiBuffer &) = &::juce::AudioProcessor::processBlockBypassed;
  (self.*process_block_bypassed$)(audio, midi);
}

::std::int32_t juce$cxxbridge1$AudioProcessor$get_total_num_input_channels(::juce::AudioProcessor const &self) noexcept {
  ::std::int32_t (::juce::AudioProcessor::*get_total_num_input_channels$)() const = &::juce::AudioProcessor::getTotalNumInputChannels;
  return (self.*get_total_num_input_channels$)();
}

::std::int32_t juce$cxxbridge1$AudioProcessor$get_total_num_output_channels(::juce::AudioProcessor const &self) noexcept {
  ::std::int32_t (::juce::AudioProcessor::*get_total_num_output_channels$)() const = &::juce::AudioProcessor::getTotalNumOutputChannels;
  return (self.*get_total_num_output_channels$)();
}

::std::int32_t juce$cxxbridge1$AudioProcessor$get_latency_samples(::juce::AudioProcessor const &self) noexcept {
  ::std::int32_t (::juce::AudioProcessor::*get_latency_samples$)() const = &::juce::AudioProcessor::getLatencySamples;
  return (self.*get_latency_samples$)();
}

void juce$cxxbridge1$AudioProcessor$set_latency_samples(::juce::AudioProcessor &self, ::std::int32_t new_latency) noexcept {
  void (::juce::AudioProcessor::*set_latency_samples$)(::std::int32_t) = &::juce::AudioProcessor::setLatencySamples;
  (self.*set_latency_samples$)(new_latency);
}

double juce$cxxbridge1$AudioProcessor$get_sample_rate(::juce::AudioProcessor const &self) noexcept {
  double (::juce::AudioProcessor::*get_sample_rate$)() const = &::juce::AudioProcessor::getSampleRate;
  return (self.*get_sample_rate$)();
}

::std::int32_t juce$cxxbridge1$AudioProcessor$get_block_size(::juce::AudioProcessor const &self) noexcept {
  ::std::int32_t (::juce::AudioProcessor::*get_block_size$)() const = &::juce::AudioProcessor::getBlockSize;
  return (self.*get_block_size$)();
}

bool juce$cxxbridge1$AudioProcessor$is_suspended(::juce::AudioProcessor const &self) noexcept {
  bool (::juce::AudioProcessor::*is_suspended$)() const = &::juce::AudioProcessor::isSuspended;
  return (self.*is_suspended$)();
}

void juce$cxxbridge1$AudioProcessor$set_non_realtime(::juce::AudioProcessor &self, bool is_non_realtime) noexcept {
  void (::juce::AudioProcessor::*set_non_realtime$)(bool) = &::juce::AudioProcessor::setNonRealtime;
  (self.*set_non_realtime$)(is_non_realtime);
}

void juce$cxxbridge1$AudioPluginInstance$fill_in_plugin_description(::juce::AudioPluginInstance const &self, ::juce::PluginDescription &description) noexcept {
  void (::juce::AudioPluginInstance::*fill_in_plugin_description$)(::juce::PluginDescription &) const = &::juce::AudioPluginInstance::fillInPluginDescription;
  (self.*fill_in_plugin_description$)(description);
}
} // extern "C"
} // namespace juce

namespace cxx_juce {
extern "C" {
::std::size_t cxx_juce$cxxbridge1$AudioPluginImpl$operator$sizeof() noexcept;
::std::size_t cxx_juce$cxxbridge1$AudioPluginImpl$operator$alignof() noexcept;

void cxx_juce$cxxbridge1$AudioPluginImpl$drop(::cxx_juce::BoxDynAudioPlugin *self_) noexcept;

void cxx_juce$cxxbridge1$AudioPluginImpl$get_name(::cxx_juce::BoxDynAudioPlugin const &self_, ::juce::JuceString *return$) noexcept;

void cxx_juce$cxxbridge1$AudioPluginImpl$prepare_to_play(::cxx_juce::BoxDynAudioPlugin &self_, double sample_rate, ::std::int32_t samples_per_block) noexcept;

void cxx_juce$cxxbridge1$AudioPluginImpl$release_resources(::cxx_juce::BoxDynAudioPlugin &self_) noexcept;

void cxx_juce$cxxbridge1$AudioPluginImpl$process_block(::cxx_juce::BoxDynAudioPlugin &self_, ::juce::AudioSampleBuffer &audio, ::juce::MidiBuffer &midi) noexcept;

double cxx_juce$cxxbridge1$AudioPluginImpl$get_tail_length_seconds(::cxx_juce::BoxDynAudioPlugin const &self_) noexcept;

bool cxx_juce$cxxbridge1$AudioPluginImpl$accepts_midi(::cxx_juce::BoxDynAudioPlugin const &self_) noexcept;

bool cxx_juce$cxxbridge1$AudioPluginImpl$produces_midi(::cxx_juce::BoxDynAudioPlugin const &self_) noexcept;

bool cxx_juce$cxxbridge1$AudioPluginImpl$has_editor(::cxx_juce::BoxDynAudioPlugin const &self_) noexcept;

::std::int32_t cxx_juce$cxxbridge1$AudioPluginImpl$get_num_programs(::cxx_juce::BoxDynAudioPlugin &self_) noexcept;

::std::int32_t cxx_juce$cxxbridge1$AudioPluginImpl$get_current_program(::cxx_juce::BoxDynAudioPlugin &self_) noexcept;

void cxx_juce$cxxbridge1$AudioPluginImpl$set_current_program(::cxx_juce::BoxDynAudioPlugin &self_, ::std::int32_t index) noexcept;

void cxx_juce$cxxbridge1$AudioPluginImpl$get_program_name(::cxx_juce::BoxDynAudioPlugin &self_, ::std::int32_t index, ::juce::JuceString *return$) noexcept;

void cxx_juce$cxxbridge1$AudioPluginImpl$change_program_name(::cxx_juce::BoxDynAudioPlugin &self_, ::std::int32_t index, ::juce::JuceString const &new_name) noexcept;

void cxx_juce$cxxbridge1$AudioPluginImpl$fill_in_plugin_description(::cxx_juce::BoxDynAudioPlugin const &self_, ::juce::PluginDescription &description) noexcept;
} // extern "C"

::std::size_t AudioPluginImpl::layout::size() noexcept {
  return cxx_juce$cxxbridge1$AudioPluginImpl$operator$sizeof();
}

::std::size_t AudioPluginImpl::layout::align() noexcept {
  return cxx_juce$cxxbridge1$AudioPluginImpl$operator$alignof();
}

void AudioPluginImpl::drop(::cxx_juce::BoxDynAudioPlugin *self_) noexcept {
  cxx_juce$cxxbridge1$AudioPluginImpl$drop(self_);
}

::juce::JuceString AudioPluginImpl::get_name(::cxx_juce::BoxDynAudioPlugin const &self_) noexcept {
  ::rust::MaybeUninit<::juce::JuceString> return$;
  cxx_juce$cxxbridge1$AudioPluginImpl$get_name(self_, &return$.value);
  return ::std::move(return$.value);
}

void AudioPluginImpl::prepare_to_play(::cxx_juce::BoxDynAudioPlugin &self_, double sample_rate, ::std::int32_t samples_per_block) noexcept {
  cxx_juce$cxxbridge1$AudioPluginImpl$prepare_to_play(self_, sample_rate, samples_per_block);
}

void AudioPluginImpl::release_resources(::cxx_juce::BoxDynAudioPlugin &self_) noexcept {
  cxx_juce$cxxbridge1$AudioPluginImpl$release_resources(self_);
}

void AudioPluginImpl::process_block(::cxx_juce::BoxDynAudioPlugin &self_, ::juce::AudioSampleBuffer &audio, ::juce::MidiBuffer &midi) noexcept {
  cxx_juce$cxxbridge1$AudioPluginImpl$process_block(self_, audio, midi);
}

double AudioPluginImpl::get_tail_length_seconds(::cxx_juce::BoxDynAudioPlugin const &self_) noexcept {
  return cxx_juce$cxxbridge1$AudioPluginImpl$get_tail_length_seconds(self_);
}

bool AudioPluginImpl::accepts_midi(::cxx_juce::BoxDynAudioPlugin const &self_) noexcept {
  return cxx_juce$cxxbridge1$AudioPluginImpl$accepts_midi(self_);
}

bool AudioPluginImpl::produces_midi(::cxx_juce::BoxDynAudioPlugin const &self_) noexcept {
  return cxx_juce$cxxbridge1$AudioPluginImpl$produces_midi(self_);
}

bool AudioPluginImpl::has_editor(::cxx_juce::BoxDynAudioPlugin const &self_) noexcept {
  return cxx_juce$cxxbridge1$AudioPluginImpl$has_editor(self_);
}

::std::int32_t AudioPluginImpl::get_num_programs(::cxx_juce::BoxDynAudioPlugin &self_) noexcept {
  return cxx_juce$cxxbridge1$AudioPluginImpl$get_num_programs(self_);
}

::std::int32_t AudioPluginImpl::get_current_program(::cxx_juce::BoxDynAudioPlugin &self_) noexcept {
  return cxx_juce$cxxbridge1$AudioPluginImpl$get_current_program(self_);
}

void AudioPluginImpl::set_current_program(::cxx_juce::BoxDynAudioPlugin &self_, ::std::int32_t index) noexcept {
  cxx_juce$cxxbridge1$AudioPluginImpl$set_current_program(self_, index);
}

::juce::JuceString AudioPluginImpl::get_program_name(::cxx_juce::BoxDynAudioPlugin &self_, ::std::int32_t index) noexcept {
  ::rust::MaybeUninit<::juce::JuceString> return$;
  cxx_juce$cxxbridge1$AudioPluginImpl$get_program_name(self_, index, &return$.value);
  return ::std::move(return$.value);
}

void AudioPluginImpl::change_program_name(::cxx_juce::BoxDynAudioPlugin &self_, ::std::int32_t index, ::juce::JuceString const &new_name) noexcept {
  cxx_juce$cxxbridge1$AudioPluginImpl$change_program_name(self_, index, new_name);
}

void AudioPluginImpl::fill_in_plugin_description(::cxx_juce::BoxDynAudioPlugin const &self_, ::juce::PluginDescription &description) noexcept {
  cxx_juce$cxxbridge1$AudioPluginImpl$fill_in_plugin_description(self_, description);
}
} // namespace cxx_juce

extern "C" {
static_assert(::rust::detail::is_complete<::std::remove_extent<::juce::AudioPluginInstance>::type>::value, "definition of `::juce::AudioPluginInstance` is required");
static_assert(sizeof(::std::unique_ptr<::juce::AudioPluginInstance>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::juce::AudioPluginInstance>) == alignof(void *), "");
void cxxbridge1$unique_ptr$juce$AudioPluginInstance$null(::std::unique_ptr<::juce::AudioPluginInstance> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::juce::AudioPluginInstance>();
}
void cxxbridge1$unique_ptr$juce$AudioPluginInstance$raw(::std::unique_ptr<::juce::AudioPluginInstance> *ptr, ::std::unique_ptr<::juce::AudioPluginInstance>::pointer raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::juce::AudioPluginInstance>(raw);
}
::std::unique_ptr<::juce::AudioPluginInstance>::element_type const *cxxbridge1$unique_ptr$juce$AudioPluginInstance$get(::std::unique_ptr<::juce::AudioPluginInstance> const &ptr) noexcept {
  return ptr.get();
}
::std::unique_ptr<::juce::AudioPluginInstance>::pointer cxxbridge1$unique_ptr$juce$AudioPluginInstance$release(::std::unique_ptr<::juce::AudioPluginInstance> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$juce$AudioPluginInstance$drop(::std::unique_ptr<::juce::AudioPluginInstance> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::juce::AudioPluginInstance>::value>{}(ptr);
}
} // extern "C"
