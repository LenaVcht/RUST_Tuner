cmake_minimum_required(VERSION 3.22)

project(RustTuner VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# ===== 1) Where is JUCE? =====
# Absolute path to your JUCE folder:
set(JUCE_DIR "/Users/nadinemueller/VS_Code/rust/JUCE" CACHE PATH "Path to JUCE")

# Bring JUCE into this project
add_subdirectory(${JUCE_DIR} JUCE_build)

# ===== 2) Define your JUCE app target =====
juce_add_gui_app(RustTuner
    PRODUCT_NAME "Rust Tuner"
)

target_sources(RustTuner PRIVATE
    Source/Main.cpp
    Source/TunerComponent.cpp
    Source/TunerComponent.h
)

target_link_libraries(RustTuner PRIVATE
    juce::juce_gui_extra
    juce::juce_audio_utils
    juce::juce_audio_devices
    juce::juce_audio_basics
)

# ===== 3) Where is the Rust library? =====
set(RUST_LOGIC_DIR "${CMAKE_SOURCE_DIR}/../rust_logic")
set(RUST_LIB_DIR   "${RUST_LOGIC_DIR}/target/release")

# Build Rust library before linking
add_custom_target(build_rust_logic
    COMMAND cargo build --release
    WORKING_DIRECTORY ${RUST_LOGIC_DIR}
    COMMENT "Building rust_logic (Rust cdylib)"
)

add_dependencies(RustTuner build_rust_logic)

# ===== 4) Link Rust library (macOS) =====
# cargo build --release produced librust_logic.dylib
target_link_libraries(RustTuner PRIVATE
    "${RUST_LIB_DIR}/librust_logic.dylib"
)
