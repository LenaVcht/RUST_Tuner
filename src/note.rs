pub const A4_FREQ: f64 = 440.0;
pub const NOTES_SHARP: [&str; 12] = ["C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"];
pub const NOTES_FLAT:  [&str; 12] = ["C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "B"];

/// Structure containing all the information about a note
#[derive(Debug, Clone)]
pub struct Note {
    pub name: String,      // Ex: "A"
    pub octave: i32,       // Ex: 4
    pub cents: f64,        // Ex: -12.5
    pub freq: f64,         // Ex: 438.0
    pub midi_index: i32,   // Numéro MIDI (Ex: 69 pour A4)
}

impl Note {
    /// Creates a note from a raw frequency
    pub fn from_frequency(freq: f64) -> Self {
        // Standard formula: MIDI = 69 + 12 * log2(freq / 440)
        let semitones_from_a4 = 12.0 * (freq / A4_FREQ).log2();
        let midi_note_float = 69.0 + semitones_from_a4;
        let midi_note = midi_note_float.round() as i32;

        // Precise calculation of cents
        let freq_midi = A4_FREQ * 2.0f64.powf((midi_note as f64 - 69.0) / 12.0);
        let cents = 1200.0 * (freq / freq_midi).log2();

        let note_idx = (midi_note.rem_euclid(12)) as usize;
        let octave = (midi_note / 12) - 1;

        Note {
            name: NOTES_SHARP[note_idx].to_string(),
            octave,
            cents,
            freq,
            midi_index: midi_note,
        }
    }

    /// Returns the full name (ex: "C#3")
    pub fn full_name(&self) -> String {
        format!("{}{}", self.name, self.octave)
    }

    /// Retrieves the names of neighboring notes (flat on the left, sharp on the right)
    pub fn neighbors(&self) -> (String, String) {
        let prev_idx = (self.midi_index - 1).rem_euclid(12) as usize;
        let next_idx = (self.midi_index + 1).rem_euclid(12) as usize;

        (NOTES_FLAT[prev_idx].to_string(), NOTES_SHARP[next_idx].to_string())
    }
}