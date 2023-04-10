#ifndef HELLO_PACKET_HPP
#define HELLO_PACKET_HPP

#include "../packet.hpp"
#include "../packets.hpp"
#include "../../buffer/hazel.hpp"

class PlatformSpecificData : public Deserializable {
public:
    void deserialize(Buffer &buffer) override {
        HazelMessage hazelMessage = HazelMessage::read_message(buffer);
        printf("Platform: %d\n", hazelMessage.getTag());
        printf("Platform Name: %s\n", hazelMessage.getBuffer()->read_string().c_str());
    }
};

class HelloPacket : public Packet {
private:
    unsigned short nonce;
    string username;
public:
    HelloPacket(unsigned short nonce): nonce(nonce) {}
    Buffer* serialize() override {

    }

    void deserialize(Buffer &buffer) override {
        cout << "HELLO PACKET" << endl;
        printf("Hazel Version: %d\n", buffer.read_byte());
        printf("Client Version: %d\n", buffer.read_int());
        string username = buffer.read_string();
        printf("Username: %s\n", username.c_str());
        this->username = username;
        //DTLS Not Supported
        printf("Last Nonce Received: %d\n", buffer.read_unsigned_int());
        printf("Current Language: %d\n", buffer.read_unsigned_int());
        printf("Chat Mode: %d\n", buffer.read_byte());
        PlatformSpecificData data;
        data.deserialize(buffer);
        buffer.read_string();
        buffer.read_unsigned_int();
        cout << endl;
    }

    void process_packet(Connection &connection) override {
        connection.setClientName(this->username);
        cout << "Connection name set to " << connection.getClientName() << endl;
        cout << "Hello packet from: " << *connection.getEndpoint() << endl;

        AcknowledgementPacket ackPacket(this->nonce);
        connection.sendPacket(*ackPacket.serialize());
    }
};

#endif //HELLO_PACKET_HPP
