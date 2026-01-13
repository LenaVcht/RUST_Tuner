# RUST_Tuner

# Roadmap

## Objective of our project

The goal of this project is to develop a high-performance musical instrument tuner. It uses **Rust** for Digital Signal Processing (DSP) to ensure memory safety and execution speed, and the **JUCE framework** for cross-platform audio hardware management via the **cxx-juce bridge**.

## Technical architecture

- **Audio** : using JUCE's AudioDeviceManager to capture real-time microphone input
- **DSP Engine (RUST)** : Implementation of the YIN algorithm for fundamental frequency detection, chosen for its robustness against harmonic interference.
- **Data Management** : Integration of a circular buffer to accumulate audio samples, enabling precise frequency analysis.

## Development Steps

### Phase 1: Infrastructure & Capture (Completed)

- Set up the hybrid Rust/C++ build environment.
- Initialized audio input channels and validated signal flow via peak level monitoring.

### Phase 2: Signal Analysis (In Progress)

- Development of the core pitch detection logic (YIN implementation).
- Implement the computing of difference between actual sound and the "perfect pitch".

### Phase 3: UI (Upcoming)

- Design of a simple graphical interface.
