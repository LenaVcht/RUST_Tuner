use {
    cxx_juce::{
        juce_audio_basics::AudioSampleBuffer,
        juce_audio_devices::{AudioDeviceCallback, AudioDeviceManager, AudioIODevice},
        JuceError, JUCE,
    },
    std::{pin::Pin, thread::sleep, time::Duration},
};

#[derive(Default)]
struct TunerCallback {
    // We can add a buffer here to store samples later
    sample_rate: f64,
    buffer: Vec<f32>,
    analysis_size: usize,
}

impl AudioDeviceCallback for TunerCallback {
    fn about_to_start(&mut self, mut device: Pin<&mut AudioIODevice>) {
        self.sample_rate = device.as_mut().get_current_sample_rate();
        self.analysis_size = 4096; 
        self.buffer = Vec::with_capacity(self.analysis_size);
        println!("🎤 Démarrage de la capture à {:.1} Hz", self.sample_rate);
    }

    fn process_block(
        &mut self,
        input: &AudioSampleBuffer,
        _output: Pin<&mut AudioSampleBuffer>,
    ) {
        // 1. Check if we have input channels
        if input.get_num_channels() > 0 {
            // 2. Retrieve samples from channel 0 (microphone)
            let input_samples = input.get_read_slice(0);

            // 3. Store samples in buffer for analysis
            for &s in input_samples {
                if self.buffer.len() < self.analysis_size {
                    self.buffer.push(s);
                }
            }

            // 4. Once we have enough samples, perform a simple analysis
            if self.buffer.len() >= self.analysis_size {
                self.analyze_pitch();

                self.buffer.clear(); // Clear buffer for next batch
            }
        }
    }

    fn stopped(&mut self) {
        println!("🎤 Capture stopped.");
    }
}

impl TunerCallback {
    fn analyze_pitch(&self) {
        if self.buffer.len() < self.analysis_size { return; }

        let samples = &self.buffer;
        let n = self.analysis_size / 2; // We analyze on half of the buffer for the offset
        let mut diff = vec![0.0f32; n];

        // STEP 1: Calculate the difference function
        // d(tau) = sum( (x[j] - x[j + tau])^2 )
        for tau in 1..n {
            for j in 0..n {
                let delta = samples[j] - samples[j + tau];
                diff[tau] += delta * delta;
            }
        }

        // STEP 2: Cumulative mean normalized difference function
        // This helps to avoid detecting harmonics too early
        let mut cmndf = vec![0.0f32; n];
        cmndf[0] = 1.0;
        let mut running_sum = 0.0;
        for tau in 1..n {
            running_sum += diff[tau];
            cmndf[tau] = diff[tau] / ((1.0 / tau as f32) * running_sum);
        }

        // STEP 3: Search for the first dip (Threshold)
        let threshold = 0.15; // Typical value for YIN
        let mut pitch_tau = None;
        
        for tau in 1..n {
            if cmndf[tau] < threshold {
                // We search for the local minimum
                let mut best_tau = tau;
                while best_tau + 1 < n && cmndf[best_tau + 1] < cmndf[best_tau] {
                    best_tau += 1;
                }
                pitch_tau = Some(best_tau);
                break;
            }
        }

        // STEP 4: Conversion to frequency (Hz)
        if let Some(tau) = pitch_tau {
            let frequency = self.sample_rate as f32 / tau as f32;
            if frequency > 30.0 && frequency < 2000.0 { // Filter for musical instruments
                println!("Detected note: {:.2} Hz", frequency);
                self.print_note_name(frequency);
            }
        }
    }

    fn print_note_name(&self, freq: f32) {
        // Simple formula to convert Hz to semitones (MIDI)
        // 69 is A 440Hz
        let midi = 12.0 * (freq / 440.0).log2() + 69.0;
        let names = ["C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"];
        let note_idx = (midi.round() as usize) % 12;
        println!("🎵 Close to: {}", names[note_idx]);
    }
}

fn main() -> Result<(), JuceError> {
    // 1. Initialize JUCE
    let juce = JUCE::initialise();

    // 2. Configure the device manager
    let mut device_manager = AudioDeviceManager::new(&juce);
    // Request 1 input channel (microphone) and 0 output channels (to avoid feedback)
    device_manager.initialise(1, 0)?;

    // 3. Create and register the Callback
    let tuner = TunerCallback::default();
    let handle = device_manager.add_audio_callback(tuner);

    println!("--- Rust/JUCE Tuner ---");
    println!("Speak into your microphone to test...");
    
    // 4. Main loop (the program runs for 5 seconds)
    for _ in (1..=5).rev() {
        sleep(Duration::from_secs(1));
    }

    // Cleanup
    device_manager.remove_audio_callback(handle);

    Ok(())
}