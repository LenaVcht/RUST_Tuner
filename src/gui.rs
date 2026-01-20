use eframe::egui;
use std::sync::{Arc, Mutex};

use crate::note::{self, Note};

/// Shared state between audio thread (cpal) and GUI.
#[derive(Default)]
pub struct SharedState {
    pub note_name: String,   // "A"
    pub note_octave: i32,    // 4
    pub freq_hz: f32,        // 440.0
    pub cents: f32,          // -3.5
    pub neighbor_left: String,  // "Ab"
    pub neighbor_right: String, // "A#"
}

impl SharedState {
    // Helper too update from audio thread
    pub fn update_from(&mut self, note: &Note) {
        self.note_name = note.name.clone();
        self.note_octave = note.octave;
        self.freq_hz = note.freq as f32;
        self.cents = note.cents as f32;
        
        let (left, right) = note.neighbors();
        self.neighbor_left = left;
        self.neighbor_right = right;
    }
}

/// GUI app struct.
pub struct TunerApp {
    shared_state: Arc<Mutex<SharedState>>,
}

impl TunerApp {
    pub fn new(shared_state: Arc<Mutex<SharedState>>) -> Self {
        Self { shared_state }
    }
}

/// Starts the GUI. Called from main.rs.
pub fn run_gui(shared_state: Arc<Mutex<SharedState>>) -> Result<(), eframe::Error> {
    let options = eframe::NativeOptions::default();

    eframe::run_native(
        "Rust Tuner",
        options,
        Box::new({
            let shared_state = shared_state.clone();
            move |_cc| Ok(Box::new(TunerApp::new(shared_state.clone())))
        }),
    )
}

impl eframe::App for TunerApp {
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        ctx.request_repaint();
        // Read shared state
        let state = self.shared_state.lock().unwrap();
        let center_note = format!("{}{}", state.note_name, state.note_octave);
        let note_letter = state.note_name.clone(); 
        let left = state.neighbor_left.clone();
        let right = state.neighbor_right.clone();
        let freq = state.freq_hz;
        let cents = state.cents;
        drop(state);

        // Decide if we are "in tune"
        let in_tune_threshold = 5.0; // +/- 5 cents window
        let in_tune = cents.abs() <= in_tune_threshold;

        let main_color = if in_tune { neon_green() } else { neon_orange() };

        // Start of the interface drawing
        egui::CentralPanel::default()
            .frame(
                egui::Frame::none()
                    .fill(egui::Color32::from_rgb(10, 10, 10))
                    .inner_margin(egui::Margin::same(24.0)),
            )
            .show(ctx, |ui| {
                ui.vertical_centered(|ui| {
                    ui.add_space(8.0);

                    // "IN TUNE" label at the top
                    ui.label(
                        egui::RichText::new("IN TUNE")
                            .size(20.0)
                            .color(if in_tune {
                                main_color
                            } else {
                                egui::Color32::from_gray(150)
                            })
                            .extra_letter_spacing(2.0),
                    );

                    ui.add_space(8.0);

                    // Center note + scale + moving line + neighbor notes + Hz
                    draw_tuning_area(
                        ui,
                        &note_letter,
                        &left,
                        &right,
                        freq,
                        cents,
                        main_color,
                    );

                    ui.add_space(32.0);

                    ui.separator(); 
                    ui.add_space(8.0);

                    // References for standard tuning notes
                    ui.label(
                        egui::RichText::new("REFERENCE TUNING NOTES")
                            .size(12.0)
                            .color(egui::Color32::from_gray(100))
                            .extra_letter_spacing(1.0),
                    );

                    ui.add_space(4.0);

                    // 3. Use a Grid to align every instrument and its notes
                    egui::Grid::new("reference_grid")
                        .striped(false)
                        .spacing(egui::vec2(20.0, 8.0))
                        .show(ui, |ui| {
                            
                            // --- Guitar Line ---
                            ui.label(
                                egui::RichText::new("Guitar")
                                    .color(egui::Color32::from_gray(140))
                            );
                            ui.label(
                                egui::RichText::new("E  A  D  G  B  E")
                                    .size(16.0)
                                    .color(egui::Color32::from_gray(200))
                                    .strong()
                            );
                            ui.end_row(); // End of guitar line

                            // --- Ukulele Line ---
                            ui.label(
                                egui::RichText::new("Ukulele")
                                    .color(egui::Color32::from_gray(140))
                            );
                            ui.label(
                                egui::RichText::new("G  C  E  A")
                                    .size(16.0)
                                    .color(egui::Color32::from_gray(200))
                                    .strong()
                            );
                            ui.end_row(); // End of ukulele line

                            // --- Violin Line ---
                            ui.label(
                                egui::RichText::new("Violin")
                                    .color(egui::Color32::from_gray(140))
                            );
                            ui.label(
                                egui::RichText::new("G  D  A  E")
                                    .size(16.0)
                                    .color(egui::Color32::from_gray(200))
                                    .strong()
                            );
                            ui.end_row(); // End of violin line

                            // --- Viola Line ---
                            ui.label(
                                egui::RichText::new("Viola")
                                    .color(egui::Color32::from_gray(140))
                            );
                            ui.label(
                                egui::RichText::new("C  G  D  A")
                                    .size(16.0)
                                    .color(egui::Color32::from_gray(200))
                                    .strong()
                            );
                            ui.end_row(); // End of viola line

                            // --- Cello Line ---
                            ui.label(
                                egui::RichText::new("Cello")
                                    .color(egui::Color32::from_gray(140))
                            );
                            ui.label(
                                egui::RichText::new("C  G  D  A")
                                    .size(16.0)
                                    .color(egui::Color32::from_gray(200))
                                    .strong()
                            );
                            ui.end_row(); // End of cello line

                            // --- Double Bass Line ---
                            ui.label(
                                egui::RichText::new("Double Bass")
                                    .color(egui::Color32::from_gray(140))
                            );
                            ui.label(
                                egui::RichText::new("E A D G")
                                    .size(16.0)
                                    .color(egui::Color32::from_gray(200))
                                    .strong()
                            );
                            ui.end_row(); // End of double bass line
                        });
                });
            });
    }
}

