mod note;
mod gui;

use cpal::traits::{DeviceTrait, HostTrait, StreamTrait};
use ringbuf::traits::{Consumer, Producer, Split, Observer};
use ringbuf::HeapRb;
use yin_rs::Yin;
use std::sync::{Arc, Mutex};
use std::thread;
use std::io::Write;

use gui::SharedState;
use note::Note;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    // 1. Creation of shared state
    let shared_state = Arc::new(Mutex::new(SharedState::default()));
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
                        let note_info = Note::from_frequency(frequency);

                        // A. UPDATE GUI
                        {
                            if let Ok(mut state) = shared_state_audio.lock() {
                                state.update_from(&note_info);
                            }
                        }

                        // B. CONSOLE DISPLAY (DEBUG)
                        // Debug output in console
                        print_tuner(&note_info);
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

// --- DEBUG FUNCTION ---

/// Debug console print function
fn print_tuner(note: &Note) {
    // Clear the current line
    print!("\r\x1b[K"); 
    
    let bar_width = 20;
    let mut bar = String::new();
    
    let position = ((note.cents + 50.0) / 100.0 * (bar_width as f64 * 2.0)).round() as usize;
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

    let color = if note.cents.abs() < 5.0 { "\x1b[32m" } else { "\x1b[31m" };
    let reset = "\x1b[0m";

    print!("Note: {:<4} Freq: {:<6.1} Hz {}[{}] {:+.1} note.cents{}", 
        note.full_name(), note.freq, color, bar, note.cents, reset);
        
    std::io::stdout().flush().unwrap();
}