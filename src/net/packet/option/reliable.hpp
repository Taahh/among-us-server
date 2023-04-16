#ifndef RELIABLE_PACKET_HPP
#define RELIABLE_PACKET_HPP

#include <queue>
#include "../packet.hpp"
#include "../../buffer/hazel.hpp"

class ReliablePacket : public Packet {
private:
    unsigned short nonce;
    unordered_map<int, Packet *> reliables;
    queue<Packet*> toDo;
    queue<Buffer*> toSerialize;
public:
    ReliablePacket(unsigned short nonce);

    ReliablePacket(unsigned short nonce, Buffer& serialize);

    ~ReliablePacket() {
        for (const auto &item: reliables) {
            delete item.second;
        }
        while (!toDo.empty()) {
            delete toDo.front();
        }
    }

    void serialize(Buffer& buffer) override;

    bool deserialize(Buffer &buffer) override;

    void process_packet(Connection &connection) override;
};

#endif //RELIABLE_PACKET_HPP
