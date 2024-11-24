#include "Server.hpp"

int main()
{
    try
    {
        NmpServer::Server server;
        server.run(); // Démarre le serveur
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
