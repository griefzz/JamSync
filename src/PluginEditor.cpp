/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ServerplugAudioProcessorEditor::ServerplugAudioProcessorEditor(ServerplugAudioProcessor &p)
    : AudioProcessorEditor(&p), audioProcessor(p) {
    addAndMakeVisible(mainComponent);
    setResizable(true, false);
    setSize(400, 300);
}

ServerplugAudioProcessorEditor::~ServerplugAudioProcessorEditor() {
}

//==============================================================================
void ServerplugAudioProcessorEditor::paint(juce::Graphics &g) {
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void ServerplugAudioProcessorEditor::resized() {
    mainComponent.setBounds(getLocalBounds());
}
