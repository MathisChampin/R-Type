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
        // NmpServer::Parser parser("../../server/configFile/level1.json");
        // parser.parseConfig();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}