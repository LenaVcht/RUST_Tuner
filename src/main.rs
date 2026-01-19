mod gui;

use std::sync::{Arc, Mutex};

use cpal::traits::{DeviceTrait, HostTrait, StreamTrait};
use ringbuf::traits::{Consumer, Producer, Split, Observer};
use ringbuf::HeapRb;
use yin_rs::Yin;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    // 1. Audio configuration (CPAL)
    let host = cpal::default_host();
    let device = host
        .default_input_device()
        .expect("No input device available");

    let config: cpal::StreamConfig = device.default_input_config()?.into();
    let sample_rate = config.sample_rate.0 as f64;
    let channels = config.channels as usize;

    println!("Microphone: {}", device.name()?);
    println!("Sample Rate: {} Hz", sample_rate);
    println!("Channels: {}", channels);

    // 2. Circular buffer creation
    let ring = HeapRb::<f64>::new(8192);
    let (mut producer, mut consumer) = ring.split();

    // 3. Audio stream construction
    let stream = device.build_input_stream(
        &config,
        move |data: &[f32], _: &cpal::InputCallbackInfo| {
            for frame in data.chunks(channels) {
                // We only take the first sample of the packet (Left Channel / Mono)
                let sample = frame[0];
                let _ = producer.try_push(sample as f64);
            }
        },
        |err| eprintln!("Audio stream error: {}", err),
        None,
    )?;

    stream.play()?;

    // 4. YIN pitch detection initialization
    let yin = Yin::init(0.1, 60.0, 1000.0, sample_rate);
    
    let window_size = 4096; 
    let mut buffer: Vec<f64> = vec![0.0; window_size];

    println!("Tuner listening... (Ctrl+C to quit)\n");

    // 5. Main loop
    loop {
        if consumer.occupied_len() >= window_size {
            // We fill the buffer
            consumer.pop_slice(&mut buffer);

            // YIN analysis
            if let Ok(yin_result) = yin.yin(&buffer) {
                let frequency = yin_result.get_frequency_with_interpolation();

                if frequency > 20.0 && frequency < 2000.0 {
                    let (note, deviation) = freq_to_note(frequency);
                    print_tuner(note, deviation, frequency);
                }
            }
        } else {
            // Small pause to avoid running the CPU at 100%
            std::thread::sleep(std::time::Duration::from_millis(10));
        }
    }
}

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

fn print_tuner(note: String, cents: f64, freq: f64) {
    print!("\r\x1b[K"); 
    
    let bar_width = 20;
    let mut bar = String::new();
    
    let position = ((cents + 50.0) / 100.0 * (bar_width as f64 * 2.0)).round() as usize;
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
        
    use std::io::Write;
    std::io::stdout().flush().unwrap();
}