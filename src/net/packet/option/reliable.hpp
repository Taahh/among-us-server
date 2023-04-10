#ifndef RELIABLE_PACKET_HPP
#define RELIABLE_PACKET_HPP

#include <queue>

#include "../packet.hpp"
#include "../packets.hpp"
#include "../../buffer/hazel.hpp"

class ReliablePacket : public Packet {
private:
    unsigned short nonce;
    unordered_map<int, Packet *> reliables;
    queue<Packet*> process;

public:
    ReliablePacket(unsigned short nonce) : nonce(nonce) {
        this->reliables[0x00] = new HostServer();
    }

    ~ReliablePacket() {
        for (const auto &item: reliables) {
            delete item.second;
        }
    }

    Buffer *serialize() override {
//        Buffer buffer(4096);
//        buffer.write_byte(0x0a);
//        buffer.write_unsigned_short(this->nonce);
//        buffer.write_byte(255);
    }

    void deserialize(Buffer &buffer) override {
        while (buffer.getBuffer() != nullptr) {
            HazelMessage hazel = HazelMessage::read_message(buffer);
            if (reliables.contains(hazel.getTag())) {
                reliables[hazel.getTag()]->deserialize(*hazel.getBuffer());
                process.push(reliables[hazel.getTag()]);
            }
            break;
        }
    }

    void process_packet(Connection &connection) override {
        while (!process.empty()) {
            process.front()->process_packet(connection);
            process.pop();
        }
    }
};

#endif //RELIABLE_PACKET_HPP
