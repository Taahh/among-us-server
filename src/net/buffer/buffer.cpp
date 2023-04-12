#include "buffer.hpp"
#include <plog/Log.h>

void Buffer::print() {
    LOG(plog::debug) << "SIZE: " << getSize() << endl;
    LOG(plog::debug) << "DATA: ";
    for (int i = 0; i < getSize(); i++) {
        LOG(plog::debug).printf("\%02hhx", buffer[i]);
        if (i < size - 1) {
            LOG(plog::debug) << " ";
        }
    }
    cout << endl;
}

void Buffer::write_buffer(Buffer &buffer) {
    for (int i = 0; i < buffer.getSize(); i++) {
        write_byte(buffer.buffer[i]);
    }
    delete &buffer;
}

void Buffer::write_byte(int val) {
    *(char *) (buffer + size) = (char) val;
    size++;
}

void Buffer::write_unsigned_short(unsigned short val) {
    val = is_little_endian ? boost::endian::endian_reverse(val) : val;
    *(unsigned short *) (buffer + size) = val;
    size += 2;
}

void Buffer::write_unsigned_short_le(unsigned short val) {
    val = !is_little_endian ? boost::endian::endian_reverse(val) : val;
    *(unsigned short *) (buffer + size) = val;
    size += 2;
}

void Buffer::write_short(short val) {
    val = is_little_endian ? boost::endian::endian_reverse(val) : val;
    *(short *) (buffer + size) = val;
    size += 2;
}

void Buffer::write_short_le(short val) {
    val = !is_little_endian ? boost::endian::endian_reverse(val) : val;
    *(short *) (buffer + size) = val;
    size += 2;
}

void Buffer::write_packed_unsigned_int(unsigned int value) {
    do {
        int b = (int) (value & 0xFF);
        if (value >= 0x80) {
            b |= 0x80;
        }

        write_byte(b);
        value >>= 7;
    } while (value > 0);
}

void Buffer::write_packed_int(int value) {
    write_packed_unsigned_int((unsigned int) value);
}

void Buffer::write_unsigned_int(unsigned int val) {
    val = is_little_endian ? boost::endian::endian_reverse(val) : val;
    *(unsigned int *) (buffer + size) = val;
    size += 4;
}

void Buffer::write_unsigned_int_le(unsigned int val) {
    val = !is_little_endian ? boost::endian::endian_reverse(val) : val;
    *(unsigned int *) (buffer + size) = val;
    size += 4;
}

void Buffer::write_int(int val) {
    val = is_little_endian ? boost::endian::endian_reverse(val) : val;
    *(int *) (buffer + size) = val;
    size += 4;
}

void Buffer::write_int_le(int val) {
    val = !is_little_endian ? boost::endian::endian_reverse(val) : val;
    *(int *) (buffer + size) = val;
    size += 4;
}

void Buffer::write_unsigned_long(unsigned long val) {
    val = is_little_endian ? boost::endian::endian_reverse(val) : val;
    *(unsigned long *) (buffer + size) = val;
    size += 8;
}

void Buffer::write_unsigned_long_le(unsigned long val) {
    val = !is_little_endian ? boost::endian::endian_reverse(val) : val;
    *(unsigned long *) (buffer + size) = val;
    size += 8;
}

void Buffer::write_long(long val) {
    val = is_little_endian ? boost::endian::endian_reverse(val) : val;
    *(long *) (buffer + size) = val;
    size += 8;
}

void Buffer::write_long_le(long val) {
    val = !is_little_endian ? boost::endian::endian_reverse(val) : val;
    *(long *) (buffer + size) = val;
    size += 8;
}

void Buffer::write_string(string val) {
    write_packed_unsigned_int(val.size());
    std::memcpy(buffer + size, val.c_str(), val.size());
    size += val.size();
}

int Buffer::read_byte() {
    char val = *buffer;
    buffer++;
    return val;
}

unsigned short Buffer::read_unsigned_short() {
    unsigned short val = *(unsigned short *) buffer;
    buffer += 2;
    return is_little_endian ? boost::endian::endian_reverse(val) : val;
}

unsigned short Buffer::read_unsigned_short_le() {
    unsigned short val = *(unsigned short *) buffer;
    buffer += 2;
    return !is_little_endian ? boost::endian::endian_reverse(val) : val;
}

short Buffer::read_short() {
    short val = *(short *) buffer;
    buffer += 2;
    return is_little_endian ? boost::endian::endian_reverse(val) : val;
}

unsigned int Buffer::read_packed_unsigned_int() {
    bool read_more = true;
    int shift = 0;
    unsigned int output = 0;

    while (read_more) {
        if (buffer + 1 == nullptr) throw new out_of_range("Read length is longer than message length.");

        int b = Buffer::read_byte();
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

int Buffer::read_packed_int() {
    return (int) Buffer::read_packed_unsigned_int();
}

unsigned int Buffer::read_unsigned_int() {
    unsigned int val = *(unsigned int *) buffer;
    buffer += 4;
    return is_little_endian ? boost::endian::endian_reverse(val) : val;
}

int Buffer::read_int() {
    int val = *(int *) buffer;
    buffer += 4;
    return is_little_endian ? boost::endian::endian_reverse(val) : val;
}

int Buffer::read_unsigned_long() {
    unsigned long val = *(unsigned long *) buffer;
    buffer += 8;
    return is_little_endian ? boost::endian::endian_reverse(val) : val;
}

int Buffer::read_long() {
    long val = *(long *) buffer;
    buffer += 8;
    return is_little_endian ? boost::endian::endian_reverse(val) : val;
}

string Buffer::read_string() {
    unsigned int size = Buffer::read_packed_unsigned_int();
    string data(buffer, buffer + size);
    buffer += size;
    return data;
}