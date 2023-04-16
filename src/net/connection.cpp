#include "connection.hpp"

void Connection::sendPacket(Packet& packet) {
    Buffer buffer(4096);
    packet.serialize(buffer);
    socket->send_to(asio::buffer(buffer.getBuffer(), buffer.getSize()), *this->endpoint);
}
