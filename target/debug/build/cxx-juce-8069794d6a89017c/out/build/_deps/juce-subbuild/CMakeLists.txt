# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 4.2.1)

# Reject any attempt to use a toolchain file. We must not use one because
# we could be downloading it here. If the CMAKE_TOOLCHAIN_FILE environment
# variable is set, the cache variable will have been initialized from it.
unset(CMAKE_TOOLCHAIN_FILE CACHE)
unset(ENV{CMAKE_TOOLCHAIN_FILE})

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(juce-populate NONE)



include(ExternalProject)
ExternalProject_Add(juce-populate
                     "UPDATE_DISCONNECTED" "False" "DOWNLOAD_EXTRACT_TIMESTAMP" "TRUE" "EXTERNALPROJECT_INTERNAL_ARGUMENT_SEPARATOR" "URL" "https://github.com/juce-framework/JUCE/archive/refs/tags/7.0.12.tar.gz" "URL_HASH" "SHA256=94e3b35e1990cd67f59736bb5e1eff1cfd9590b16fea82696f309a8f59452434"
                    SOURCE_DIR          "/Users/nadinemueller/VS_Code/rust/RUST_Tuner/target/debug/build/cxx-juce-8069794d6a89017c/out/build/_deps/juce-src"
                    BINARY_DIR          "/Users/nadinemueller/VS_Code/rust/RUST_Tuner/target/debug/build/cxx-juce-8069794d6a89017c/out/build/_deps/juce-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
                    USES_TERMINAL_PATCH     YES
)


