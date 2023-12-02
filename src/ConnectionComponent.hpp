#pragma once
#include <JuceHeader.h>

using namespace juce;

struct Connection : public Component {
    Connection(const String &code) {
        connection_code.setText(code, dontSendNotification);
        addAndMakeVisible(connection_code);

        connection_delete.setButtonText("Delete");
        connection_delete.onClick = [this]() { listeners.call([&](Listener &l) { l.on_delete(this); }); };
        addAndMakeVisible(connection_delete);

        connection_mute.onClick = [this]() { listeners.call([&](Listener &l) { l.on_mute(this); }); };
        addAndMakeVisible(connection_mute);
    }

    void paint(Graphics &g) override {
        g.fillAll(Colours::black);
    }

    void resized() override {
        FlexBox fb;
        fb.items.add(FlexItem(connection_code).withFlex(1));
        fb.items.add(FlexItem(connection_delete).withFlex(1));
        fb.items.add(FlexItem(connection_mute).withFlex(1));
        fb.performLayout(getLocalBounds());
    }

    struct Listener {
        virtual ~Listener() = default;

        virtual void on_delete(Connection *) = 0;
        virtual void on_mute(Connection *)   = 0;
    };

    void addListener(Listener *newListener) { listeners.add(newListener); }

    ListenerList<Listener> listeners;

    Label connection_code;
    TextButton connection_delete;
    ToggleButton connection_mute;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Connection)
};