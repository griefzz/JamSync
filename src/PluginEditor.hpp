#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.hpp"
#include "MainComponent.hpp"

//==============================================================================
/**
*/
class ServerplugAudioProcessorEditor : public juce::AudioProcessorEditor {
public:
    ServerplugAudioProcessorEditor(ServerplugAudioProcessor &);
    ~ServerplugAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics &) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ServerplugAudioProcessor &audioProcessor;

    MainComponent mainComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ServerplugAudioProcessorEditor)
};
