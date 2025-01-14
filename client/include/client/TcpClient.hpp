#ifndef TCP_CLIENT_HPP
#define TCP_CLIENT_HPP

#include <asio.hpp>
#include <iostream>
#include <optional>
#include <vector>

namespace NmpClient {

class TcpClient {
public:
    TcpClient(const std::string& host, const std::string& port);
    void connect();
    void send(const std::string& message);
    std::optional<std::string> receive();

private:
    asio::io_context _io_context;
    asio::ip::tcp::socket _socket;
    asio::ip::tcp::resolver _resolver;
};

} // namespace NmpClient

#endif // TCP_CLIENT_HPP