#include "LobbyServerTCP.hpp"
#include <iostream>
#include <algorithm>
#include <sstream>

LobbyServerTCP::LobbyServerTCP(asio::io_context& ioContext, int port)
    : acceptor_(ioContext) {
    acceptor_.open(asio::ip::tcp::v4());
    acceptor_.set_option(asio::ip::tcp::acceptor::reuse_address(true));
    acceptor_.bind(asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port));
    acceptor_.listen();
    std::cout << "TCP server started on port " << port << std::endl;
}

void LobbyServerTCP::startAccepting() {
    acceptConnection();
}

void LobbyServerTCP::acceptConnection() {
    auto socket = std::make_shared<asio::ip::tcp::socket>(acceptor_.get_executor());
    acceptor_.async_accept(*socket, [this, socket](std::error_code ec) {
        if (!ec) {
            auto remoteEndpoint = socket->remote_endpoint();
            auto clientIP = remoteEndpoint.address().to_string();
            auto clientPort = remoteEndpoint.port();

            std::cout << "New client connected from IP: " << clientIP << " on port: " << clientPort << std::endl;

            handleClient(socket);
        }
        acceptConnection();
    });
}

void LobbyServerTCP::handleClient(std::shared_ptr<asio::ip::tcp::socket> socket) {
    auto buffer = std::make_shared<std::vector<char>>(1024);

    auto it = clientPlayerIds_.find(socket);
    std::string playerId;

    if (it == clientPlayerIds_.end()) {
        playerId = "player" + std::to_string(playerIdCounter_++);
        clientPlayerIds_[socket] = playerId;
        std::cout << "Assigned playerId: " << playerId << " to new client.\n";
    } else {
        playerId = it->second;
        std::cout << "Reusing playerId: " << playerId << " for existing client.\n";
    }

    auto doRead = [this, socket, buffer, playerId]() {
        socket->async_read_some(asio::buffer(*buffer), 
            [this, socket, buffer, playerId](std::error_code ec, std::size_t length) {
                if (!ec) {
                    if (length > 0) {
                        std::string request(buffer->begin(), buffer->begin() + length);

                        request.erase(std::remove(request.begin(), request.end(), '\n'), request.end());
                        request.erase(std::remove(request.begin(), request.end(), '\r'), request.end());

                        std::cout << "Received request from player " << playerId << ": " << request << std::endl;

                        std::string response = processRequest(request, playerId);

                        asio::async_write(*socket, asio::buffer(response), [socket](std::error_code writeEc, std::size_t) {
                            if (writeEc) {
                                std::cerr << "Error writing response: " << writeEc.message() << std::endl;
                            }
                        });
                    }

                    this->handleClient(socket);
                } else if (ec == asio::error::eof) {
                    std::cout << "Client disconnected: " << playerId << std::endl;

                    leaveLobby(playerId);
                    clientPlayerIds_.erase(socket);
                } else {
                    std::cerr << "Error reading request: " << ec.message() << std::endl;
                }
            });
    };

    doRead();
}

std::string LobbyServerTCP::processRequest(const std::string& request, const std::string& playerId) {
    std::stringstream sstream(request);
    std::string command;
    sstream >> command;

    std::cout << "Processing command: " << command << " from player: " << playerId << std::endl;

    if (command == "LIST_LOBBIES") {
        return listLobbies();
    } else if (command == "CREATE_LOBBY") {
        std::string lobbyId;
        sstream >> lobbyId;
        if (lobbyId.empty()) {
            return "ERROR: Invalid CREATE_LOBBY command. Usage: CREATE_LOBBY <lobbyId>\n";
        }
        if (isPlayerInLobby(playerId)) {
            return "ERROR: You must leave your current lobby before creating a new one.\n";
        }
        return createLobby(lobbyId);
    } else if (command == "JOIN_LOBBY") {
        std::string lobbyId;
        sstream >> lobbyId;
        if (lobbyId.empty()) {
            return "ERROR: Invalid JOIN_LOBBY command. Usage: JOIN_LOBBY <lobbyId>\n";
        }
        if (isPlayerInLobby(playerId)) {
            return "ERROR: You must leave your current lobby before joining another.\n";
        }
        return joinLobby(lobbyId, playerId);
    } else if (command == "LEAVE_LOBBY") {
        return leaveLobby(playerId);
    } else if (command == "SEND_MESSAGE") {
        std::string message;
        std::getline(sstream, message); 
        message = message.substr(1);
        return sendMessage(playerId, message);
    } else if (command == "GET_CHAT_HISTORY") {
        return getChatHistory(playerId);
    } else {
        return "ERROR: Unknown command\n";
    }
}

