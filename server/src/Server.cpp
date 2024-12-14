#include "Server.hpp"
#include "Registry.hpp"

// namespace NmpServer
// {
    // Server::Server() : _io_context(),
    //     _socket(_io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 8080)), _ptp(*this)
    // {
    //     _bufferAsio.fill(0);
    //     std::cout << "Server listening on port 8080" << std::endl;
    // }

    // void Server::run()
    // {
    //     this->get_data();
    //     _io_context.run();
    //     std::cout << "Server is running on port 8080..." << std::endl;
    // }

    // void Server::send_data(Packet &packet)
    // {
    //     std::shared_ptr<Packet> shared_packet = std::make_shared<Packet>(packet);
    //     _binary.serialize(packet, _bufferSerialize);

    //     _socket.async_send_to(
    //         asio::buffer(_bufferSerialize), _remote_endpoint,
    //         [this, shared_packet](const std::error_code& error, std::size_t bytes_transferred)
    //         {
    //             this->handle_send_data(error, bytes_transferred);
    //         });

    //     std::cout << "SERVER Message envoyé à " << _remote_endpoint << std::endl;
    // }

    // void Server::handle_send_data(const std::error_code& error, std::size_t bytes)
    // {
    //     std::cout << "MA MERE" << std::endl;
    //     if (!error)
    //     {
    //         std::cout << "Envoi réussi (" << bytes << " octets). \n\n" << std::endl;
    //         _binary.clearBuffer(_bufferSerialize);
    //     }
    //     else
    //     {
    //         std::cerr << "Erreur lors de l'envoi : " << error.message() << std::endl;
    //     }
    // }

    // void NmpServer::Server::get_data()
    // {
    //     _socketRead.async_receive_from(
    //         asio::buffer(_bufferAsio), _remote_endpoint,
    //         [this](const std::error_code& error, std::size_t bytes_transferred)
    //         {
    //             this->handle_get_data(error, bytes_transferred);
    //         });

    //     std::cout << "Waiting for data..." << std::endl;
    // }


    // void NmpServer::Server::handle_get_data(const std::error_code& error, std::size_t bytes)
    // {
    //     if (!error)
    //     {
    //         std::cout << "START HANDLE GET DATA" << std::endl;
    //         std::vector<uint32_t> test;

    //         for (std::size_t i = 0; i < bytes / sizeof(uint32_t); ++i) {
    //             uint32_t val = reinterpret_cast<uint32_t*>(_bufferAsio.data())[i];
    //             test.push_back(val);
    //         }
    //         _bufferAsio.fill(0);

    //         NmpServer::Packet packet = _binary.deserialize(test);
    //         //this->add_to_queue(packet);
    //         std::cout << "Message byte: " << bytes << std::endl;
    //         // //call protocol handler
    //         // _ptp.fillPacket(packet);
    //         // //_ptp.executeOpCode();
    //         // std::cout << "END HANDLE GET DATA\n" << std::endl;
    //         this->get_data();
    //     }
    //     else
    //     {
    //         std::cerr << "Error receiving data: " << error.message() << std::endl;
    //     }
    // }

    // void Server::add_to_queue(Packet &packet)
    // {
    //     _queueInput.push(packet);
    // }
//}

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
            }

            _ptp.fillPacket(packet);
            _ptp.executeOpCode();
        }
    }

    void Server::send_data(Packet &packet)
    {
        std::cout << "send packet" << std::endl;

        std::cout << "Sending to remote endpoint: " 
                  << _remote_endpoint.address().to_string() << ":"
                  << _remote_endpoint.port() << std::endl;

        _binary.serialize(packet, _bufferSerialize);
        for (auto elem: _bufferSerialize) {
            std::cout << "elem: " << elem << std::endl;
        }
        _socketSend.send_to(asio::buffer(_bufferSerialize), _remote_endpoint);
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
            } else {
                std::cout << "No data available, continuing..." << std::endl;
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
}