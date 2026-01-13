/*
Implement:
YIN (yin_pitch)
freq → note (freq_to_note)
small C-FFI wrappers (extern "C")
*/

#[repr(C)]
pub struct NoteInfo {
    pub freq: f32,
    pub midi: i32,
    pub cents: f32,
}

#[no_mangle]
pub extern "C" fn analyze_pitch(samples_ptr: *const f32, len: i32, sample_rate: f32) -> NoteInfo {
    // TODO: real YIN + note logic here
    NoteInfo {
        freq: 440.0,
        midi: 69,
        cents: 0.0,
    }
}
