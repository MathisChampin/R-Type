#include "Server.hpp"
#include "Registry.hpp"



namespace NmpServer
{
    Server::Server() : 
        _running(false),
        _io_context(),
        _socketRead(_io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 8080)),
        _socketSend(_io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), 8081)),
        _ptp(*this),
        _parser("../../server/configFile/level1.json")
    {
        _bufferAsio.fill(0);
        _prodLevel.generateLevel(2);
        _parser.parseConfig();
        //_ptp.loadEnnemiesFromconfig(_parser.getVector());
        _vecSpawn = _parser.getVector();
    }

    Server::~Server()
    {

    }

    void Server::run()
    {
        _running = true;
        _io_context.run();

        std::thread systemThread(&Server::threadSystem, this);
        std::thread inputThread(&Server::threadInput, this);
        std::thread handleInputThread(&Server::threaEvalInput, this);

        inputThread.join();
        systemThread.join();
        handleInputThread.join();
    }

    void Server::pauseThreads()
    {
        {
            std::lock_guard<std::mutex> lock(_pauseMutex);
            _paused.store(true);
            std::cout << "thread sleep animation can run" << std::endl;
        }
    }

    void Server::resumeThreads()
    {
        {
        std::lock_guard<std::mutex> lock(_pauseMutex);
        _paused.store(false);
        }
        _pauseCv.notify_all();
        std::cout << "thread going" << std::endl;
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
        _levels = ecs.get_components<component::level>();
    }

    int Server::getId(component::attribute &att)
    {
        auto it = _mapSpriteID.find(att._type);
        if (it != _mapSpriteID.end()) {
            return it->second;
        }
        return 0;
    }

    void Server::sendScoreLife(int i)
    {
        auto &l = _lifes[i];
        auto &s = _scores[i];
        auto &att = _attributes[i];
        auto &lvl = _levels[i];
        // std::cout << "lEVEL: " << lvl._levelKey << std::endl;
        Packet packet(EVENT::INFO, l.life, s.score, lvl._levelKey);
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
                 att._type == component::attribute::Player4 )) {
                sendScoreLife(i);
            }
        }
        Packet packet(EVENT::EOI);
            broadcast(packet);
        //std::cout << "END SEND ENTITY" << std::endl;
    }

    bool Server::check_level_player(registry &_ecs)
    {
        auto &att = _ecs.get_components<component::attribute>();
        auto &level = _ecs.get_components<component::level>();

        for (size_t i = 0; i < att.size(); i++) {
            if ((att[i]._type == component::attribute::Player1 ||
            att[i]._type == component::attribute::Player2 ||
            att[i]._type == component::attribute::Player3 ||
            att[i]._type == component::attribute::Player4) && (level[i]._levelKey == component::level::Level3 ||
            level[i]._levelKey == component::level::Level4 || level[i]._levelKey == component::level::Level5 ||
            level[i]._levelKey == component::level::Level6))
                return true;
        }
        return false;
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
            {
                std::unique_lock<std::mutex> lock(_pauseMutex);
                _pauseCv.wait(lock, [this] { return !_paused.load(); });
            }
            this->get_data();
        }
    }

    void Server::threaEvalInput()
    {
        Packet packet;
        while (true) {
            {
                std::unique_lock<std::mutex> lock(_pauseMutex);
                _pauseCv.wait(lock, [this] { return !_paused.load(); });
            }
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
                std::cout << "packet" << std::endl;
                _ptp.fillPacket(packet);
                _ptp.executeOpCode();
            }
        }
    }

    void Server::threadSystem()
    {
        System sys;
        ClockManager clock;
        int difficulty{2};
        clock.start();
        
        auto frameDuration = std::chrono::milliseconds(40);
        while (_running) {
            {
                std::unique_lock<std::mutex> lock(_pauseMutex);
                _pauseCv.wait(lock, [this] { return !_paused.load(); });
            }
            {
                std::lock_guard<std::mutex> lock(_ecsMutex);
                delaySpawn(clock);
                auto &ecs = _ptp.getECS();
                sys.collision_system(ecs);
                sys.position_system(ecs);
                sys.shoot_system_ennemies(ecs);
                sys.lose_system(ecs);
                sys.spawn_power_up_life(ecs);
                sys.collision_power_up(ecs);
                sys.level_system(ecs);
                copyEcs();

                if (!check_level(ecs) && isLevelReady()) {
                    difficulty += 3;
                    clock.start();
                    std::cout << "reset: " << clock.elapsedSeconds() << std::endl;

                    _ptp.clearPlayer();
                    std::cout << "new level" << std::endl;

                    _prodLevel.generateLevel(difficulty);
                    _parser.loadNewLevel("../../server/configFile/level1.json");
                    _vecSpawn = _parser.getVector();

                    pauseThreads();
                    std::this_thread::sleep_for(std::chrono::seconds(3));
                    resumeThreads();

                    continue;
                }
            }
            send_entity();
            std::this_thread::sleep_for(frameDuration);
        }
    }

    void Server::delaySpawn(ClockManager &clock)
    {
        for (auto it = _vecSpawn.begin(); it != _vecSpawn.end(); ) {
            if (clock.elapsedSeconds() >= it->delaySpawn) {
                _ptp.initEnnemies(it->posX, it->posY, it->type);
                it = _vecSpawn.erase(it);
            } else {
                ++it;
            }
        }
    }

    bool Server::isLevelReady()
    {
        return _vecSpawn.empty();
    }


    void Server::send_data(Packet &packet, asio::ip::udp::endpoint endpoint)
    {
        // std::cout << "send packet" << std::endl;

        // std::cout << "Sending to remote endpoint: " 
        //           << endpoint.address().to_string() << ":"
        //           << endpoint.port() << std::endl;

        _binary.serialize(packet, _bufferSerialize);
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
                                // std::cout << "afterbytes: " << bytes << std::endl;

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