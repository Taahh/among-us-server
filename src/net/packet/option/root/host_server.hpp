#ifndef RELIABLE_HOST_PACKET_HPP
#define RELIABLE_HOST_PACKET_HPP

#include "../reliable.hpp"
#include "../../packet.hpp"
#include "../../../buffer/hazel.hpp"
#include "../../../game_code.hpp"

class HostServer : public Packet {
public:
    bool deserialize(Buffer &buffer) override;

    void serialize(Buffer& buffer) override;

    void process_packet(Connection &connection) override;
};

#endif //RELIABLE_HOST_PACKET_HPP
