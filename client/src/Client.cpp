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
        std::array<char, 128> recv_buf;

        std::cout << "get data from server" << std::endl;
        std::size_t bytes = _socket.receive_from(asio::buffer(recv_buf), clientEndpoint);
        std::cout.write(recv_buf.data(), bytes);

    }

    void Client::send_input()
    {
        std::array<char, 1> send_buf  = {{ 1 }};
        send_buf[0] = 'c';
        _socket.send_to(asio::buffer(send_buf), _receiver_endpoint);
        std::cout << "client send input" << std::endl;
    }
}