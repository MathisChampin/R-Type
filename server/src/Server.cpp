#include "Server.hpp"

namespace NmpServer
{
    Server::Server() : _io_context(),
        _socket(_io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 8080))
    {
        std::cout << "Server listening on port 8080" << std::endl;
    }

    void Server::run()
    {
        this->get_data();
        _io_context.run();
        std::cout << "Server is running on port 8080..." << std::endl;
    }

    void Server::send_data()
    {
        std::cout << "send_data" << std::endl;
    }

    void Server::get_data()
    {
        _socket.async_receive_from(
            asio::buffer(_recv_buffer), _remote_endpoint,
            [this](const std::error_code& error, std::size_t bytes_transferred)
            {
                this->handle_get_data(error, bytes_transferred);
            });

        std::cout << "Waiting for data..." << std::endl;
    }

    void Server::handle_get_data(const std::error_code& error, std::size_t bytes)
    {
        if (!error)
        {
            std::string data(_recv_buffer.data(), bytes);
            std::cout << "Message received: " << data << std::endl;

            this->get_data();
        }
        else
        {
            std::cerr << "Error receiving data: " << error.message() << std::endl;
        }
    }
}