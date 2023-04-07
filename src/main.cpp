#include <iostream>
#include <boost/asio.hpp>
#include "net/buffer/buffer.hpp"
#include "net/packet/packets.hpp"

namespace asio = boost::asio;
using asio::io_context;
using asio::ip::udp;
using namespace std;

int main() {
    io_context context;
    udp::socket socket(context, udp::endpoint(udp::v4(), 22023));
    cout << "Listening for connections" << endl;

    char buf[4096];
    for (;;) {
        auto data = asio::buffer(buf);

        udp::endpoint remote_endpoint;
        auto size = socket.receive_from(data, remote_endpoint);

        Buffer buffer(*buf, size);
        buffer.print();

        cout << endl;

        int packet_id = buffer.read_byte();
        if (packet_id == 8) {
            unsigned short nonce = buffer.read_unsigned_short();
            HelloPacket packet(nonce);
            packet.deserialize(buffer);
//            cout << "Packet ID: " << packet_id << " (HELLO) | Nonce: " << nonce << endl;
//
//            buffer.read_byte(); // hazel version
//            int client_version = buffer.read_int();
//            cout << buffer.read_string() << endl;
        }

    }
}
