#pragma once

#include "IClient.hpp"
#include "ClientBinary.hpp"
#include <iostream>
#include <asio.hpp>

namespace NmpClient {
    class Client : public IClient {
        public:
            Client();

            void send_input(Packet &packet) override;
            Packet get_data() override;
            std::size_t get_id() const;

        private:
            void evalResJoin(Packet &packet);

            std::size_t _id;
            asio::io_context _io_context;
            asio::ip::udp::resolver _resolver;
            asio::ip::udp::endpoint _receiver_endpoint;
            asio::ip::udp::socket _socket_Read;
            asio::ip::udp::socket _socket_Send;
            std::vector<uint32_t> _bufferSerialize;
            std::array<uint32_t, 256> _bufferAsio;
            NmpBinary::Binary _binary;
    };
}