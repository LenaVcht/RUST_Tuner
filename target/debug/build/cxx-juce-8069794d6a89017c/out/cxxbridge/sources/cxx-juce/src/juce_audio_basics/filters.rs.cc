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
  enum class IIRCoefficientsLayout : ::std::uint8_t;
  enum class SingleThreadedIIRFilterLayout : ::std::uint8_t;
}

namespace juce {
#ifndef CXXBRIDGE1_ENUM_juce$IIRCoefficientsLayout
#define CXXBRIDGE1_ENUM_juce$IIRCoefficientsLayout
enum class IIRCoefficientsLayout : ::std::uint8_t {
  Size = 20,
  Alignment = 4,
};
#endif // CXXBRIDGE1_ENUM_juce$IIRCoefficientsLayout

#ifndef CXXBRIDGE1_ENUM_juce$SingleThreadedIIRFilterLayout
#define CXXBRIDGE1_ENUM_juce$SingleThreadedIIRFilterLayout
enum class SingleThreadedIIRFilterLayout : ::std::uint8_t {
  Size = 36,
  Alignment = 4,
};
#endif // CXXBRIDGE1_ENUM_juce$SingleThreadedIIRFilterLayout
} // namespace juce

static_assert(
    ::rust::IsRelocatable<::juce::IIRCoefficients>::value,
    "type juce::IIRCoefficients should be trivially move constructible and trivially destructible in C++ to be used as a return value of `make_low_pass`, `make_high_pass`, `make_notch_filter` in Rust");
static_assert(
    ::rust::IsRelocatable<::juce::SingleThreadedIIRFilter>::value,
    "type juce::SingleThreadedIIRFilter should be trivially move constructible and trivially destructible in C++ to be used as a return value of `single_threaded_iir_filter_new` in Rust");

namespace cxx_juce {
extern "C" {
void cxx_juce$cxxbridge1$iir_coefficients_drop(::juce::IIRCoefficients &filter) noexcept {
  void (*iir_coefficients_drop$)(::juce::IIRCoefficients &) = ::cxx_juce::drop;
  iir_coefficients_drop$(filter);
}
} // extern "C"
} // namespace cxx_juce

namespace juce {
extern "C" {
void juce$cxxbridge1$IIRCoefficients$make_low_pass(double sample_rate, double frequency, double q, ::juce::IIRCoefficients *return$) noexcept {
  ::juce::IIRCoefficients (*make_low_pass$)(double, double, double) = &::juce::IIRCoefficients::makeLowPass;
  new (return$) ::juce::IIRCoefficients(make_low_pass$(sample_rate, frequency, q));
}

void juce$cxxbridge1$IIRCoefficients$make_high_pass(double sample_rate, double frequency, double q, ::juce::IIRCoefficients *return$) noexcept {
  ::juce::IIRCoefficients (*make_high_pass$)(double, double, double) = &::juce::IIRCoefficients::makeHighPass;
  new (return$) ::juce::IIRCoefficients(make_high_pass$(sample_rate, frequency, q));
}

void juce$cxxbridge1$IIRCoefficients$make_notch_filter(double sample_rate, double frequency, double q, ::juce::IIRCoefficients *return$) noexcept {
  ::juce::IIRCoefficients (*make_notch_filter$)(double, double, double) = &::juce::IIRCoefficients::makeNotchFilter;
  new (return$) ::juce::IIRCoefficients(make_notch_filter$(sample_rate, frequency, q));
}
} // extern "C"
} // namespace juce

namespace cxx_juce {
extern "C" {
void cxx_juce$cxxbridge1$single_threaded_iir_filter_new(::juce::SingleThreadedIIRFilter *return$) noexcept {
  ::juce::SingleThreadedIIRFilter (*single_threaded_iir_filter_new$)() = ::cxx_juce::construct;
  new (return$) ::juce::SingleThreadedIIRFilter(single_threaded_iir_filter_new$());
}

void cxx_juce$cxxbridge1$single_threaded_iir_filter_drop(::juce::SingleThreadedIIRFilter &self_) noexcept {
  void (*single_threaded_iir_filter_drop$)(::juce::SingleThreadedIIRFilter &) = ::cxx_juce::drop;
  single_threaded_iir_filter_drop$(self_);
}
} // extern "C"
} // namespace cxx_juce

namespace juce {
extern "C" {
void juce$cxxbridge1$SingleThreadedIIRFilter$set_coefficients(::juce::SingleThreadedIIRFilter &self, ::juce::IIRCoefficients const &coefficients) noexcept {
  void (::juce::SingleThreadedIIRFilter::*set_coefficients$)(::juce::IIRCoefficients const &) = &::juce::SingleThreadedIIRFilter::setCoefficients;
  (self.*set_coefficients$)(coefficients);
}

void juce$cxxbridge1$SingleThreadedIIRFilter$process_samples(::juce::SingleThreadedIIRFilter &self, float *samples, ::std::int32_t num_samples) noexcept {
  void (::juce::SingleThreadedIIRFilter::*process_samples$)(float *, ::std::int32_t) = &::juce::SingleThreadedIIRFilter::processSamples;
  (self.*process_samples$)(samples, num_samples);
}
} // extern "C"
} // namespace juce
