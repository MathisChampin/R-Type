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

    void Server::send_data(const std::string& message)
    {
        std::shared_ptr<std::string> shared_message = std::make_shared<std::string>(message);

        _binary.serialize(*shared_message, _buffer);
        _socket.async_send_to(asio::buffer(_buffer), _remote_endpoint,
            [this, shared_message](const std::error_code& error, std::size_t bytes_transferred)
            {
                this->handle_send_data(error, bytes_transferred);
            });

        std::cout << "Message envoyé : " << message << std::endl;
    }

    void Server::handle_send_data(const std::error_code& error, std::size_t bytes)
    {
        if (!error)
        {
            std::cout << "Envoi réussi (" << bytes << " octets)." << std::endl;
        }
        else
        {
            std::cerr << "Erreur lors de l'envoi : " << error.message() << std::endl;
        }
    }

    void Server::get_data()
    {
        _socket.async_receive_from(
            asio::buffer(_test_buffer), _remote_endpoint,
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
            std::vector<uint32_t> test;

            for (std::size_t i = 0; i < bytes / sizeof(uint32_t); ++i) {
                uint32_t val = reinterpret_cast<uint32_t*>(_test_buffer.data())[i];
                test.push_back(val);
            }

            std::string res = _binary.deserialize(test);
            std::cout << res << std::endl;
            this->send_data(res);
            this->get_data();
        }
        else
        {
            std::cerr << "Error receiving data: " << error.message() << std::endl;
        }
    }
}