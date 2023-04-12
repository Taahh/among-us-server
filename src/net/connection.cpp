#include "connection.hpp"

void Connection::sendPacket(const Buffer &buffer) {
    socket->send_to(asio::buffer(buffer.getBuffer(), buffer.getSize()), *this->endpoint);
    delete &buffer;
}
