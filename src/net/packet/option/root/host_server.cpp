#include "host_server.hpp"

Buffer *HostServer::serialize() {
    HazelMessage hazelMessage = HazelMessage::start_message(0x00);
    string code = "TAAH";
    hazelMessage.getBuffer()->write_int_le(GameCode::string_to_int(code));
    hazelMessage.end_message();

    return hazelMessage.getBuffer();
}

void HostServer::process_packet(Connection &connection) {
    ReliablePacket reliable(connection.getNextNonce(), *this->serialize());
    reliable.serialize();
//    connection.sendPacket(*reliable.serialize());
}
