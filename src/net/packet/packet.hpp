#ifndef PACKET_HPP
#define PACKET_HPP

#include "../buffer/buffer.hpp"

class Serializable {
public:
    virtual void serialize(Buffer& buffer) = 0;
};

class Deserializable {
public:
    virtual void deserialize(Buffer& buffer) = 0;
};

class Packet : public Serializable, public Deserializable {

};

#endif //PACKET_HPP
