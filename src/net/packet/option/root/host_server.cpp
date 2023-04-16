#include "host_server.hpp"
#include "../../../inner/options.hpp"

bool HostServer::deserialize(Buffer &buffer) {
    unsigned int size = buffer.read_packed_unsigned_int();
    PLOG(plog::debug) << "Size of Options: " << size << endl;
    int version = buffer.read_byte();
    PLOGD << "Version: " << version << endl;
    HazelMessage hazel = HazelMessage::read_message(buffer);
    int game_mode = hazel.getBuffer()->read_byte();
    PLOGD << "Game Mode: " << game_mode << endl;
    if (game_mode != 1) {
        PLOGE << "DOES NOT SUPPORT NON NORMAL GAMES CURRENTLY!" << endl;
        return false;
    }
    GameOptionsData data(version);
    data.deserialize(buffer);
}

void HostServer::serialize(Buffer& buffer) {
    HazelMessage hazelMessage = HazelMessage::start_message(0x00);
    string code = "TAAH";
    hazelMessage.getBuffer()->write_int_le(GameCode::string_to_int(code));
    hazelMessage.end_message();
    hazelMessage.copy_to(buffer);
}

void HostServer::process_packet(Connection &connection) {
    Buffer buffer(4096);
    this->serialize(buffer);

    ReliablePacket reliable(connection.getNextNonce(), buffer);
    connection.sendPacket(reliable);
}