std::string LobbyServerTCP::listLobbies() {
    if (lobbies_.empty()) {
        return "No lobbies available.\n";
    }

    std::string response = "Lobbies:\n";
    for (const auto& [lobbyId, lobby] : lobbies_) {
        response += lobbyId + " (" + std::to_string(lobby.players.size()) + " players)\n";
    }
    return response;
}

std::string LobbyServerTCP::createLobby(const std::string& lobbyId) {
    if (lobbies_.find(lobbyId) != lobbies_.end()) {
        return "ERROR: Lobby already exists.";
    }
    lobbies_[lobbyId] = Lobby{lobbyId, {}, {}};
    return "Lobby created with ID: " + lobbyId;
}

std::string LobbyServerTCP::joinLobby(const std::string& lobbyId, const std::string& playerId) {
    if (lobbies_.find(lobbyId) == lobbies_.end()) {
        return "ERROR: Lobby does not exist.";
    }
    lobbies_[lobbyId].players.push_back(playerId);
    return "Player " + playerId + " joined lobby " + lobbyId;
}

std::string LobbyServerTCP::leaveLobby(const std::string& playerId) {
    for (auto& [lobbyId, lobby] : lobbies_) {
        auto it = std::find(lobby.players.begin(), lobby.players.end(), playerId);
        if (it != lobby.players.end()) {
            lobby.players.erase(it);
            std::cout << "Player " << playerId << " left lobby " << lobbyId << std::endl;

            if (lobby.players.empty()) {
                lobbies_.erase(lobbyId);
                std::cout << "Lobby " << lobbyId << " deleted as it became empty." << std::endl;
            }

            return "Player " + playerId + " left lobby " + lobbyId + "\n";
        }
    }

    std::cout << "Player " << playerId << " is not in any lobby.\n";
    return "ERROR: You are not in any lobby.\n";
}

bool LobbyServerTCP::isPlayerInLobby(const std::string& playerId) const {
    for (const auto& [lobbyId, lobby] : lobbies_) {
        if (std::find(lobby.players.begin(), lobby.players.end(), playerId) != lobby.players.end()) {
            return true;
        }
    }
    return false;
}

std::string LobbyServerTCP::sendMessage(const std::string& playerId, const std::string& message) {
    std::string lobbyId = "";
    for (const auto& [lid, lobby] : lobbies_) {
        if (std::find(lobby.players.begin(), lobby.players.end(), playerId) != lobby.players.end()) {
            lobbyId = lid;
            break;
        }
    }

    if (lobbyId.empty()) {
        return "ERROR: You are not in any lobby.\n";
    }

    std::string fullMessage = playerId + ": " + message;
    lobbies_[lobbyId].chatHistory.push_back(fullMessage);

    for (const auto& player : lobbies_[lobbyId].players) {
        for (auto const& [socket, id] : clientPlayerIds_) {
            if (id == player) {
                asio::async_write(*socket, asio::buffer(fullMessage + "\n"), [](std::error_code ec, std::size_t) {
                    if (ec) {
                        std::cerr << "Error sending message to player: " << ec.message() << std::endl;
                    }
                });
            }
        }
    }

    return "";
}

std::string LobbyServerTCP::getChatHistory(const std::string& playerId) {
    std::string lobbyId = "";
    for (const auto& [lid, lobby] : lobbies_) {
        if (std::find(lobby.players.begin(), lobby.players.end(), playerId) != lobby.players.end()) {
            lobbyId = lid;
            break;
        }
    }

    if (lobbyId.empty()) {
        return "ERROR: You are not in any lobby.\n";
    }

    std::string chatHistoryStr = "Chat History:\n";
    for (const auto& message : lobbies_[lobbyId].chatHistory) {
        chatHistoryStr += message + "\n";
    }

    return chatHistoryStr;
}