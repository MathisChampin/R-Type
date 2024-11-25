#include "Server.hpp"

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
