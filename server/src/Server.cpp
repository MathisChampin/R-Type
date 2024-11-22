#include "Server.hpp"

namespace NmpServer
{
    Server::Server()
    {
        std::cout << "CONSTRUCTOR SERVER" << std::endl;
    }

    void Server::run()
    {
        std::cout << "run" << std::endl;
    }

    void Server::send_data()
    {
        std::cout << "send_data" << std::endl;
    }

    void Server::get_data()
    {
        std::cout << "get_data" << std::endl;
    }
}