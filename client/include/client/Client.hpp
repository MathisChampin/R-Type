#pragma once

#include "IClient.hpp"
#include "ClientBinary.hpp"
#include <iostream>
#include <asio.hpp>

namespace NmpClient
{
    class Client : public IClient
    {
    public:
        Client();

        /**
         * @brief Sends the input packet to the server.
         *
         * @param packet The packet containing the input data to be sent.
         */
        void send_input(Packet &packet) override;
        std::optional<Packet> get_data() override;
        std::size_t get_id() const;

        std::size_t _id;

    private:
        void evalResJoin(Packet &packet);

        asio::io_context _io_context;
        asio::ip::udp::resolver _resolver;
        asio::ip::udp::endpoint _receiver_endpoint;
        asio::ip::udp::socket _socket;
        std::vector<uint32_t> _bufferSerialize;
        std::array<uint32_t, 256> _bufferAsio;
        NmpBinary::Binary _binary;
    };
}