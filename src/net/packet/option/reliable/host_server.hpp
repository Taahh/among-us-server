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
        return nullptr;
    }

    void process_packet(Connection &connection) override {

    }
};

#endif //RELIABLE_HOST_PACKET_HPP
