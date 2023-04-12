#include "reliable.hpp"
#include "root/roots.hpp"
#include "acknowledgement.hpp"

ReliablePacket::ReliablePacket(unsigned short nonce) : nonce(nonce) {
    this->reliables[0x00] = new HostServer();
}

ReliablePacket::ReliablePacket(unsigned short nonce, Buffer &serialize) : nonce(nonce) {
    this->toSerialize.push(&serialize);
}

Buffer *ReliablePacket::serialize() {
    Buffer *buffer = new Buffer(4096);
    buffer->write_byte(0x01);
    buffer->write_unsigned_short(this->nonce);
    while (this->toSerialize.front() && !this->toSerialize.empty()) {
        buffer->write_buffer(*this->toSerialize.front());
//        delete this->toSerialize.front();
        this->toSerialize.pop();
    }
}

void ReliablePacket::deserialize(Buffer &buffer) {
    while (buffer.getBuffer() != nullptr) {
        HazelMessage hazel = HazelMessage::read_message(buffer);
        if (reliables.contains(hazel.getTag())) {
            reliables[hazel.getTag()]->deserialize(*hazel.getBuffer());
            toDo.push(reliables[hazel.getTag()]);
        }
        break;
    }
    cout << "done deserializing" << endl;
}

void ReliablePacket::process_packet(Connection &connection) {
    AcknowledgementPacket ackPacket(this->nonce);
    connection.sendPacket(*ackPacket.serialize());
    cout << "acked" << endl;
    while (!toDo.empty()) {
        toDo.front()->process_packet(connection);
        toDo.pop();
    }
}
