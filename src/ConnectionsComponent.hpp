#pragma once
#include <JuceHeader.h>
#include "ConnectionComponent.hpp"

using namespace juce;

// Connections holds an array of Connections, giving the ability to add and delete new ones
struct Connections : public Component, public Connection::Listener {
    Connections() {}

    void paint(Graphics &g) override {
        g.fillAll(Colours::lightblue);
    }

    void resized() override {
        FlexBox fb;
        fb.flexDirection  = FlexBox::Direction::column;
        fb.justifyContent = FlexBox::JustifyContent::flexStart;

        for (auto *client: clients) {
            fb.items.add(FlexItem(*client)
                                 .withFlex(1)
                                 .withMaxHeight((float) getHeight() / 10)
                                 .withMargin(FlexItem::Margin(5, 5, 5, 5)));
        }

        fb.performLayout(getLocalBounds());
    }

    void add_client(ConnectionType type, const String &code) {
        auto conn = std::make_unique<ClientConnection>((int)type, [&](const MemoryBlock &) {});
        if (conn->connectToSocket(code, 8888, 1000)) {
            auto client = clients.add(new Connection(type, code, conn.release()));
            client->addListener(this);
            addAndMakeVisible(client);
            resized();
        } else {
            DBG("Failed to connect to server");
            jassertfalse;
        }
    }

    void on_delete(Connection *obj) override {
        clients.removeObject(obj);
        resized();
    }

    void on_mute(Connection *obj) override {
        obj->_conn->mute(obj->connection_mute.getToggleState());
    }

    void on_set_type(Connection* obj) override {
        obj->_conn->set_type(obj->connection_type.getSelectedId());
    }

    OwnedArray<Connection> clients;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Connections)
};