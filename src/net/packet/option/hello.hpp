#ifndef HELLO_PACKET_HPP
#define HELLO_PACKET_HPP

#include "../packet.hpp"
#include "../../buffer/hazel.hpp"

class PlatformSpecificData : public Deserializable {
public:
    void deserialize(Buffer &buffer) override;
};

class HelloPacket : public Packet {
private:
    unsigned short nonce;
    string username;
public:
    HelloPacket(unsigned short nonce): nonce(nonce) {}

    inline Buffer* serialize() override {
        return nullptr;
    }

    void deserialize(Buffer &buffer) override;

    void process_packet(Connection &connection) override;
};

#endif //HELLO_PACKET_HPP
