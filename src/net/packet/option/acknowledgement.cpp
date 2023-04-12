#include "acknowledgement.hpp"

Buffer *AcknowledgementPacket::serialize() {
    Buffer* buffer = new Buffer(4096);
    buffer->write_byte(0x0a);
    buffer->write_unsigned_short(this->nonce);
    buffer->write_byte(255);
    return buffer;
}
