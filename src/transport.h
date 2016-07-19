#pragma once

namespace MRPC {
    class Node;
    class Transport {
    public:
        Node *node;
        bool poll();
        void close();
        virtual void send(Json::Object&) = 0;
        virtual Json::Value recv() = 0;
    };
    struct UDPEndpoint {
        IPAddress ip;
        uint16_t port;
    };
    class UDPTransport : public Transport {
    public:
        UDPTransport();
        UDPTransport(int local_port);
        void send(Json::Object&);
        Json::Value recv();
        struct UDPEndpoint *guid_lookup(const char *hex);
    private:
        struct UDPEndpoint broadcast;
        AMap<struct UDPEndpoint> known_guids;
        WiFiUDP udp;
        uint16_t remote_port;
    };
}