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
  enum class MidiBufferLayout : ::std::uint8_t;
  enum class MidiMessageLayout : ::std::uint8_t;
  enum class MidiFileLayout : ::std::uint8_t;
}

namespace juce {
#ifndef CXXBRIDGE1_ENUM_juce$MidiBufferLayout
#define CXXBRIDGE1_ENUM_juce$MidiBufferLayout
enum class MidiBufferLayout : ::std::uint8_t {
  Size = 16,
  Alignment = 8,
};
#endif // CXXBRIDGE1_ENUM_juce$MidiBufferLayout

#ifndef CXXBRIDGE1_ENUM_juce$MidiMessageLayout
#define CXXBRIDGE1_ENUM_juce$MidiMessageLayout
enum class MidiMessageLayout : ::std::uint8_t {
  Size = 24,
  Alignment = 8,
};
#endif // CXXBRIDGE1_ENUM_juce$MidiMessageLayout

#ifndef CXXBRIDGE1_ENUM_juce$MidiFileLayout
#define CXXBRIDGE1_ENUM_juce$MidiFileLayout
enum class MidiFileLayout : ::std::uint8_t {
  Size = 24,
  Alignment = 8,
};
#endif // CXXBRIDGE1_ENUM_juce$MidiFileLayout
} // namespace juce

static_assert(
    ::rust::IsRelocatable<::juce::JuceString>::value,
    "type juce::JuceString should be trivially move constructible and trivially destructible in C++ to be used as a return value of `get_description` in Rust");
static_assert(
    ::rust::IsRelocatable<::juce::MidiBuffer>::value,
    "type juce::MidiBuffer should be trivially move constructible and trivially destructible in C++ to be used as a return value of `midi_buffer_new` in Rust");
static_assert(
    ::rust::IsRelocatable<::juce::MidiMessage>::value,
    "type juce::MidiMessage should be trivially move constructible and trivially destructible in C++ to be used as a return value of `midi_message_clone`, `note_on`, `note_off` in Rust");
static_assert(
    ::rust::IsRelocatable<::juce::MidiFile>::value,
    "type juce::MidiFile should be trivially move constructible and trivially destructible in C++ to be used as a return value of `midi_file_new` in Rust");

namespace cxx_juce {
extern "C" {
void cxx_juce$cxxbridge1$midi_buffer_new(::juce::MidiBuffer *return$) noexcept {
  ::juce::MidiBuffer (*midi_buffer_new$)() = ::cxx_juce::construct;
  new (return$) ::juce::MidiBuffer(midi_buffer_new$());
}

void cxx_juce$cxxbridge1$midi_buffer_drop(::juce::MidiBuffer &buffer) noexcept {
  void (*midi_buffer_drop$)(::juce::MidiBuffer &) = ::cxx_juce::drop;
  midi_buffer_drop$(buffer);
}
} // extern "C"
} // namespace cxx_juce

namespace juce {
extern "C" {
void juce$cxxbridge1$MidiBuffer$clear(::juce::MidiBuffer &self) noexcept {
  void (::juce::MidiBuffer::*clear$)() = &::juce::MidiBuffer::clear;
  (self.*clear$)();
}

bool juce$cxxbridge1$MidiBuffer$is_empty(::juce::MidiBuffer const &self) noexcept {
  bool (::juce::MidiBuffer::*is_empty$)() const = &::juce::MidiBuffer::isEmpty;
  return (self.*is_empty$)();
}

::std::int32_t juce$cxxbridge1$MidiBuffer$get_num_events(::juce::MidiBuffer const &self) noexcept {
  ::std::int32_t (::juce::MidiBuffer::*get_num_events$)() const = &::juce::MidiBuffer::getNumEvents;
  return (self.*get_num_events$)();
}

bool juce$cxxbridge1$MidiBuffer$add_event(::juce::MidiBuffer &self, ::juce::MidiMessage const &message, ::std::int32_t sample_number) noexcept {
  bool (::juce::MidiBuffer::*add_event$)(::juce::MidiMessage const &, ::std::int32_t) = &::juce::MidiBuffer::addEvent;
  return (self.*add_event$)(message, sample_number);
}

void juce$cxxbridge1$MidiBuffer$clear_range(::juce::MidiBuffer &self, ::std::int32_t start_sample, ::std::int32_t num_samples) noexcept {
  void (::juce::MidiBuffer::*clear_range$)(::std::int32_t, ::std::int32_t) = &::juce::MidiBuffer::clear;
  (self.*clear_range$)(start_sample, num_samples);
}
} // extern "C"
} // namespace juce

namespace cxx_juce {
extern "C" {
void cxx_juce$cxxbridge1$midi_message_drop(::juce::MidiMessage &msg) noexcept {
  void (*midi_message_drop$)(::juce::MidiMessage &) = ::cxx_juce::drop;
  midi_message_drop$(msg);
}

void cxx_juce$cxxbridge1$midi_message_clone(::juce::MidiMessage const &message, ::juce::MidiMessage *return$) noexcept {
  ::juce::MidiMessage (*midi_message_clone$)(::juce::MidiMessage const &) = ::cxx_juce::construct;
  new (return$) ::juce::MidiMessage(midi_message_clone$(message));
}
} // extern "C"
} // namespace cxx_juce

