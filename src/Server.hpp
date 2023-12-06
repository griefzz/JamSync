#pragma once
#include <JuceHeader.h>
#include <format>
#include <string>
#include <functional>

using namespace juce;

using on_message = std::function<void(const MemoryBlock &)>;

/** Simple repeater class that sends received text to an action listener. */
class ServerConnection : public InterprocessConnection {
public:
    ServerConnection(on_message on_message_cb) : on_message_cb(on_message_cb), InterprocessConnection(false) {}
    ~ServerConnection() { disconnect(); }
    void connectionMade() override { DBG("Client connected.\n"); }
    void connectionLost() override { DBG("Client disconnected.\n"); }
    void messageReceived(const MemoryBlock &message) override {
        on_message_cb(message);
    }

    on_message on_message_cb;
};

class Server : public InterprocessConnectionServer {
public:
    Server() {}
    InterprocessConnection *createConnectionObject() override {
        process.add(new ServerConnection([&](const MemoryBlock &) {}));
        return process.getLast();
    }

private:

    OwnedArray<ServerConnection> process;
};
