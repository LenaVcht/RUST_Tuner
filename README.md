# RUST_Tuner


## Project Structure: rust_tuner
rust_tuner/ <br/>
├── Cargo.toml               # Rust dependencies & build configuration <br/>
├── build.rs                 # Build script to bind Rust ↔ C++ (cxx-juce) <br/>
├── src/
│   └── main.rs              # Rust logic: YIN, frequency → note <br/>
├── cpp/                     # JUCE C++ code <br/>
│   ├── TunerApp.h           # JUCE header for GUI / Audio <br/>
│   ├── TunerApp.cpp         # JUCE GUI + Audio input stream <br/>
│   └── juce_module/         # Optional: JUCE modules (Audio, GUI, etc.) <br/>
├── include/                 # Header files for Rust/C++ bindings <br/>
│   └── tuner_bridge.h <br/>
├── resources/               # Optional: icons, fonts, GUI assets <br/>
├── target/                  # Build output (auto-generated) <br/>
└── README.md                # Project description & instructions <br/>
