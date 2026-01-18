#include "cxx_juce.h"
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
  using SystemStats = ::juce::SystemStats;
}

static_assert(
    ::rust::IsRelocatable<::juce::JuceString>::value,
    "type juce::JuceString should be trivially move constructible and trivially destructible in C++ to be used as a return value of `get_juce_version`, `get_stack_backtrace` in Rust");

namespace juce {
extern "C" {
void juce$cxxbridge1$SystemStats$get_juce_version(::juce::JuceString *return$) noexcept {
  ::juce::JuceString (*get_juce_version$)() = &::juce::SystemStats::getJUCEVersion;
  new (return$) ::juce::JuceString(get_juce_version$());
}

void juce$cxxbridge1$SystemStats$get_stack_backtrace(::juce::JuceString *return$) noexcept {
  ::juce::JuceString (*get_stack_backtrace$)() = &::juce::SystemStats::getStackBacktrace;
  new (return$) ::juce::JuceString(get_stack_backtrace$());
}
} // extern "C"
} // namespace juce