namespace juce {
extern "C" {
void juce$cxxbridge1$MidiMessage$note_on(::std::int32_t channel, ::std::int32_t note_number, float velocity, ::juce::MidiMessage *return$) noexcept {
  ::juce::MidiMessage (*note_on$)(::std::int32_t, ::std::int32_t, float) = &::juce::MidiMessage::noteOn;
  new (return$) ::juce::MidiMessage(note_on$(channel, note_number, velocity));
}

void juce$cxxbridge1$MidiMessage$note_off(::std::int32_t channel, ::std::int32_t note_number, float velocity, ::juce::MidiMessage *return$) noexcept {
  ::juce::MidiMessage (*note_off$)(::std::int32_t, ::std::int32_t, float) = &::juce::MidiMessage::noteOff;
  new (return$) ::juce::MidiMessage(note_off$(channel, note_number, velocity));
}

void juce$cxxbridge1$MidiMessage$get_description(::juce::MidiMessage const &self, ::juce::JuceString *return$) noexcept {
  ::juce::JuceString (::juce::MidiMessage::*get_description$)() const = &::juce::MidiMessage::getDescription;
  new (return$) ::juce::JuceString((self.*get_description$)());
}

bool juce$cxxbridge1$MidiMessage$is_note_on(::juce::MidiMessage const &self, bool return_true_for_note_on_velocity_zero) noexcept {
  bool (::juce::MidiMessage::*is_note_on$)(bool) const = &::juce::MidiMessage::isNoteOn;
  return (self.*is_note_on$)(return_true_for_note_on_velocity_zero);
}

bool juce$cxxbridge1$MidiMessage$is_note_off(::juce::MidiMessage const &self, bool return_true_for_note_on_velocity_zero) noexcept {
  bool (::juce::MidiMessage::*is_note_off$)(bool) const = &::juce::MidiMessage::isNoteOff;
  return (self.*is_note_off$)(return_true_for_note_on_velocity_zero);
}

::std::int32_t juce$cxxbridge1$MidiMessage$get_channel(::juce::MidiMessage const &self) noexcept {
  ::std::int32_t (::juce::MidiMessage::*get_channel$)() const = &::juce::MidiMessage::getChannel;
  return (self.*get_channel$)();
}

::std::int32_t juce$cxxbridge1$MidiMessage$get_note_number(::juce::MidiMessage const &self) noexcept {
  ::std::int32_t (::juce::MidiMessage::*get_note_number$)() const = &::juce::MidiMessage::getNoteNumber;
  return (self.*get_note_number$)();
}

::std::uint8_t juce$cxxbridge1$MidiMessage$get_velocity(::juce::MidiMessage const &self) noexcept {
  ::std::uint8_t (::juce::MidiMessage::*get_velocity$)() const = &::juce::MidiMessage::getVelocity;
  return (self.*get_velocity$)();
}

float juce$cxxbridge1$MidiMessage$get_float_velocity(::juce::MidiMessage const &self) noexcept {
  float (::juce::MidiMessage::*get_float_velocity$)() const = &::juce::MidiMessage::getFloatVelocity;
  return (self.*get_float_velocity$)();
}

double juce$cxxbridge1$MidiMessage$get_time_stamp(::juce::MidiMessage const &self) noexcept {
  double (::juce::MidiMessage::*get_time_stamp$)() const = &::juce::MidiMessage::getTimeStamp;
  return (self.*get_time_stamp$)();
}
} // extern "C"
} // namespace juce

namespace cxx_juce {
extern "C" {
void cxx_juce$cxxbridge1$midi_file_drop(::juce::MidiFile &file) noexcept {
  void (*midi_file_drop$)(::juce::MidiFile &) = ::cxx_juce::drop;
  midi_file_drop$(file);
}

void cxx_juce$cxxbridge1$midi_file_new(::juce::MidiFile *return$) noexcept {
  ::juce::MidiFile (*midi_file_new$)() = ::cxx_juce::construct;
  new (return$) ::juce::MidiFile(midi_file_new$());
}
} // extern "C"
} // namespace cxx_juce

namespace juce {
extern "C" {
::std::int32_t juce$cxxbridge1$MidiFile$get_num_tracks(::juce::MidiFile const &self) noexcept {
  ::std::int32_t (::juce::MidiFile::*get_num_tracks$)() const = &::juce::MidiFile::getNumTracks;
  return (self.*get_num_tracks$)();
}

::std::int16_t juce$cxxbridge1$MidiFile$get_time_format(::juce::MidiFile const &self) noexcept {
  ::std::int16_t (::juce::MidiFile::*get_time_format$)() const = &::juce::MidiFile::getTimeFormat;
  return (self.*get_time_format$)();
}

void juce$cxxbridge1$MidiFile$set_ticks_per_quarter_note(::juce::MidiFile &self, ::std::int32_t ticks_per_quarter_note) noexcept {
  void (::juce::MidiFile::*set_ticks_per_quarter_note$)(::std::int32_t) = &::juce::MidiFile::setTicksPerQuarterNote;
  (self.*set_ticks_per_quarter_note$)(ticks_per_quarter_note);
}

void juce$cxxbridge1$MidiFile$set_smpte_time_format(::juce::MidiFile &self, ::std::int32_t frames_per_second, ::std::int32_t sub_frame_divisor) noexcept {
  void (::juce::MidiFile::*set_smpte_time_format$)(::std::int32_t, ::std::int32_t) = &::juce::MidiFile::setSmpteTimeFormat;
  (self.*set_smpte_time_format$)(frames_per_second, sub_frame_divisor);
}
} // extern "C"
} // namespace juce
