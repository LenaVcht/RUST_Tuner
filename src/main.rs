mod gui;

use cpal::traits::{DeviceTrait, HostTrait, StreamTrait};
use ringbuf::traits::{Consumer, Producer, Split, Observer};
use ringbuf::HeapRb;
use yin_rs::Yin;
use std::sync::{Arc, Mutex};
use std::thread;
use std::io::Write;

// We import the SharedState struct from the gui module
use gui::SharedState;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    // 1. Creation of shared state
    let shared_state = Arc::new(Mutex::new(SharedState {
        note: "--".to_string(),
        freq_hz: 0.0,
        cents: 0.0,
    }));

    let shared_state_audio = shared_state.clone();

    // 2. Audio Configuration
    let host = cpal::default_host();
    let device = host
        .default_input_device()
        .expect("No input device available");
    let config: cpal::StreamConfig = device.default_input_config()?.into();
    let sample_rate = config.sample_rate.0 as f64;
    let channels = config.channels as usize;

    println!("Microphone: {}", device.name().unwrap_or_default());
    println!("Sample Rate: {} Hz", sample_rate);

    // 3. Circular buffer
    let ring = HeapRb::<f64>::new(8192);
    let (mut producer, mut consumer) = ring.split();

    // 4. Audio stream
    let stream = device.build_input_stream(
        &config,
        move |data: &[f32], _: &cpal::InputCallbackInfo| {
            for frame in data.chunks(channels) {
                let sample = frame[0];
                let _ = producer.try_push(sample as f64);
            }
        },
        |err| eprintln!("Audio stream error: {}", err),
        None,
    )?;

    stream.play()?;

    // 5. Audio Thread (YIN + Console Print + Update GUI)
    thread::spawn(move || {
        let yin = Yin::init(0.1, 60.0, 1000.0, sample_rate);
        let window_size = 4096; 
        let mut buffer: Vec<f64> = vec![0.0; window_size];

        println!("Audio engine started. Waiting for sound...\n");

        loop {
            if consumer.occupied_len() >= window_size {
                consumer.pop_slice(&mut buffer);

                if let Ok(yin_result) = yin.yin(&buffer) {
                    let frequency = yin_result.get_frequency_with_interpolation();

                    // We filter out aberrant or too low frequencies
                    if frequency > 20.0 && frequency < 2000.0 {
                        let (note, cents) = freq_to_note(frequency);

                        // A. UPDATE GUI
                        {
                            if let Ok(mut state) = shared_state_audio.lock() {
                                state.note = note.clone();
                                state.freq_hz = frequency as f32;
                                state.cents = cents as f32;
                            }
                        }

                        // B. CONSOLE DISPLAY (DEBUG)
                        // Debug output in console
                        print_tuner(note, cents, frequency);
                    }
                }
            } else {
                thread::sleep(std::time::Duration::from_millis(5));
            }
        }
    });

    // 6. Launch GUI
    gui::run_gui(shared_state)?;

    Ok(())
}

// --- UTILITY FUNCTIONS ---

fn freq_to_note(freq: f64) -> (String, f64) {
    let a4 = 440.0;
    let semitones_from_a4 = 12.0 * (freq / a4).log2();
    let midi_note = (69.0 + semitones_from_a4).round();
    
    let freq_midi = a4 * 2.0f64.powf((midi_note - 69.0) / 12.0);
    let cents = 1200.0 * (freq / freq_midi).log2();

    let notes = [
        "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"
    ];
    
    let note_index = (midi_note as usize) % 12;
    let octave = (midi_note as isize / 12) - 1;
    
    (format!("{}{}", notes[note_index], octave), cents)
}

/// Debug console print function
fn print_tuner(note: String, cents: f64, freq: f64) {
    // Clear the current line
    print!("\r\x1b[K"); 
    
    let bar_width = 20;
    let mut bar = String::new();
    
    let position = ((cents + 50.0) / 100.0 * (bar_width as f64 * 2.0)).round() as usize;
    // Safety clamp to avoid out-of-bounds
    let position = position.clamp(0, bar_width * 2);

    for i in 0..(bar_width * 2 + 1) {
        if i == position {
            bar.push('O'); 
        } else if i == bar_width {
            bar.push('|'); 
        } else {
            bar.push('-');
        }
    }

    let color = if cents.abs() < 5.0 { "\x1b[32m" } else { "\x1b[31m" };
    let reset = "\x1b[0m";

    print!("Note: {:<4} Freq: {:<6.1} Hz {}[{}] {:+.1} cents{}", 
        note, freq, color, bar, cents, reset);
        
    std::io::stdout().flush().unwrap();
}