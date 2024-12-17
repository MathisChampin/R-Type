#include "Server.hpp"
#include "Registry.hpp"

namespace NmpServer
{
    Server::Server() : 
        _running(false),
        _io_context(),
        _socketRead(_io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 8080)),
        _socketSend(_io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 8081)),
        _ptp(*this)
    {
        _bufferAsio.fill(0);
    }

    Server::~Server() {
        stopSystemThread();
    }

    void Server::run()
    {
        _running = true;
        startSystemThread();
        _io_context.run();

        std::thread inputThread(&Server::threadInput, this);
        std::thread ecsThread(&Server::threadEcs, this);

        inputThread.join();
        ecsThread.join();
        _systemThread.join();
    }

    void Server::startSystemThread()
    {
        _systemThread = std::thread(&Server::systemLoop, this);

    }

    void Server::stopSystemThread() {
        _running = false;
        if (_systemThread.joinable()) {
            _systemThread.join();
        }
    }

    void Server::systemLoop() {
    System sys;
    const auto frameDuration = std::chrono::milliseconds(20);
    const auto shootCooldown = std::chrono::seconds(5);
    auto lastShootTime = std::chrono::steady_clock::now();

    while (_running) {
        auto startTime = std::chrono::steady_clock::now();

        {
            std::lock_guard<std::mutex> lock(_ecsMutex);
            auto &ecs = _ptp.getECS();
            if (std::chrono::steady_clock::now() - lastShootTime >= shootCooldown) {
                sys.shoot_system_ennemies(ecs);
                lastShootTime = std::chrono::steady_clock::now();
            }
            //sys.shoot_system_player(ecs);
            sys.collision_system(ecs);
            sys.kill_system(ecs);
            sys.position_system(ecs);
            send_entity(ecs);
        }

        // Calcul de la durée écoulée et ajustement du sommeil
        auto elapsedTime = std::chrono::steady_clock::now() - startTime;
        if (elapsedTime < frameDuration) {
            std::this_thread::sleep_for(frameDuration - elapsedTime);
        }
    }
}


    uint32_t Server::getId(component::attribute &att)
    {
        uint32_t id = 0;

        if (att._type == component::attribute::Player1 ||
            att._type == component::attribute::Player2 ||
            att._type == component::attribute::Player3 ||
            att._type == component::attribute::Player4) {
            id = 1;
            std::cout << "je t'envoie un player" << std::endl;
            }
        if (att._type == component::attribute::Ennemies) {
            id = 2;
            std::cout << "je t'envoie un ennemie" << std::endl;
        }
        if (att._type == component::attribute::Shoot) {
            std::cout << "je t'envoie un shoot" << std::endl;
            id = 3;
        }
        return id;
    }

    void Server::send_entity(registry &_ecs)
    {
        sparse_array<component::position> &positions = _ecs.get_components<component::position>();
        sparse_array<component::state> &states = _ecs.get_components<component::state>();
        sparse_array<component::size> &sizes = _ecs.get_components<component::size>();
        sparse_array<component::attribute> &attributes = _ecs.get_components<component::attribute>();
        int id = 0;

        for (size_t i = 0; i < states.size() && i < attributes.size(); i++) {
            auto &st = states[i];
            auto &att = attributes[i];
            if (st._stateKey == component::state::stateKey::Alive) {
                id = getId(att);
                auto &pos = positions[i];
                auto &s = sizes[i];
                std::cout << "id client: "  << i << std::endl;
                SpriteInfo sprite = {static_cast<int>(i), id, pos.x, pos.y, s.x, s.y};
                Packet packet(EVENT::SPRITE, sprite);
                auto &_vecPlayer = _ptp.get_vector();
                for (const auto &[entity, endpoint] : _vecPlayer) {
                    send_data(packet, endpoint);
                }
            }
        }
    }

    void Server::threadInput()
    {
        while (true) {
            get_data();
            //std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    void Server::threadEcs()
    {
        while (true) {
            Packet packet;
            {
                std::unique_lock<std::mutex> lock(_queueMutex);
                if (!_running)
                    return;
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