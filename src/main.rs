use cpal::traits::{DeviceTrait, HostTrait, StreamTrait};

fn main() {
    let host = cpal::default_host();
    
    // 1. Get the default input device (Microphone)
    let device = host.default_input_device()
        .expect("Failed to find input device. Is your mic plugged in?");

    println!("Using input device: {}", device.name().unwrap());

    // 2. Get default input configuration
    let config = device.default_input_config().expect("Failed to get default input config");
    
    // 3. Define the error callback
    let err_fn = |err| eprintln!("An error occurred on the input stream: {}", err);

    // 4. Build and run the stream based on the sample format
    // Most modern mics use f32, but we handle i16/u16 just in case.
    let stream = match config.sample_format() {
        cpal::SampleFormat::F32 => {
            device.build_input_stream(
                &config.into(),
                move |data: &[f32], _: &cpal::InputCallbackInfo| {
                    print_amplitude(data);
                },
                err_fn,
                None
            )
        },
        sample_format => panic!("Unsupported sample format: {}", sample_format),
    }.unwrap();

    // 5. Start the stream
    stream.play().unwrap();
    println!("Listening... Speak into the mic! (Ctrl+C to stop)");

    // Keep the main thread alive for 10 seconds
    std::thread::sleep(std::time::Duration::from_secs(10));
}

fn print_amplitude(samples: &[f32]) {
    // Find the highest absolute value in this buffer
    let max_amp = samples.iter()
        .map(|&s| s.abs())
        .fold(0.0, f32::max);

    // Create a simple visual meter
    let meter_size = (max_amp * 50.0) as usize;
    let meter = "=".repeat(meter_size);
    print!("\r[{:<50}]", meter);
    
    // Flush stdout so the meter updates on the same line
    use std::io::{self, Write};
    io::stdout().flush().unwrap();
}