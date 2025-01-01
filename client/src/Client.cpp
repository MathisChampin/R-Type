#include "../include/client/Client.hpp"
#include "../include/client/ClientPacket.hpp"

namespace NmpClient
{
    Client::Client() : _resolver(_io_context), _socket(_io_context)
    {
        asio::ip::udp::resolver::results_type endpoints =
            _resolver.resolve(asio::ip::udp::v4(), "127.0.0.1", "8080");
        _receiver_endpoint = *endpoints.begin();
        _socket.open(asio::ip::udp::v4());
        std::cout << "client bind to server 8080" << std::endl;

        Packet packetJoin(42, EVENT::JOIN);
        this->send_input(packetJoin);
        std::optional<Packet> resJoin;
        while (!resJoin.has_value())
        {
            std::cout << "waiting for join response" << std::endl;
            resJoin = this->get_data();
        }
        evalResJoin(resJoin.value());
        std::cout << "id client: " << _id << std::endl;
    }

    std::optional<Packet> Client::get_data()
    {
        asio::ip::udp::endpoint clientEndpoint;
        std::vector<uint32_t> test;
        std::error_code ignored_error;

        // Mise en mode non-bloquant
        _socket.non_blocking(true);

        std::size_t bytes = 0;
        try
        {
            // Tentative de réception des données, sans blocage
            bytes = _socket.receive_from(asio::buffer(_bufferAsio), clientEndpoint, 0, ignored_error);

            // Si des données ont été reçues
            if (bytes > 0)
            {
                // Extraire les octets reçus dans le vecteur test
                for (std::size_t i = 0; i < bytes / sizeof(uint32_t); ++i)
                {
                    uint32_t val = reinterpret_cast<uint32_t *>(_bufferAsio.data())[i];
                    test.push_back(val);
                }

                // Désérialiser les données en un paquet
                NmpClient::Packet packet = _binary.deserialize(test);
                _bufferAsio.fill(0); // Réinitialisation du buffer

                // Retourner le paquet encapsulé dans un std::optional
                return packet;
            }
            else
            {
                // Si aucune donnée n'a été reçue, retourner std::nullopt
                return std::nullopt;
            }
        }
        catch (const std::system_error &e)
        {
            std::cout << "Error while receiving data: " << e.what() << std::endl;
            return std::nullopt;
        }
        return std::nullopt;
    }

    void Client::send_input(Packet &packet)
    {
        _binary.serialize(packet, _bufferSerialize);

        _socket.send_to(asio::buffer(_bufferSerialize), _receiver_endpoint);
        _binary.clearBuffer(_bufferSerialize);
        std::cout << "client send input" << std::endl;
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