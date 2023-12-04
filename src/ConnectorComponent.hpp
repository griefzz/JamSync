#pragma once
#include <ranges>
#include <JuceHeader.h>
#include "ConnectionsComponent.hpp"

using namespace juce;

// Connector handles adding connections to Connections
struct Connector : public Component {
    Connector(Connections *conns) : _conns(conns) {
        connection_type.addItem("In", 1);
        connection_type.addItem("Out", 2);
        connection_type.addItem("Both", 3);
        connection_type.setSelectedId(3);
        addAndMakeVisible(connection_type);

        connection_code.setText("connection code");
        addAndMakeVisible(connection_code);

        connection_add.setButtonText("Add");
        connection_add.onClick = [&, this]() {
            _conns->add_client((ConnectionType) connection_type.getSelectedId(), connection_code.getText());
        };
        addAndMakeVisible(connection_add);
    }

    void paint(Graphics &g) override {
        g.fillAll(Colours::hotpink);
    }

    void resized() override {
        FlexBox fb;
        fb.flexDirection  = FlexBox::Direction::row;
        fb.justifyContent = FlexBox::JustifyContent::center;

        fb.items.add(FlexItem(connection_type)
                             .withFlex(0, 1, (float) getWidth() / 5.0f)
                             .withMargin(FlexItem::Margin((float) getHeight() / 4, 2.5, (float) getHeight() / 4, 2.5)));

        fb.items.add(FlexItem(connection_code)
                             .withFlex(0, 1, (float) getWidth() / 2.0f)
                             .withMargin(FlexItem::Margin((float) getHeight() / 4, 2.5, (float) getHeight() / 4, 2.5)));

        fb.items.add(FlexItem(connection_add)
                             .withFlex(0, 1, (float) getWidth() / 5.0f)
                             .withMargin(FlexItem::Margin((float) getHeight() / 4, 2.5, (float) getHeight() / 4, 2.5)));

        fb.performLayout(getLocalBounds());
    }

    Connections *_conns;

    ComboBox connection_type;
    TextEditor connection_code;
    TextButton connection_add;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Connector)
};
