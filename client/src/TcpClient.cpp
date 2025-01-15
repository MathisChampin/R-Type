#include "../include/client/TcpClient.hpp"

namespace NmpClient {

TcpClient::TcpClient(const std::string& host, const std::string& port)
    : _socket(_io_context), _resolver(_io_context) {
    auto endpoints = _resolver.resolve(host, port);
    asio::connect(_socket, endpoints);
    std::cout << "Connecté au serveur TCP " << host << ":" << port << std::endl;
}

void TcpClient::send(const std::string& message) {
    asio::write(_socket, asio::buffer(message));
    std::cout << "Message envoyé : " << message << std::endl;
}

std::optional<std::string> TcpClient::receive() {
    try {
        std::vector<char> buffer(1024);
        size_t length = _socket.read_some(asio::buffer(buffer));
        return std::string(buffer.begin(), buffer.begin() + length);
    } catch (const std::exception& e) {
        std::cerr << "Erreur lors de la réception : " << e.what() << std::endl;
        return std::nullopt;
    }
}

} // namespace NmpClient