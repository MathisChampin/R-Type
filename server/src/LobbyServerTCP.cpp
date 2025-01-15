#include "LobbyServerTCP.hpp"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <thread>
#include <asio/ip/tcp.hpp>
#include <asio/io_context.hpp>

// Helper function to trim whitespace from a string
std::string LobbyServerTCP::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    if (std::string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, (last - first + 1));
}

// Helper function to convert a string to lowercase
std::string LobbyServerTCP::tolower(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// Helper function to print the raw bytes of a string
void LobbyServerTCP::printRawBytes(const std::string& str) {
    std::cout << "Raw bytes: ";
    for (char c : str) {
        std::cout << static_cast<int>(c) << " ";
    }
    std::cout << std::endl;
}

// Helper function to print the contents of the lobbies_ map
void LobbyServerTCP::printLobbies(const std::map<std::string, Lobby>& lobbies)
{
    std::cout << "Current Lobbies:\n";
    for (const auto& pair : lobbies) {
        std::cout << "  Lobby ID: " << pair.first << std::endl;
        std::cout << "    Creator IP: " << pair.second.creatorIP << std::endl;
        std::cout << "    Joined: " << (pair.second.joined ? "true" : "false") << std::endl;
        std::cout << "    Players: ";
        for (const auto& player : pair.second.players) {
            std::cout << player << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Helper function to get the local machine's external IP address
std::string LobbyServerTCP::getLocalIP() {
    try {
        asio::io_context ioContext;
        asio::ip::udp::resolver resolver(ioContext);
        asio::ip::udp::resolver::query query(asio::ip::udp::v4(), "google.com", "");
        auto it = resolver.resolve(query);
        asio::ip::udp::endpoint endpoint = *it;

        asio::ip::udp::socket socket(ioContext);
        socket.open(asio::ip::udp::v4());
        socket.connect(endpoint);
        asio::ip::address localAddress = socket.local_endpoint().address();
        return localAddress.to_string();
    }
    catch (std::exception& e) {
        std::cerr << "Error getting local IP: " << e.what() << std::endl;
        return "";
    }
}

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

            handleClient(socket, clientIP);
        }
        acceptConnection();
    });
}

