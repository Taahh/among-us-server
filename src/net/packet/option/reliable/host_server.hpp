#ifndef RELIABLE_HOST_PACKET_HPP
#define RELIABLE_HOST_PACKET_HPP

#include "../../packet.hpp"
#include "../../../buffer/hazel.hpp"
#include "../../../game_code.hpp"

class HostServer : public Packet {
private:
    unsigned short nonce;
public:
    void deserialize(Buffer &buffer) override {
        cout << "HOST SERVER" << endl;
    }

    Buffer *serialize() override {
        Buffer* buffer = new Buffer(4096);

        buffer->write_byte(0x01);
        buffer->write_unsigned_short(nonce);
        HazelMessage hazelMessage = HazelMessage::start_message(0x00);
        string code = "TEST";
        hazelMessage.getBuffer()->write_int_le(GameCode::string_to_int(code));
        hazelMessage.end_message();
        hazelMessage.copy_to(*buffer);
        buffer->print();

        return nullptr;
    }

    void process_packet(Connection &connection) override {
        this->serialize();
    }
};

#endif //RELIABLE_HOST_PACKET_HPP
