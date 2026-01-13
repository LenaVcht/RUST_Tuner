#pragma once

#include <juce_audio_utils/juce_audio_utils.h>

// C interface to Rust library
extern "C"
{
    typedef struct
    {
        float freq;
        int midi;
        float cents;
    } NoteInfo;

    // This must match the function in your Rust lib.rs
    NoteInfo analyze_pitch(const float *samples_ptr, int len, float sample_rate);
}

class TunerComponent : public juce::AudioAppComponent
{
public:
    TunerComponent();
    ~TunerComponent() override;

    // Audio callbacks
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;
    void releaseResources() override;

    // GUI callbacks
    void paint(juce::Graphics &g) override;
    void resized() override;

private:
    std::vector<float> buffer;
    float sampleRateHz{44100.0f};

    juce::Label noteLabel;
    juce::Label freqLabel;
    juce::Label centsLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TunerComponent)
};
