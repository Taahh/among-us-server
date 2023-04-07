#ifndef HAZEL_HPP
#define HAZEL_HPP

#include "buffer.hpp"

class HazelMessage {
private:
    unsigned short length;
    int tag;
    Buffer* buffer;
    HazelMessage(unsigned short length, int tag, Buffer& buffer) : length(length), tag(tag), buffer(&buffer) {}
public:
    static HazelMessage read_message(Buffer& buffer) {
        unsigned short size = buffer.read_unsigned_short_le();
        int tag = buffer.read_byte();
        HazelMessage hazelMessage(size, tag, buffer);
        return hazelMessage;
    }

    unsigned short getLength() const {
        return length;
    }

    int getTag() const {
        return tag;
    }

    Buffer *getBuffer() const {
        return buffer;
    }
};

#endif //HAZEL_HPP
