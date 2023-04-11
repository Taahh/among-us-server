#include "reliable.hpp"
#include "root/roots.hpp"

ReliablePacket::ReliablePacket(unsigned short nonce) : nonce(nonce) {
    this->reliables[0x00] = new HostServer();
}

ReliablePacket::ReliablePacket(unsigned short nonce, queue<Packet*> serialize) : nonce(nonce) {
    this->toDo = serialize;
}

ReliablePacket::ReliablePacket(unsigned short nonce, Packet* serialize) : nonce(nonce) {
    this->toDo.push(serialize);
}