void LobbyServerTCP::handleClient(std::shared_ptr<asio::ip::tcp::socket> socket, const std::string& clientIP) {
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

    auto doRead = [this, socket, buffer, playerId, clientIP]() {
        socket->async_read_some(asio::buffer(*buffer),
            [this, socket, buffer, playerId, clientIP](std::error_code ec, std::size_t length) {
                if (!ec) {
                    if (length > 0) {
                        std::string request(buffer->begin(), buffer->begin() + length);

                        request.erase(std::remove(request.begin(), request.end(), '\n'), request.end());
                        request.erase(std::remove(request.begin(), request.end(), '\r'), request.end());

                        std::cout << "Received request from player " << playerId << ": " << request << std::endl;

                        std::string response = processRequest(request, playerId, clientIP);

                        asio::async_write(*socket, asio::buffer(response), [socket](std::error_code writeEc, std::size_t) {
                            if (writeEc) {
                                std::cerr << "Error writing response: " << writeEc.message() << std::endl;
                            }
                        });
                    }

                    this->handleClient(socket, clientIP);
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

std::string LobbyServerTCP::processRequest(const std::string& request, const std::string& playerId, const std::string& clientIP) {
    std::stringstream sstream(request);
    std::string command;
    sstream >> command;

    std::cout << "Processing command: " << command << " from player: " << playerId << std::endl;

    if (command == "LIST_LOBBIES") {
        return listLobbies();
    } else if (command == "CREATE_LOBBY") {
        std::string lobbyId;
        sstream >> lobbyId;
        lobbyId = trim(lobbyId);
        std::cout << "CREATE_LOBBY: Lobby ID after trim: '" << lobbyId << "'" << std::endl;
        printRawBytes(lobbyId);
        if (lobbyId.empty()) {
            return "ERROR: Invalid CREATE_LOBBY command. Usage: CREATE_LOBBY <lobbyId>\n";
        }
        if (isPlayerInLobby(playerId)) {
            return "ERROR: You must leave your current lobby before creating a new one.\n";
        }
        return createLobby(lobbyId, clientIP);
    } else if (command == "JOIN_LOBBY") {
        std::string lobbyId;
        sstream >> lobbyId;
        lobbyId = trim(lobbyId);
        std::cout << "JOIN_LOBBY: Lobby ID after trim: '" << lobbyId << "'" << std::endl;
        printRawBytes(lobbyId);
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
        message = trim(message);
        return sendMessage(playerId, message);
    } else if (command == "GET_CHAT_HISTORY") {
        return getChatHistory(playerId);
    } else if (command == "GET_UDP_INFO") {
        std::string lobbyId;
        sstream >> lobbyId;
        lobbyId = trim(lobbyId);
        std::cout << "GET_UDP_INFO: Lobby ID after trim: '" << lobbyId << "'" << std::endl;
        printRawBytes(lobbyId);
        return getUdpInfo(lobbyId);
    }
    else {
        return "ERROR: Unknown command\n";
    }
}

std::string LobbyServerTCP::listLobbies() {
    std::lock_guard<std::mutex> lock(lobbies_mutex_);
    if (lobbies_.empty()) {
        return "No lobbies available.\n";
    }

    std::string response = "Lobbies:\n";
    for (const auto& [lobbyId, lobby] : lobbies_) {
        response += lobbyId + " (" + std::to_string(lobby.players.size()) + " players)\n";
    }
    return response;
}

std::string LobbyServerTCP::createLobby(const std::string& lobbyId, const std::string& creatorIP) {
    std::string lowerLobbyId = tolower(lobbyId);
    std::lock_guard<std::mutex> lock(lobbies_mutex_);

    std::cout << "createLobby: Trying to create lobby with ID: " << lowerLobbyId << std::endl;
    if (lobbies_.find(lowerLobbyId) != lobbies_.end()) {
        return "ERROR: Lobby already exists.\n";
    }

    std::string updatedCreatorIP = creatorIP;
    if (creatorIP == "127.0.0.1") {
        std::cout << "createLobby: Creator IP is localhost (127.0.0.1). Attempting to get external IP.\n";
        updatedCreatorIP = getLocalIP();
        if (updatedCreatorIP.empty()) {
            std::cerr << "createLobby: Failed to determine external IP. Using localhost IP.\n";
            updatedCreatorIP = "127.0.0.1";
        } else {
            std::cout << "createLobby: Updated creator IP to: " << updatedCreatorIP << std::endl;
        }
    }
    lobbies_[lowerLobbyId] = Lobby{lowerLobbyId, {}, {}, updatedCreatorIP};
    std::cout << "Lobby created with ID: " << lowerLobbyId << " by " << updatedCreatorIP << std::endl;
    printLobbies(lobbies_);
    return "Lobby created with ID: " + lowerLobbyId + "\n";
}

std::string LobbyServerTCP::joinLobby(const std::string& lobbyId, const std::string& playerId) {
    std::string lowerLobbyId = tolower(lobbyId);
    std::lock_guard<std::mutex> lock(lobbies_mutex_);
    std::cout << "joinLobby: Trying to join lobby with ID: " << lowerLobbyId << std::endl;
    if (lobbies_.find(lowerLobbyId) == lobbies_.end()) {
        std::cout << "joinLobby: Lobby not found: " << lowerLobbyId << std::endl;
        return "ERROR: Lobby does not exist.\n";
    }
    lobbies_[lowerLobbyId].players.push_back(playerId);
    lobbies_[lowerLobbyId].joined = true;
    std::cout << "joinLobby: Player " << playerId << " added to lobby " << lowerLobbyId << std::endl;
    printLobbies(lobbies_);
    return "Player " + playerId + " joined lobby " + lowerLobbyId + "\n";
}

std::string LobbyServerTCP::leaveLobby(const std::string& playerId) {
    std::lock_guard<std::mutex> lock(lobbies_mutex_);
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

bool LobbyServerTCP::isPlayerInLobby(const std::string& playerId)  {
    std::lock_guard<std::mutex> lock(lobbies_mutex_);
    for (const auto& [lobbyId, lobby] : lobbies_) {
        if (std::find(lobby.players.begin(), lobby.players.end(), playerId) != lobby.players.end()) {
            return true;
        }
    }
    return false;
}

std::string LobbyServerTCP::sendMessage(const std::string& playerId, const std::string& message) {
    std::lock_guard<std::mutex> lock(lobbies_mutex_);
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

    std::string fullMessage = playerId + ": " + message + "\n";
    lobbies_[lobbyId].chatHistory.push_back(fullMessage);

    for (const auto& player : lobbies_[lobbyId].players) {
        for (auto const& [socket, id] : clientPlayerIds_) {
            if (id == player) {
                asio::async_write(*socket, asio::buffer(fullMessage), [](std::error_code ec, std::size_t) {
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
    std::lock_guard<std::mutex> lock(lobbies_mutex_);
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
        chatHistoryStr += message;
    }

    return chatHistoryStr;
}

std::string LobbyServerTCP::getUdpInfo(const std::string& lobbyId) {
    std::string lowerLobbyId = tolower(lobbyId);
    std::lock_guard<std::mutex> lock(lobbies_mutex_);
    std::cout << "getUdpInfo: Request for lobby: " << lowerLobbyId << std::endl;
    printLobbies(lobbies_);

    auto it = lobbies_.find(lowerLobbyId);
    if (it == lobbies_.end()) {
        std::cout << "getUdpInfo: Lobby not found: " << lowerLobbyId << std::endl;
        return "ERROR: Lobby " + lowerLobbyId + " does not exist.\n";
    }

    if (!it->second.joined) {
        std::cout << "getUdpInfo: Lobby not yet fully joined: " << lowerLobbyId << std::endl;
        return "ERROR: Lobby " + lowerLobbyId + " not yet fully joined.\n";
    }

    std::string creatorIP = it->second.creatorIP;
    if (creatorIP.empty()) {
        std::cout << "getUdpInfo: Creator IP not found for lobby: " << lowerLobbyId << std::endl;
        return "ERROR: Creator IP information not available for lobby " + lowerLobbyId + ".\n";
    }

    std::cout << "getUdpInfo: Returning creator IP: " << creatorIP << " for lobby: " << lowerLobbyId << std::endl;
    return creatorIP;
}