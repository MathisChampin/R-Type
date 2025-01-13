#include "Server.hpp"
#include "Registry.hpp"
#include "ClockManager.hpp"


namespace NmpServer
{
    Server::Server() : 
        _running(false),
        _io_context(),
        _socketRead(_io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 8080)),
        _socketSend(_io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 8081)),
        _ptp(*this),
        _parser("../../server/configFile/test.json")
    {
        _bufferAsio.fill(0);
        _parser.parseConfig();
        _ptp.loadEnnemiesFromconfig(_parser.getVector());
    }

    Server::~Server()
    {

    }

    void Server::run()
    {
        _running = true;
        _io_context.run();

        std::thread systemThread(&Server::threadSystem, this);
        std::thread shootEnnemiesThread(&Server::threadShootEnnemies, this);
        std::thread inputThread(&Server::threadInput, this);
        std::thread handleInputThread(&Server::threaEvalInput, this);

        notifyShoot();

        inputThread.join();
        systemThread.join();
        handleInputThread.join();
        shootEnnemiesThread.join();
    }

    void Server::copyEcs()
    {
        auto &ecs = _ptp.getECS();
        _positions = ecs.get_components<component::position>();
        _states = ecs.get_components<component::state>();
        _sizes = ecs.get_components<component::size>();
        _attributes = ecs.get_components<component::attribute>();
        _lifes = ecs.get_components<component::life>();
        _scores = ecs.get_components<component::score>();

    }

    int Server::getId(component::attribute &att)
    {
        int id = 0;

        if (att._type == component::attribute::Player1 ||
            att._type == component::attribute::Player2 ||
            att._type == component::attribute::Player3 ||
            att._type == component::attribute::Player4) {
            id = 1;
            //std::cout << "je t'envoie un player" << std::endl;
            }
        if (att._type == component::attribute::Shoot) {
            std::cout << "je t'envoie un shoot" << std::endl;
            id = 2;
        }
        if (att._type == component::attribute::Ennemies) {
            id = 3;
            std::cout << "je t'envoie un ennemie" << std::endl;
        }
        if (att._type == component::attribute::Ennemies2) {
            std::cout << "je t'envoie un ennemis 2" << std::endl;
            id = 4;
        }
        if (att._type == component::attribute::Ennemies3) {
            std::cout << "je t'envoie un ennemis 3" << std::endl;
            id = 5;
        }
        if (att._type == component::attribute::Ennemies4) {
            std::cout << "je t'envoie un ennemis 4" << std::endl;
            id = 6;
        }
        if (att._type == component::attribute::Ennemies5) {
            std::cout << "je t'envoie un ennemis 5" << std::endl;
            id = 7;
        }
        return id;
    }

    void Server::sendScoreLife(int i)
    {
        auto &l = _lifes[i];
        auto &s = _scores[i];
        auto &att = _attributes[i];

        Packet packet(EVENT::INFO, l.life, s.score);
        if (att._type == component::attribute::Player1) {
            std::cout << "send life player 1" << std::endl;
            send_data(packet, _vecPlayer[0]);
        } else if (att._type == component::attribute::Player2) {
            send_data(packet, _vecPlayer[1]);
        } else if (att._type == component::attribute::Player3) {
            send_data(packet, _vecPlayer[2]);
        } else if (att._type == component::attribute::Player4) {
            send_data(packet, _vecPlayer[3]);
        }
    }

    void Server::send_entity()
    {
        int id = 0;
        //std::cout << "BEGIN SEND ENTITY" << std::endl;
        for (size_t i = 0; i < _states.size() && i < _attributes.size(); i++) {
            auto &st = _states[i];
            auto &att = _attributes[i];
            if (st._stateKey == component::state::stateKey::Alive) {
                id = getId(att);
                auto &pos = _positions[i];
                auto &s = _sizes[i];
                SpriteInfo sprite = {static_cast<int>(i), id, pos.x, pos.y, s.x, s.y};
                Packet packet(EVENT::SPRITE, sprite);
                broadcast(packet);
            }
            if ((st._stateKey == component::state::stateKey::Alive || st._stateKey == component::state::stateKey::Lose) &&
                (att._type == component::attribute::Player1 || 
                 att._type == component::attribute::Player2 || 
                 att._type == component::attribute::Player3 || 
                 att._type == component::attribute::Player4)) {
                sendScoreLife(i);
            }
        }
        Packet packet(EVENT::EOI);
            broadcast(packet);
        //std::cout << "END SEND ENTITY" << std::endl;
    }

    void Server::notifyShoot()
    {
        ClockManager clock;
        _shootReady = false;

        clock.start();
        while (1) {
            //std::cout << "time elapsed: " << clock.elapsedSeconds() << std::endl;
            if (clock.elapsedSeconds() >= 5.0) {
                //std::cout << "Notify shoot" << std::endl;
                _shootReady = true;
                _cvShoot.notify_one();
                clock.start();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }

    }

    bool Server::check_level(registry &_ecs)
    {
        auto &att = _ecs.get_components<component::attribute>();
        auto &st = _ecs.get_components<component::state>();

        for (size_t i = 0; i < att.size(); i++) {
            if ((att[i]._type == component::attribute::Ennemies ||
            att[i]._type == component::attribute::Ennemies2 ||
            att[i]._type == component::attribute::Ennemies3 ||
            att[i]._type == component::attribute::Ennemies4 ||
            att[i]._type == component::attribute::Ennemies5) && st[i]._stateKey == component::state::Alive)
                return true;
        }
        return false;
    }

    void Server::threadInput()
    {
        while (true) {
            this->get_data();
        }
    }

    void Server::threaEvalInput()
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
            if (packet.getOpCode() == EVENT::JOIN)
                _vecPlayer.push_back(_copy_endpoint);
            {
                std::unique_lock<std::mutex> lock(_ecsMutex);
                _ptp.fillPacket(packet);
                _ptp.executeOpCode();
            }
            //lock player mutex
        }
    }

    void Server::threadSystem()
    {
        System sys;
        const auto frameDuration = std::chrono::milliseconds(40);

        while (_running) {
            {
                std::lock_guard<std::mutex> lock(_ecsMutex);
                auto &ecs = _ptp.getECS();
                sys.collision_system(ecs);
                sys.position_system(ecs);
                sys.lose_system(ecs);
                copyEcs();

                // if (!check_level(ecs)) {
                //     sys.kill_system(ecs);
                //     _ptp.clearPlayer();
                //     _parser.loadNewLevel("../../server/configFile/level2.json");
                //     _ptp.loadEnnemiesFromconfig(_parser.getVector());
                // }
            }
            send_entity();
            std::this_thread::sleep_for(frameDuration);
        }
    }

    void Server::threadShootEnnemies()
    {
        System sys;

        while (true) {
            std::unique_lock<std::mutex> lock(_ecsMutex);
            _cvShoot.wait(lock, [this] { return _shootReady; });
            auto &ecs = _ptp.getECS();
            sys.shoot_system_ennemies(ecs);
            _shootReady = false;
            //std::cout << "has shoot" << std::endl;
        }
    }

    void Server::send_data(Packet &packet, asio::ip::udp::endpoint endpoint)
    {
        // std::cout << "send packet" << std::endl;

        // std::cout << "Sending to remote endpoint: " 
        //           << endpoint.address().to_string() << ":"
        //           << endpoint.port() << std::endl;

        _binary.serialize(packet, _bufferSerialize);
        // for (auto elem: _bufferSerialize) {
        //     std::cout << "elem: " << elem << std::endl;
        // }
        _socketSend.send_to(asio::buffer(_bufferSerialize), endpoint);
        _bufferSerialize.clear();
    }

    void Server::get_data() 
    {
        std::vector<int> rawData;
        std::error_code ignored_error;

        _socketRead.non_blocking(true);

        std::size_t bytes = 0;
        try {
            bytes = _socketRead.receive_from(asio::buffer(_bufferAsio), _remote_endpoint, 0, ignored_error);

            if (bytes > 0) {
                // std::cout << "Received data from remote endpoint: " 
                //           << _remote_endpoint.address().to_string() << ":"
                //           << _remote_endpoint.port() << std::endl;

                // std::cout << "bytes: " << bytes << std::endl;

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


    void Server::extract_bytes(std::size_t &bytes, std::vector<int> &vec)
    {
        for (std::size_t i = 0; i < bytes / sizeof(int); i++) {
            int val = _bufferAsio[i];
            vec.push_back(val);
        }

        _bufferAsio.fill(0);
    }

    asio::ip::udp::endpoint Server::getLastEndpoint() const
    {
        return _copy_endpoint;
    }

    void Server::broadcast(Packet &packet)
    {
        //auto &_vecPlayer = _ptp.get_vector();
        for (const auto &endpoint : _vecPlayer) {
            send_data(packet, endpoint);
        }
    }
}