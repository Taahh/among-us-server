#ifndef RELIABLE_PACKET_HPP
#define RELIABLE_PACKET_HPP

#include <queue>
#include "reliable/reliables.hpp"
#include "../packet.hpp"
#include "../../buffer/hazel.hpp"

class ReliablePacket : public Packet {
private:
    unsigned short nonce;
    unordered_map<int, Packet *> reliables;
    queue<Packet*> toDo;

public:
    ReliablePacket(unsigned short nonce) : nonce(nonce) {
        this->reliables[0x00] = new HostServer();
    }

    ReliablePacket(unsigned short nonce, queue<Packet*> serialize) : nonce(nonce) {
        this->toDo = serialize;
    }

    ReliablePacket(unsigned short nonce, Packet* serialize) : nonce(nonce) {
        this->toDo.push(serialize);
    }

    ~ReliablePacket() {
        for (const auto &item: reliables) {
            delete item.second;
        }
    }

    Buffer *serialize() override {
        Buffer* buffer = new Buffer(4096);
        buffer->write_byte(0x01);
        buffer->write_unsigned_short(this->nonce);
        while (!this->toDo.empty()) {
            buffer->write_buffer(*this->toDo.front()->serialize());
        }
    }

    void deserialize(Buffer &buffer) override {
        while (buffer.getBuffer() != nullptr) {
            HazelMessage hazel = HazelMessage::read_message(buffer);
            if (reliables.contains(hazel.getTag())) {
                reliables[hazel.getTag()]->deserialize(*hazel.getBuffer());
                toDo.push(reliables[hazel.getTag()]);
            }
            break;
        }
    }

    void process_packet(Connection &connection) override {
        AcknowledgementPacket ackPacket(this->nonce);
        connection.sendPacket(*ackPacket.serialize());

        while (!toDo.empty()) {
            toDo.front()->process_packet(connection);
            toDo.pop();
        }
    }
};

#endif //RELIABLE_PACKET_HPP
