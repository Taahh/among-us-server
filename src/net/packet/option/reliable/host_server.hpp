#include "../reliable.hpp"
#ifndef RELIABLE_HOST_PACKET_HPP
#define RELIABLE_HOST_PACKET_HPP

#include "../../packet.hpp"
#include "../../../buffer/hazel.hpp"
#include "../../../game_code.hpp"

class HostServer : public Packet {
public:
    void deserialize(Buffer &buffer) override {
        cout << "HOST SERVER" << endl;
    }

    Buffer *serialize() override {
        HazelMessage hazelMessage = HazelMessage::start_message(0x00);
        string code = "TAAH";
        hazelMessage.getBuffer()->write_int_le(GameCode::string_to_int(code));
        hazelMessage.end_message();

        return hazelMessage.getBuffer();
    }

    void process_packet(Connection &connection) override {
        ReliablePacket reliable(connection.getLastNonceReceived(), this);
        connection.sendPacket(*reliable.serialize());
    }
};

#endif //RELIABLE_HOST_PACKET_HPP