/// Bright green when in tune.
fn neon_green() -> egui::Color32 {
    egui::Color32::from_rgb(0, 255, 80)
}

/// Orange/red when not in tune.
fn neon_orange() -> egui::Color32 {
    egui::Color32::from_rgb(255, 100, 0)
}

/// Draws the core tuning area:
/// - big note centered on the scale
/// - horizontal row of ticks (with a gap behind the note)
/// - thin white line indicating cents offset
/// - neighbor notes left/right
/// - frequency text below
fn draw_tuning_area(
    ui: &mut egui::Ui,
    center_note: &str,
    left_note: &str,
    right_note: &str,
    freq_hz: f32,
    cents: f32,
    accent: egui::Color32,
) {
    let desired_size = egui::vec2(ui.available_width() * 0.9, 180.0);
    let (rect, _resp) = ui.allocate_exact_size(desired_size, egui::Sense::hover());
    let painter = ui.painter_at(rect);

    // Background for the whole area
    painter.rect_filled(rect, 18.0, egui::Color32::from_rgb(15, 15, 15));

    let center_x = rect.center().x;
    let center_y = rect.center().y;

    // 1) Tick scale
    let scale_height = 48.0;
    let scale_rect = egui::Rect::from_center_size(
        egui::pos2(center_x, center_y + 10.0),
        egui::vec2(rect.width() * 0.9, scale_height),
    );
    let baseline_y = scale_rect.center().y + 6.0;

    let tick_count_each_side = 12;
    let total_ticks = tick_count_each_side * 2 + 1;
    let width = scale_rect.width();
    let dx = width / (total_ticks as f32 - 1.0);
    let left_edge = scale_rect.center().x - width / 2.0;

    // gap behind the big note where no ticks are drawn
    let note_gap_width = 90.0;
    let gap_left = center_x - note_gap_width * 0.5;
    let gap_right = center_x + note_gap_width * 0.5;

    for i in 0..total_ticks {
        let x = left_edge + i as f32 * dx;
        let is_center = i == tick_count_each_side;

        // skip the center tick entirely
        if is_center {
            continue;
        }

        // skip ticks behind the big note
        if x >= gap_left && x <= gap_right {
            continue;
        }

        let tick_height = 18.0;
        let color = egui::Color32::from_gray(90);

        painter.line_segment(
            [
                egui::pos2(x, baseline_y - tick_height / 2.0),
                egui::pos2(x, baseline_y + tick_height / 2.0),
            ],
            (2.0, color),
        );
    }

    // 2) Thin white line that moves according to cents
    let max_cents = 50.0;
    let clamped = cents.clamp(-max_cents, max_cents);
    let t = (clamped + max_cents) / (2.0 * max_cents); // 0..1 across the scale width
    let line_x = left_edge + t * width;

    let line_top = scale_rect.top();
    let line_bottom = scale_rect.bottom();

    painter.line_segment(
        [
            egui::pos2(line_x, line_top),
            egui::pos2(line_x, line_bottom),
        ],
        (3.0, egui::Color32::WHITE),
    );

    // 3) Mask area behind the big note to remove any remaining ticks/line
    let mask_width = 90.0;
    let mask_height = scale_height;
    let mask_rect = egui::Rect::from_center_size(
        egui::pos2(center_x, scale_rect.center().y),
        egui::vec2(mask_width, mask_height + 10.0),
    );
    painter.rect_filled(mask_rect, 0.0, egui::Color32::from_rgb(15, 15, 15));

    // 4) Big center note rendered on top
    painter.text(
        egui::pos2(center_x, scale_rect.center().y - 8.0),
        egui::Align2::CENTER_CENTER,
        center_note,
        egui::FontId::monospace(64.0),
        accent,
    );

    // 5) Neighbor notes left and right
    let neighbor_y = scale_rect.center().y + 32.0;
    let side_offset = scale_rect.width() * 0.55 / 2.0;

    painter.text(
        egui::pos2(center_x - side_offset, neighbor_y),
        egui::Align2::CENTER_CENTER,
        left_note,
        egui::FontId::monospace(20.0),
        egui::Color32::from_gray(220),
    );

    painter.text(
        egui::pos2(center_x + side_offset, neighbor_y),
        egui::Align2::CENTER_CENTER,
        right_note,
        egui::FontId::monospace(20.0),
        egui::Color32::from_gray(220),
    );

    // 6) Frequency display below the scale
    let freq_text = if freq_hz > 0.0 {
        format!("{:.1} Hz", freq_hz)
    } else {
        "-- Hz".to_string()
    };

    painter.text(
        egui::pos2(center_x, rect.bottom() - 18.0),
        egui::Align2::CENTER_CENTER,
        freq_text,
        egui::FontId::monospace(18.0),
        egui::Color32::from_gray(180),
    );

    // Outer subtle outline
    painter.rect_stroke(
        rect.shrink(2.0),
        18.0,
        egui::Stroke::new(1.0, egui::Color32::from_gray(60)),
    );
}