#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <iostream>
#include <stdexcept>
#include <linux/kernel.h>
#include <boost/endian/conversion.hpp>

using namespace std;

enum Endianness {
    LE,
    BE
};

#if BOOST_ENDIAN_BIG_BYTE
static constexpr Endianness system_endianness = Endianness::BE;
#elif BOOST_ENDIAN_LITTLE_BYTE
static constexpr Endianness system_endianness = Endianness::LE;
#endif

class Buffer {
private:
    char *buffer;
    unsigned int size;
public:
    Buffer(char &buffer, unsigned int size) : buffer(&buffer), size(size) {}

    Buffer(int size) {
        this->buffer = new char[size];
        this->size = 0;
    }

    void print() {
        cout << "SIZE: " << getSize() << endl;
        cout << "DATA: ";
        for (int i = 0; i < getSize(); i++) {
            printf("\%02hhx", buffer[i]);
            if (i < size - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }

    void write_byte(int val) {
        *(int*)(buffer + size) = val;
//        std::memcpy(buffer, &val, sizeof(val));
        size++;
    }

    void write_unsigned_short(unsigned short val) {
        val = system_endianness == LE ? boost::endian::endian_reverse(val) : val;
        *(unsigned short *) (buffer + size) = val;
        size += 2;
    }

    void write_unsigned_short_le(unsigned short val) {
        val = system_endianness == BE ? boost::endian::endian_reverse(val) : val;
        *(unsigned short *) (buffer + size) = val;
        size += 2;
    }

    void write_short(short val) {
        val = system_endianness == LE ? boost::endian::endian_reverse(val) : val;
        *(short *) (buffer + size) = val;
        size += 2;
    }

    void write_short_le(short val) {
        val = system_endianness == BE ? boost::endian::endian_reverse(val) : val;
        *(short *) (buffer + size) = val;
        size += 2;
    }

    void write_packed_unsigned_int(unsigned int value) {
        do {
            int b = (int) (value & 0xFF);
            if (value >= 0x80) {
                b |= 0x80;
            }

            write_byte(b);
            value >>= 7;
        } while (value > 0);
    }

    void write_packed__int(int value) {
        write_packed_unsigned_int((unsigned int) value);
    }

    void write_int(int val) {
        val = system_endianness == LE ? boost::endian::endian_reverse(val) : val;
        *(short *) (buffer + size) = val;
        size += 4;
    }

    void write_int_le(int val) {
        val = system_endianness == BE ? boost::endian::endian_reverse(val) : val;
        *(short *) (buffer + size) = val;
        size += 4;
    }

    void write_unsigned_long(unsigned long val) {
        val = system_endianness == LE ? boost::endian::endian_reverse(val) : val;
        *(short *) (buffer + size) = val;
        size += 8;
    }

    void write_unsigned_long_le(unsigned long val) {
        val = system_endianness == BE ? boost::endian::endian_reverse(val) : val;
        *(short *) (buffer + size) = val;
        size += 8;
    }

    void write_long(long val) {
        val = system_endianness == LE ? boost::endian::endian_reverse(val) : val;
        *(short *) (buffer + size) = val;
        size += 8;
    }

    void write_long_le(long val) {
        val = system_endianness == BE ? boost::endian::endian_reverse(val) : val;
        *(short *) (buffer + size) = val;
        size += 8;
    }

    void write_string(string val) {
        write_packed_unsigned_int(val.size());
        std::memcpy(buffer + size, val.c_str(), val.size());
        size += val.size();
    }

    int read_byte() {
        char val = *buffer;
        buffer++;
        return val;
    }

    unsigned short read_unsigned_short() {
        unsigned short val = *(unsigned short *) buffer;
        buffer += 2;
        return system_endianness == LE ? boost::endian::endian_reverse(val) : val;
    }

    unsigned short read_unsigned_short_le() {
        unsigned short val = *(unsigned short *) buffer;
        buffer += 2;
        return system_endianness == BE ? boost::endian::endian_reverse(val) : val;
    }

    short read_short() {
        short val = *(short *) buffer;
        buffer += 2;
        return system_endianness == LE ? boost::endian::endian_reverse(val) : val;
    }

    unsigned int read_packed_unsigned_int() {
        bool read_more = true;
        int shift = 0;
        unsigned int output = 0;

        while (read_more) {
            if (buffer + 1 == nullptr) throw new out_of_range("Read length is longer than message length.");

            int b = read_byte();
            if (b >= 0x80) {
                read_more = true;
                b ^= 0x80;
            } else {
                read_more = false;
            }

            output |= (unsigned int) (b << shift);
            shift += 7;
        }

        return output;
    }

    int read_packed_int() {
        return (int) read_packed_unsigned_int();
    }

    unsigned int read_unsigned_int() {
        unsigned int val = *(unsigned int *) buffer;
        buffer += 4;
        return system_endianness == LE ? boost::endian::endian_reverse(val) : val;
    }

    int read_int() {
        int val = *(int *) buffer;
        buffer += 4;
        return system_endianness == LE ? boost::endian::endian_reverse(val) : val;
    }

    int read_unsigned_long() {
        unsigned long val = *(unsigned long *) buffer;
        buffer += 8;
        return system_endianness == LE ? boost::endian::endian_reverse(val) : val;
    }

    int read_long() {
        long val = *(long *) buffer;
        buffer += 8;
        return system_endianness == LE ? boost::endian::endian_reverse(val) : val;
    }

    string read_string() {
        unsigned int size = read_packed_unsigned_int();
        string data(buffer, buffer + size);
        buffer += size;
        return data;
    }

    char *getBuffer() const {
        return buffer;
    }

    unsigned int getSize() const {
        return size;
    }
};

#endif //BUFFER_HPP
