#ifndef ACKNOWLEDGEMENT_PACKET_HPP
#define ACKNOWLEDGEMENT_PACKET_HPP

#include "../packet.hpp"
#include "../../buffer/hazel.hpp"

class AcknowledgementPacket : public Packet {
private:
    unsigned short nonce;
public:
    AcknowledgementPacket(unsigned short nonce): nonce(nonce) {}

    void serialize(Buffer &buffer) override {
        buffer.write_byte(0x0a);
        buffer.write_unsigned_short(this->nonce);
        buffer.write_byte(255);
    }

    void deserialize(Buffer &buffer) override {
    }

    void process_packet(Connection &connection) override {
    }
};

#endif //ACKNOWLEDGEMENT_PACKET_HPP
