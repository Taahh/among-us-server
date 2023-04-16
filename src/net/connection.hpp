#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "packet/packet.hpp"

#include <queue>
#include <boost/asio.hpp>
#include <boost/functional/hash.hpp>
#include <boost/unordered_set.hpp>
#include <string>
#include "buffer/buffer.hpp"


namespace asio = boost::asio;
using asio::ip::udp;
using namespace std;

class Connection {
private:
    udp::endpoint* endpoint;
    udp::socket* socket;
    string client_name;
    int last_nonce_received;
    int next_nonce;
public:
    Connection(udp::endpoint &endpoint, udp::socket& socket) : endpoint(&endpoint), socket(&socket), client_name(""), last_nonce_received(0), next_nonce(0) {}

    void sendPacket(Packet& packet);

    udp::endpoint *getEndpoint() const {
        return endpoint;
    }

    void setEndpoint(udp::endpoint &endpoint) {
        this->endpoint = &endpoint;
    }

    const string &getClientName() const {
        return client_name;
    }

    void setClientName(const string &clientName) {
        this->client_name = clientName;
    }

    int getLastNonceReceived() const {
        return last_nonce_received;
    }

    void setLastNonceReceived(int lastNonceReceived) {
        this->last_nonce_received = lastNonceReceived;
    }

    int getNextNonce() {
        return next_nonce++;
    }


};
#endif //CONNECTION_HPP
