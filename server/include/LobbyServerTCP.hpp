#pragma once

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

struct Lobby {
    std::string id;
    std::vector<std::string> players;
    std::vector<std::string> chatHistory;
    std::string creatorIP;
    bool joined = false; // Flag to indicate if the lobby has been fully joined
};

class LobbyServerTCP {
public:
    LobbyServerTCP(asio::io_context& ioContext, int port);
    void startAccepting();

private:
    asio::ip::tcp::acceptor acceptor_;
    std::map<std::string, Lobby> lobbies_;
    std::mutex lobbies_mutex_; // Mutex to protect concurrent access to lobbies_

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

    bool isPlayerInLobby(const std::string& playerId) ;

    // Helper functions
    std::string trim(const std::string& str);
    std::string tolower(const std::string& str);
    void printRawBytes(const std::string& str);
    void printLobbies(const std::map<std::string, Lobby>& lobbies);
    std::string getLocalIP();
};