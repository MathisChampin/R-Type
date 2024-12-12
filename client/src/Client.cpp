#include "../include/client/Client.hpp"
#include "../include/client/ClientPacket.hpp"

namespace NmpClient {
    Client::Client() : _resolver(_io_context), _socket_Read(_io_context), _socket_Send(_io_context)
    {
        auto endpoints = _resolver.resolve(asio::ip::udp::v4(), "127.0.0.1", "8080");
        _receiver_endpoint = *endpoints.begin();

        _socket_Read.open(asio::ip::udp::v4());
        _socket_Read.bind(asio::ip::udp::endpoint(asio::ip::udp::v4(), 8081));
        _socket_Send.open(asio::ip::udp::v4());
        _socket_Read.bind(asio::ip::udp::endpoint(asio::ip::udp::v4(), 8080));
        std::cout << "Client ready on ports: Read (8081), Send (8080)" << std::endl;
        Packet packetJoin(42, EVENT::JOIN);
        this->send_input(packetJoin);
        Packet resJoin = this->get_data();
        evalResJoin(resJoin);

        std::cout << "Client ID: " << _id << std::endl;
    }

    Packet Client::get_data()
    {
        asio::ip::udp::endpoint serverEndpoint;
        std::vector<uint32_t> rawData;

        std::size_t bytes = _socket_Read.receive_from(asio::buffer(_bufferAsio), serverEndpoint);
        for (std::size_t i = 0; i < bytes / sizeof(uint32_t); ++i) {
            uint32_t val = reinterpret_cast<uint32_t*>(_bufferAsio.data())[i];
            rawData.push_back(val);
        }

        try {
            Packet packet = _binary.deserialize(rawData);
            _bufferAsio.fill(0);
            return packet;
        } catch (const std::exception& e) {
            std::cerr << "Deserialization error: " << e.what() << std::endl;
            throw;
        }
    }

    void Client::send_input(Packet &packet)
    {
        try {
            _binary.serialize(packet, _bufferSerialize);

            _socket_Send.send_to(asio::buffer(_bufferSerialize), _receiver_endpoint);
            _binary.clearBuffer(_bufferSerialize);

            std::cout << "Packet sent to server" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Serialization or send error: " << e.what() << std::endl;
        }
    }

    void Client::evalResJoin(Packet &packet)
    {
        _id = packet.getId();
    }

    std::size_t Client::get_id() const
    {
        return _id;
    }
}
