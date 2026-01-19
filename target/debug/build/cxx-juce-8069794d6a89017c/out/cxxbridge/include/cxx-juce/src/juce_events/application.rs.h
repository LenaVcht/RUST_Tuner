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
  using JUCEApplicationBase = ::juce::JUCEApplicationBase;
}
namespace cxx_juce {
  struct JuceApplicationBaseImpl;
}

namespace cxx_juce {
#ifndef CXXBRIDGE1_STRUCT_cxx_juce$JuceApplicationBaseImpl
#define CXXBRIDGE1_STRUCT_cxx_juce$JuceApplicationBaseImpl
struct JuceApplicationBaseImpl final : public ::rust::Opaque {
  static void drop(::cxx_juce::BoxDynJuceApplicationBase *app) noexcept;
  static ::juce::JuceString getApplicationName(::cxx_juce::BoxDynJuceApplicationBase const &app) noexcept;
  static ::juce::JuceString getApplicationVersion(::cxx_juce::BoxDynJuceApplicationBase const &app) noexcept;
  static void initialise(::cxx_juce::BoxDynJuceApplicationBase &app, ::juce::JuceString const &command_line) noexcept;
  static void shutdown(::cxx_juce::BoxDynJuceApplicationBase &app) noexcept;
  static void systemRequestedQuit(::cxx_juce::BoxDynJuceApplicationBase &app) noexcept;
  static bool moreThanOneInstanceAllowed(::cxx_juce::BoxDynJuceApplicationBase const &app) noexcept;
  static void anotherInstanceStarted(::cxx_juce::BoxDynJuceApplicationBase &app, ::juce::JuceString const &command_line) noexcept;
  static void suspended(::cxx_juce::BoxDynJuceApplicationBase &app) noexcept;
  static void resumed(::cxx_juce::BoxDynJuceApplicationBase &app) noexcept;
  static void unhandledException(::cxx_juce::BoxDynJuceApplicationBase &app) noexcept;
  static void timerCallback(::cxx_juce::BoxDynJuceApplicationBase &app, ::std::int32_t timer_id) noexcept;
  ~JuceApplicationBaseImpl() = delete;

private:
  friend ::rust::layout;
  struct layout {
    static ::std::size_t size() noexcept;
    static ::std::size_t align() noexcept;
  };
};
#endif // CXXBRIDGE1_STRUCT_cxx_juce$JuceApplicationBaseImpl

::std::unique_ptr<::juce::JUCEApplicationBase> createInstance() noexcept;
} // namespace cxx_juce

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__
