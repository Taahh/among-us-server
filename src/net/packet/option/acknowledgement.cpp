#include "acknowledgement.hpp"

void AcknowledgementPacket::serialize(Buffer& buffer) {
    buffer.write_byte(0x0a);
    buffer.write_unsigned_short(this->nonce);
    buffer.write_byte(255);
}
