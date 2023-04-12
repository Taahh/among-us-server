#include <iostream>
#include <boost/unordered_map.hpp>
#include <boost/asio.hpp>
#include <plog/Log.h>
#include <plog/Initializers/RollingFileInitializer.h>
#include "util/custom_formatter.hpp"

#include "net/connection.hpp"
#include "net/buffer/buffer.hpp"
#include "net/packet/packets.hpp"

namespace asio = boost::asio;
using asio::io_context;
using asio::ip::udp;
using namespace std;

//static const
boost::unordered_map<string, Connection *> connections;

void signalHandle(int signum) {
    for (const auto &item: connections) {
        delete item.second;
    }

    cout << "Exiting Among Us UDP Server" << endl;
    exit(signum);
}

int main() {
    ColoredAppender<plog::TxtFormatter> consoleAppender;
    plog::init(plog::Severity::debug, "log.txt").addAppender(&consoleAppender);
    std::signal(SIGTERM, signalHandle);
    std::signal(SIGABRT, signalHandle);

    io_context context;
    udp::socket socket(context, udp::endpoint(udp::v4(), 22023));
//    cout << "Listening for connections" << endl;
    LOG(plog::info) << "Listening for connections" << endl;

    char buf[4096];
    for (;;) {
        auto data = asio::buffer(buf);

        udp::endpoint remote_endpoint;
        auto size = socket.receive_from(data, remote_endpoint);
        Connection *connection;
        if (connections.contains(remote_endpoint.address().to_string())) {
            connection = connections[remote_endpoint.address().to_string()];
        } else {
            connection = new Connection(remote_endpoint, socket);
            connections[remote_endpoint.address().to_string()] = connection;
        }
        LOG(plog::debug) << "Packet from " << remote_endpoint;
        if (connection->getClientName() != "") LOG(plog::debug) << ", user: " << connection->getClientName() << endl;
        else LOG(plog::debug) << endl;

        Buffer buffer(*buf, size);
        buffer.print();

        int packet_id = buffer.read_byte();
        if (packet_id == 8) {
            unsigned short nonce = buffer.read_unsigned_short();
            HelloPacket packet(nonce);
            packet.deserialize(buffer);
            packet.process_packet(*connection);
        }
        if (packet_id == 1) {
            unsigned short nonce = buffer.read_unsigned_short();
            ReliablePacket packet(nonce);
            packet.deserialize(buffer);
            packet.process_packet(*connection);
        }
        if (packet_id == 0x0c) {
            unsigned short nonce = buffer.read_unsigned_short();
            AcknowledgementPacket ack(nonce);
            connection->sendPacket(*ack.serialize());
        }

    }
}
