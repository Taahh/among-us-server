#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <iostream>
#include <bit>
#include <stdexcept>
#include <linux/kernel.h>
#include <boost/endian/conversion.hpp>

using namespace std;

constexpr bool is_little_endian = std::endian::native == std::endian::little;

class Buffer {
private:
    char *buffer;
    bool deleteBuffer;
    unsigned int size;
public:
    Buffer(char &buffer, unsigned int size) : buffer(&buffer), size(size), deleteBuffer(false) {}

    Buffer(int size) {
        this->buffer = new char[size];
        this->deleteBuffer = true;
        this->size = 0;
    }

    ~Buffer() {
        if (deleteBuffer) {
            delete[] this->buffer;
        }
    }

    char *getBuffer() const {
        return buffer;
    }

    unsigned int getSize() const {
        return size;
    }

    void print();

    void write_buffer(Buffer &buffer);

    void write_byte(int val);

    void write_unsigned_short(unsigned short val);

    void write_unsigned_short_le(unsigned short val);

    void write_short(short val);

    void write_short_le(short val);

    void write_packed_unsigned_int(unsigned int value);

    void write_packed_int(int value);

    void write_unsigned_int(unsigned int val);

    void write_unsigned_int_le(unsigned int val);

    void write_int(int val);

    void write_int_le(int val);

    void write_unsigned_long(unsigned long val);

    void write_unsigned_long_le(unsigned long val);

    void write_long(long val);

    void write_long_le(long val);

    void write_string(string val);

    int read_byte();

    unsigned short read_unsigned_short();

    unsigned short read_unsigned_short_le();

    short read_short();

    unsigned int read_packed_unsigned_int();

    int read_packed_int();

    unsigned int read_unsigned_int();

    unsigned int read_unsigned_int_le();

    int read_int();

    int read_int_le();

    int read_unsigned_long();

    int read_long();

    float read_float();

    float read_float_le();

    string read_string();
};

#endif //BUFFER_HPP
