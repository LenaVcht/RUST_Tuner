# RUST_Tuner


# Project Structure: rust_tuner
rust_tuner/
├── Cargo.toml               # Rust dependencies & build configuration
├── build.rs                 # Build script to bind Rust ↔ C++ (cxx-juce)
├── src/
│   └── main.rs              # Rust logic: YIN, frequency → note
├── cpp/                     # JUCE C++ code
│   ├── TunerApp.h           # JUCE header for GUI / Audio
│   ├── TunerApp.cpp         # JUCE GUI + Audio input stream
│   └── juce_module/         # Optional: JUCE modules (Audio, GUI, etc.)
├── include/                 # Header files for Rust/C++ bindings
│   └── tuner_bridge.h
├── resources/               # Optional: icons, fonts, GUI assets
├── target/                  # Build output (auto-generated)
└── README.md                # Project description & instructions
