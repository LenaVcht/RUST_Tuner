# RUST_Tuner

# Roadmap

## Objective of our project

The goal of this project is to develop a high-performance musical instrument tuner. It uses **Rust** for Digital Signal Processing (DSP) to ensure memory safety and execution speed, and **CPAL** the cross-platform audio library.

## Technical architecture

- **Audio** : using CPAL to capture real-time microphone input
- **DSP Engine (RUST)** : Implementation of the YIN algorithm for fundamental frequency detection, chosen for its robustness against harmonic interference.
- **Data Management** : Integration of a circular buffer to accumulate audio samples, enabling precise frequency analysis.

## Development Steps

### Phase 1: Infrastructure & Capture

- Set up the hybrid Rust build environment.
- Initialized audio input channels and validated signal flow via peak level monitoring.

### Phase 2: Signal Analysis

- Development of the core pitch detection logic (YIN implementation).
- Implement the computing of difference between actual sound and the "perfect pitch".

### Phase 3: UI

- Design of a simple graphical interface.

### Screenshots of our Application
<img src="https://github.com/LenaVcht/RUST_Tuner/blob/main/Screenshots/Snapshot_26-01-21_17-42-20.png" height="60%" width="80%" alt="Screenshot"/>
<img src="https://github.com/LenaVcht/RUST_Tuner/blob/main/Screenshots/Snapshot_26-01-21_17-44-17.png" height="60%" width="80%" alt="Screenshot"/>


