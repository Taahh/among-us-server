#ifndef ACKNOWLEDGEMENT_PACKET_HPP
#define ACKNOWLEDGEMENT_PACKET_HPP

#include "../packet.hpp"
#include "../../buffer/hazel.hpp"

class AcknowledgementPacket : public Packet {
private:
    unsigned short nonce;
public:
    AcknowledgementPacket(unsigned short nonce): nonce(nonce) {}

    Buffer* serialize() override;

    void deserialize(Buffer &buffer) override {
    }

    void process_packet(Connection &connection) override {
    }
};

#endif //ACKNOWLEDGEMENT_PACKET_HPP
