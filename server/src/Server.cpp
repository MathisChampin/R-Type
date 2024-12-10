#include "Server.hpp"
#include "Registry.hpp"

namespace NmpServer
{
    Server::Server() : _io_context(),
        _socket(_io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 8080)), _ptp(*this)
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

    void Server::send_data(Packet &packet, const asio::ip::udp::endpoint &client_endpoint)
    {
        std::lock_guard<std::mutex> lock(_socket_mutex);

        std::shared_ptr<Packet> shared_packet = std::make_shared<Packet>(packet);
        _binary.serialize(packet, _bufferSerialize);

        _socket.async_send_to(
            asio::buffer(_bufferSerialize), client_endpoint,
            [this, shared_packet](const std::error_code& error, std::size_t bytes_transferred)
            {
                this->handle_send_data(error, bytes_transferred);
            });

        std::cout << "SERVER Message envoyé à " << client_endpoint << std::endl;
    }

    void Server::handle_send_data(const std::error_code& error, std::size_t bytes)
    {
        std::cout << "MA MERE" << std::endl;
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
        std::lock_guard<std::mutex> lock(_socket_mutex);

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

            std::string client_key = _remote_endpoint.address().to_string() + ":" + std::to_string(_remote_endpoint.port());
            {
                std::lock_guard<std::mutex> lock(_socket_mutex);
                _clients[client_key] = _remote_endpoint;
            }

            for (std::size_t i = 0; i < bytes / sizeof(uint32_t); ++i) {
                uint32_t val = reinterpret_cast<uint32_t*>(_bufferAsio.data())[i];
                test.push_back(val);
            }
            _bufferAsio.fill(0);

            NmpServer::Packet packet = _binary.deserialize(test);
            std::cout << "Message byte: " << bytes << std::endl;
            //call protocol handler
            _ptp.fillPacket(packet);
            _ptp.executeOpCode();
            std::cout << "END HANDLE GET DATA\n" << std::endl;
            this->get_data();
        }
        else
        {
            std::cerr << "Error receiving data: " << error.message() << std::endl;
        }
    }

    void Server::broadcast(Packet &packet)
    {
        for (const auto& [key, client_endpoint] : _clients)
        {
            std::cout << "key: " << key << std::endl;
            send_data(packet, client_endpoint);
        }
    }

    asio::ip::udp::endpoint Server::getEndpoint() const
    {
        return _remote_endpoint;
    }

    std::unordered_map<std::string, asio::ip::udp::endpoint> Server::getClient() const
    {
        return _clients;
    }
}