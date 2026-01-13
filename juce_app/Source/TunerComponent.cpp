#include "TunerComponent.h"

TunerComponent::TunerComponent()
{
    // 1 input (mic), 0 outputs
    setAudioChannels(1, 0);

    addAndMakeVisible(noteLabel);
    addAndMakeVisible(freqLabel);
    addAndMakeVisible(centsLabel);

    noteLabel.setJustificationType(juce::Justification::centred);
    freqLabel.setJustificationType(juce::Justification::centred);
    centsLabel.setJustificationType(juce::Justification::centred);

    noteLabel.setText("Note: --", juce::dontSendNotification);
    freqLabel.setText("Freq: -- Hz", juce::dontSendNotification);
    centsLabel.setText("Cents: --", juce::dontSendNotification);

    setSize(400, 200);
}

TunerComponent::~TunerComponent()
{
    shutdownAudio();
}

void TunerComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    sampleRateHz = (float)sampleRate;
    buffer.reserve((size_t)samplesPerBlockExpected * 4);
}

void TunerComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill)
{
    auto *readPtr = bufferToFill.buffer->getReadPointer(0, bufferToFill.startSample);
    int numSamples = bufferToFill.numSamples;

    for (int i = 0; i < numSamples; ++i)
        buffer.push_back(readPtr[i]);

    const int frameSize = 2048;

    if ((int)buffer.size() >= frameSize)
    {
        // Call into Rust
        NoteInfo result = analyze_pitch(buffer.data(), frameSize, sampleRateHz);

        if (result.freq > 0.0f)
        {
            int midi = result.midi;
            static const char *names[] = {"C", "C#", "D", "D#", "E", "F",
                                          "F#", "G", "G#", "A", "A#", "B"};
            int index = midi % 12;
            int octave = midi / 12 - 1;
            juce::String noteName = juce::String(names[index]) + juce::String(octave);

            // Update GUI on the message thread
            juce::MessageManager::callAsync([this, result, noteName]()
                                            {
                noteLabel.setText ("Note: "  + noteName,                      juce::dontSendNotification);
                freqLabel.setText ("Freq: "  + juce::String (result.freq, 1) + " Hz",
                                   juce::dontSendNotification);
                centsLabel.setText ("Cents: " + juce::String (result.cents, 1),
                                    juce::dontSendNotification); });
        }

        buffer.clear();
    }
}

void TunerComponent::releaseResources()
{
    buffer.clear();
}

void TunerComponent::paint(juce::Graphics &g)
{
    g.fillAll(juce::Colours::black);
}

void TunerComponent::resized()
{
    auto area = getLocalBounds().reduced(10);
    noteLabel.setBounds(area.removeFromTop(40));
    freqLabel.setBounds(area.removeFromTop(40));
    centsLabel.setBounds(area.removeFromTop(40));
}
