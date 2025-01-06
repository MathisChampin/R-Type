#include "Server.hpp"
#include "Parser.hpp"

#include <filesystem>
#include <thread>

int main()
{
    try
    {
        NmpServer::Server server;
        server.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}


