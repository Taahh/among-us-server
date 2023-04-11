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
    static HazelMessage start_message(int tag) {
        Buffer *buf = new Buffer(4096);
        HazelMessage hazelMessage(0, tag, *buf);
        buf->write_byte(tag);
        buf->write_unsigned_short_le(0x00);
        return hazelMessage;
    };

    void end_message() {
        *(unsigned short*)&this->getBuffer()->getBuffer()[1] = this->buffer->getSize() - 3;
    }

    void copy_to(Buffer &buffer) {
        for (int i = 0; i < this->getBuffer()->getSize(); i++) {
            buffer.write_byte(this->getBuffer()->getBuffer()[i]);
        }
        delete this->buffer;
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
