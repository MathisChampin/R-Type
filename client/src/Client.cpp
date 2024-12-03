#include "Client.hpp"

namespace NmpClient 
{
    Client::Client() : _resolver(_io_context), _socket(_io_context)
    {
        asio::ip::udp::resolver::results_type endpoints =
            _resolver.resolve(asio::ip::udp::v4(), "127.0.0.1", "8080");
        _receiver_endpoint = *endpoints.begin();

        _socket.open(asio::ip::udp::v4());
        std::cout << "client bind to server 8080" << std::endl;
    }

    void Client::get_data()
    {
        asio::ip::udp::endpoint clientEndpoint;
        std::vector<uint32_t> test;
        
        std::size_t bytes = _socket.receive_from(asio::buffer(_bufferAsio), clientEndpoint);
        for (std::size_t i = 0; i < bytes / sizeof(uint32_t); ++i) {
            uint32_t val = reinterpret_cast<uint32_t*>(_bufferAsio.data())[i];
            test.push_back(val);
        }
        std::string res = _binary.deserialize(test);
        std::cout << res << std::endl;
        _bufferAsio.fill(0);
    }

    void Client::send_input()
    {
        _binary.serialize("1/2/4/9", _bufferSerialize);
        
        _socket.send_to(asio::buffer(_bufferSerialize), _receiver_endpoint);
        _binary.clearBuffer(_bufferSerialize);
        std::cout << "client send input" << std::endl;
    }
}