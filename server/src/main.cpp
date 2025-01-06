#include "Server.hpp"
#include "Parser.hpp"

#include <filesystem>
#include <thread>

#include "LobbyServerTCP.hpp"
#include <asio.hpp>

#include "LobbyServerTCP.hpp"
#include <asio.hpp>

int main() {
    try {
        asio::io_context ioContext;
        LobbyServerTCP server(ioContext, 8080); // Démarrer le serveur sur le port 8080
        server.startAccepting();
        ioContext.run(); // Lancer l'exécution du contexte
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
