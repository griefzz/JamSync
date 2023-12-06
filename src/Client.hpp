#pragma once
#include <string>
#include <chrono>
#include <format>
#include <iostream>
#include <functional>
#include <JuceHeader.h>

using namespace juce;

using on_message = std::function<void(const MemoryBlock &)>;


struct ClientConnection : InterprocessConnection {
    enum ConnectionType { Input = 1,
                          Output,
                          Both };
    ClientConnection(int type, on_message on_message_cb) : on_message_cb(on_message_cb), InterprocessConnection(false) {}
    ~ClientConnection() { disconnect(); }
    void connectionMade() override { DBG("Connected."); }
    void connectionLost() override { DBG("Disconnected."); }
    void messageReceived(const MemoryBlock &message) override {
        if (!muted && ctype != Input) on_message_cb(message);
    }

    // Callbacks for each connection
    bool muted = false;
    void mute(bool on) { muted = on; }

    ConnectionType ctype;
    void set_type(int type) { type = (ConnectionType) ctype; }

    on_message on_message_cb;
};
