#pragma once

#include "IServer.hpp"
#include <iostream>

namespace NmpServer {
    class Server : public IServer {
        public:
            Server();

            void run() override;
            void send_data() override;
            void get_data() override;
    };
}