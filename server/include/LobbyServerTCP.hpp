#pragma once

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <asio.hpp>

struct Lobby {
    std::string id;
    std::vector<std::string> players;
    std::vector<std::string> chatHistory;
    std::string creatorIP; // IP address of the creator
};

class LobbyServerTCP {
public:
    LobbyServerTCP(asio::io_context& ioContext, int port);
    void startAccepting();

private:
    asio::ip::tcp::acceptor acceptor_;
    std::map<std::string, Lobby> lobbies_;

    std::unordered_map<std::shared_ptr<asio::ip::tcp::socket>, std::string> clientPlayerIds_;
    int playerIdCounter_ = 1;

    void acceptConnection();
    void handleClient(std::shared_ptr<asio::ip::tcp::socket> socket, const std::string& clientIP);

    std::string processRequest(const std::string& request, const std::string& playerId, const std::string& clientIP);
    std::string listLobbies();
    std::string createLobby(const std::string& lobbyId, const std::string& creatorIP);
    std::string joinLobby(const std::string& lobbyId, const std::string& playerId);
    std::string leaveLobby(const std::string& playerId);

    std::string sendMessage(const std::string& playerId, const std::string& message);
    std::string getChatHistory(const std::string& playerId);
    std::string getUdpInfo(const std::string& lobbyId);

    bool isPlayerInLobby(const std::string& playerId) const;
};