#ifndef PACKET_HPP
#define PACKET_HPP

#include "../buffer/buffer.hpp"
#include "../../connection.hpp"

class Serializable {
public:
    virtual void serialize(Buffer& buffer) = 0;
};

class Deserializable {
public:
    virtual void deserialize(Buffer& buffer) = 0;
};

class Packet : public Serializable, public Deserializable {
public:
    virtual void process_packet(Connection& connection) = 0;

};

#endif //PACKET_HPP
