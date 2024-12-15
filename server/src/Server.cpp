#include "Server.hpp"
#include "Registry.hpp"

namespace NmpServer
{
    Server::Server() : _io_context(),
        _socketRead(_io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 8080)),
        _socketSend(_io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 8081)),
        _ptp(*this)
    {
        _bufferAsio.fill(0);
    }

    void Server::run()
    {
        _io_context.run();

        std::thread inputThread(&Server::threadInput, this);
        std::thread ecsThread(&Server::threadEcs, this);

        inputThread.join();
        ecsThread.join();
    }

    void Server::threadInput()
    {
        while (true) {
            get_data();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    void Server::threadEcs()
    {
        while (true) {
            Packet packet;
            {
                std::unique_lock<std::mutex> lock(_queueMutex);
                _cv.wait(lock, [this] { return !_queue.empty(); });
                packet = _queue.front();
                _queue.pop();
                _copy_endpoint = _remote_endpoint;
            }

            _ptp.fillPacket(packet);
            _ptp.executeOpCode();

        }
    }

    void Server::send_data(Packet &packet, asio::ip::udp::endpoint endpoint)
    {
        std::cout << "send packet" << std::endl;

        std::cout << "Sending to remote endpoint: " 
                  << endpoint.address().to_string() << ":"
                  << endpoint.port() << std::endl;

        _binary.serialize(packet, _bufferSerialize);
        for (auto elem: _bufferSerialize) {
            std::cout << "elem: " << elem << std::endl;
        }
        _socketSend.send_to(asio::buffer(_bufferSerialize), endpoint);
        _bufferSerialize.clear();
    }

    void Server::get_data() 
    {
        std::vector<uint32_t> rawData;
        std::error_code ignored_error;

        _socketRead.non_blocking(true);

        std::size_t bytes = 0;
        try {
            bytes = _socketRead.receive_from(asio::buffer(_bufferAsio), _remote_endpoint, 0, ignored_error);

            if (bytes > 0) {
                std::cout << "Received data from remote endpoint: " 
                          << _remote_endpoint.address().to_string() << ":"
                          << _remote_endpoint.port() << std::endl;

                std::cout << "bytes: " << bytes << std::endl;

                extract_bytes(bytes, rawData);
                NmpServer::Packet packet = _binary.deserialize(rawData);

                std::lock_guard<std::mutex> lock(_queueMutex);
                _queue.push(packet);
                _cv.notify_one();
            }
        } catch (const std::system_error& e) {
            std::cout << "Error while receiving data: " << e.what() << std::endl;
        }

        _socketRead.non_blocking(false);
    }


    void Server::extract_bytes(std::size_t &bytes, std::vector<uint32_t> &vec)
    {
        for (std::size_t i = 0; i < bytes / sizeof(uint32_t); i++) {
            uint32_t val = _bufferAsio[i];
            vec.push_back(val);
        }

        _bufferAsio.fill(0);
    }

    asio::ip::udp::endpoint Server::getLastEndpoint() const
    {
        return _copy_endpoint;
    }
}