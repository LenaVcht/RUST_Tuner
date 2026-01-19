mod gui;

use std::sync::{Arc, Mutex};

use cpal::traits::{DeviceTrait, HostTrait, StreamTrait};

fn main() {
    let host = cpal::default_host();

    // 1. Default Input Device (Mikrofon)
    let device = host
        .default_input_device()
        .expect("Failed to find input device. Is your mic plugged in?");

    println!("Using input device: {}", device.name().unwrap());

    // 2. Default Input Config
    let config = device
        .default_input_config()
        .expect("Failed to get default input config");

    let sample_format = config.sample_format();
    let config: cpal::StreamConfig = config.into();

    // Gemeinsamer Zustand für GUI + Audio
    let shared_state = Arc::new(Mutex::new(gui::SharedState {
        note: "–".to_string(),
        freq_hz: 0.0,
        cents: 0.0,
    }));

    // Fehler-Callback
    let err_fn = |err| eprintln!("An error occurred on the input stream: {}", err);

    // Clone für den Audio-Callback
    let shared_for_audio = shared_state.clone();

    // 3. Stream bauen (nur f32 – wie in deinem Code)
    let stream = match sample_format {
        cpal::SampleFormat::F32 => {
            device
                .build_input_stream(
                    &config,
                    move |data: &[f32], _: &cpal::InputCallbackInfo| {
                        // Maximaler Pegel in diesem Buffer
                        let max_amp = data.iter().copied().map(f32::abs).fold(0.0, f32::max);

                        // Hier später: YIN aufrufen und Note/Frequenz/Cents berechnen.
                        // Für den Moment mappen wir die Lautstärke auf -50..+50,
                        // nur damit sich die GUI-Bar bewegt.
                        let mut state = shared_for_audio
                            .lock()
                            .expect("Failed to lock shared GUI state");

                        state.cents = (max_amp * 100.0 - 50.0).clamp(-50.0, 50.0);
                        state.freq_hz = 0.0;
                        state.note = "–".to_string();
                    },
                    err_fn,
                    None,
                )
                .expect("Failed to build input stream")
        }
        other => panic!("Unsupported sample format: {}", other),
    };

    // 4. Stream starten
    stream.play().expect("Failed to start input stream");
    println!("Listening... GUI Tuner is running.");

    // 5. GUI starten (blockiert, bis das Fenster geschlossen wird)
    gui::run_gui(shared_state).expect("Failed to start GUI");

    // Wenn das GUI-Fenster zu ist, fällt main raus und der Stream wird gedroppt.
}
