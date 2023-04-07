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

    void print() {
        cout << "SIZE: " << getSize() << endl;
        cout << "DATA: ";
        for (int i = 0; i < getSize(); i++) {
            printf("\%02hhx", buffer[i]);
            if (i < size - 1) {
                cout << " ";
            }
        }
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

    short read_short() {
        short val = *(short *) buffer;
        buffer += 2;
        return system_endianness == LE ? boost::endian::endian_reverse(val) : val;
    }

    int read_packed_int() {
        return (int) read_packed_unsigned_int();
    }

    unsigned int read_packed_unsigned_int() {
        bool read_more = true;
        int shift = 0;
        unsigned int output = 0;

        while (read_more)
        {
            if (buffer + 1 == nullptr) throw new out_of_range("Read length is longer than message length.");

            int b = read_byte();
            if (b >= 0x80)
            {
                read_more = true;
                b ^= 0x80;
            }
            else
            {
                read_more = false;
            }

            output |= (unsigned int)(b << shift);
            shift += 7;
        }

        return output;
    }

    int read_int() {
        int val = *(int *) buffer;
        buffer += 4;
        return system_endianness == LE ? boost::endian::endian_reverse(val) : val;
    }

    unsigned int read_unsigned_int() {
        unsigned int val = *(unsigned int *) buffer;
        buffer += 4;
        return system_endianness == LE ? boost::endian::endian_reverse(val) : val;
    }

    int read_long() {
        long val = *(long *) buffer;
        buffer += 8;
        return system_endianness == LE ? boost::endian::endian_reverse(val) : val;
    }

    int read_unsigned_long() {
        unsigned long val = *(unsigned long *) buffer;
        buffer += 8;
        return system_endianness == LE ? boost::endian::endian_reverse(val) : val;
    }

    string read_string() {
        unsigned int size = read_packed_unsigned_int();
        string data(buffer, buffer + size);
        buffer += size;
        return data;
    }


    unsigned int getSize() const {
        return size;
    }
};

#endif //BUFFER_HPP
