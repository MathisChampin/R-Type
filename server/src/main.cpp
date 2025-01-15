#include "Server.hpp"
#include "Parser.hpp"
#include "LobbyServerTCP.hpp"

#include <filesystem>
#include <thread>


int main() {
    try {
        asio::io_context io_context;
        LobbyServerTCP server(io_context, 50000);
        server.startAccepting();
        io_context.run();
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
