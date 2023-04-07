#ifndef HELLO_PACKET_HPP
#define HELLO_PACKET_HPP

#include "../packet.hpp"

class PlatformSpecificData : public Deserializable {
public:
    void deserialize(Buffer &buffer) override {

    }
};

class HelloPacket : public Packet {
private:
    unsigned short nonce;
public:
    HelloPacket(unsigned short nonce): nonce(nonce) {}
    void serialize(Buffer &buffer) override {

    }

    void deserialize(Buffer &buffer) override {
        cout << "HELLO PACKET" << endl;
        printf("Hazel Version: %d\n", buffer.read_byte());
        printf("Client Version: %d\n", buffer.read_int());
        printf("Username: %s\n", buffer.read_string().c_str());
        //DTLS Not Supported
        printf("Last Nonce Received: %d\n", buffer.read_unsigned_int());
        printf("Current Language: %d\n", buffer.read_unsigned_int());
        printf("Chat Mode: %d\n", buffer.read_byte());
        cout << endl;
    }
};

#endif //HELLO_PACKET_HPP
