#pragma once
#include <JuceHeader.h>
#include "ConnectorComponent.hpp"
#include "ConnectionsComponent.hpp"

using namespace juce;

class Main : public Component {
public:
    //==============================================================================
    Main() : connector(&connections) {
        addAndMakeVisible(connector);
        addAndMakeVisible(connections);

        setSize(600, 400);
    }

    void paint(Graphics &g) override {
        g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
    }

    void resized() override {
        Grid grid;

        using Track = Grid::TrackInfo;
        using Fr    = Grid::Fr;

        grid.templateRows    = {Track(Fr(1)), Track(Fr(5))};
        grid.templateColumns = {Track(Fr(1))};

        grid.items = {GridItem(connector), GridItem(connections)};

        grid.performLayout(getLocalBounds());
    }

private:
    //==============================================================================
    Connector connector;
    Connections connections;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Main)
};