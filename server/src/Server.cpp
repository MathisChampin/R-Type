#include "Server.hpp"

namespace NmpServer
{
    Server::Server() : _io_context(),
        _socket(_io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 8080))
    {
        _bufferAsio.fill(0);
        std::cout << "Server listening on port 8080" << std::endl;
    }

    void Server::run()
    {
        this->get_data();
        _io_context.run();
        std::cout << "Server is running on port 8080..." << std::endl;
    }

    void Server::send_data(Packet &packet) //send Packet
    {
        std::shared_ptr<Packet> shared_packet = std::make_shared<Packet>(packet);

        _binary.serialize(packet, _bufferSerialize);
        _socket.async_send_to(asio::buffer(_bufferSerialize), _remote_endpoint,
            [this, shared_packet](const std::error_code& error, std::size_t bytes_transferred)
            {
                this->handle_send_data(error, bytes_transferred);
            });

        std::cout << "SERVER Message envoyé : " << std::endl;
    }

    void Server::handle_send_data(const std::error_code& error, std::size_t bytes)
    {
        if (!error)
        {
            std::cout << "Envoi réussi (" << bytes << " octets). \n\n" << std::endl;
            _binary.clearBuffer(_bufferSerialize);
        }
        else
        {
            std::cerr << "Erreur lors de l'envoi : " << error.message() << std::endl;
        }
    }

    void Server::get_data()
    {
        _socket.async_receive_from(
            asio::buffer(_bufferAsio), _remote_endpoint,
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
            std::cout << "START HANDLE GET DATA" << std::endl;
            std::vector<uint32_t> test;

            for (std::size_t i = 0; i < bytes / sizeof(uint32_t); ++i) {
                uint32_t val = reinterpret_cast<uint32_t*>(_bufferAsio.data())[i];
                test.push_back(val);
            }
            _bufferAsio.fill(0);

            NmpServer::Packet packet = _binary.deserialize(test);
            std::cout << "Message byte: " << bytes << std::endl;
            std::cout << "END HANDLE GET DATA" << std::endl;
            //call protocol handler
            auto direction = packet.getArg();
            if (direction.has_value())
                std::cout << "Direction: ";
            if (direction == DIRECTION::DOWN)
                std::cout << "DOWN" << std::endl;
            else if (direction == DIRECTION::UP)
                std::cout << "UP" << std::endl;
            else if (direction == DIRECTION::LEFT)
                std::cout << "LEFT" << std::endl;
            else if (direction == DIRECTION::RIGHT)
                std::cout << "RIGHT" << std::endl;
            else
                std::cout << "NO DIRECTION" << std::endl;
            this->send_data(packet);
            this->get_data();
        }
        else
        {
            std::cerr << "Error receiving data: " << error.message() << std::endl;
        }
    }
}