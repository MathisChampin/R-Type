#include "ProtocolHandler.hpp"
#include "Server.hpp"

namespace NmpServer
{
    void ProtocoleHandler::executeOpCode()
    {
        System sys;
        std::cout << "CALL PROTOCOLE" << std::endl;
        EVENT key = _pck.getOpCode();
        auto it = _mapFctOpCode.find(key);
        if (it != _mapFctOpCode.end()) {
            it->second();
        }
        createEnnemies();
        shootEnnemies();
        sys.position_system(_ecs);
        sys.collision_system(_ecs);
        sys.kill_system(_ecs);
    }

    void ProtocoleHandler::createEnnemies()
    {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = now - _lastEnemyCreationTime;

        if (elapsed.count() >= 2.0) {
            std::cout << "creation of ennemies" << std::endl;
            initEnnemies();
            _lastEnemyCreationTime = now;
        }
    }

    void ProtocoleHandler::shootEnnemies()
    {
        System sys;

        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = now - _lastShootCreationTime;

        if (elapsed.count() >= 3.0) {
            std::cout << "shoot of ennemies" << std::endl;
            sys.shoot_system_ennemies(_ecs);
            _lastShootCreationTime = now;
        }
    }

    ProtocoleHandler::ProtocoleHandler(Server &server) : _refServer(server), _lastEnemyCreationTime(std::chrono::steady_clock::now()), _lastShootCreationTime(std::chrono::steady_clock::now())
    {
        std::cout << "protocole Handler create" << std::endl;
        this->initComponents();
    }

    void ProtocoleHandler::fillPacket(Packet &packet)
    {
        _pck = packet;
    }



    void ProtocoleHandler::evalMove()
    {
        std::cout << "evalMove" << std::endl;
        std::cout << "id client: " << _pck.getId() << std::endl;

        std::size_t idClient{ _pck.getId()};
        auto &pos = _ecs.get_components<component::position>();
        auto player = _ecs.get_entity(idClient);
    
         asio::ip::udp::endpoint foundEndpoint;
        for (const auto &pair : _vecPlayer) {
            if (pair.first == player) {
                foundEndpoint = pair.second;
                break;
            }
        }
        auto &position = pos[player.get_id()];
        System sys;

        auto direction = _pck.getArg();
            if (direction.has_value())
                std::cout << "Direction: ";
            if (direction == DIRECTION::DOWN) {
                std::cout << "DOWN" << std::endl;
                _ecs.add_component<component::controllable>(player, {component::controllable::Down});
                sys.control_system(_ecs);
                std::cout << "pos x: " << position.x << " pos y: " << position.y << std::endl;
                Packet packetPos(EVENT::MOVE, position.x, position.y);
                _refServer.get().send_data(packetPos, foundEndpoint);
            } else if (direction == DIRECTION::UP) {
                std::cout << "UP" << std::endl;
                _ecs.add_component<component::controllable>(player, {component::controllable::Up});
                sys.control_system(_ecs);
                std::cout << "pos x: " << position.x << " pos y: " << position.y << std::endl;
                Packet packetPos(EVENT::MOVE, position.x, position.y);
                _refServer.get().send_data(packetPos, foundEndpoint);
            } else if (direction == DIRECTION::LEFT) {
                std::cout << "LEFT" << std::endl;
                _ecs.add_component<component::controllable>(player, {component::controllable::Left});
                sys.control_system(_ecs);
                std::cout << "pos x: " << position.x << " pos y: " << position.y << std::endl;
                Packet packetPos(EVENT::MOVE, position.x, position.y);
                _refServer.get().send_data(packetPos, foundEndpoint);
            } else if (direction == DIRECTION::RIGHT) {
                std::cout << "RIGHT" << std::endl;
                _ecs.add_component<component::controllable>(player, {component::controllable::Right});
                sys.control_system(_ecs);
                std::cout << "pos x: " << position.x << " pos y: " << position.y << std::endl;
                Packet packetPos(EVENT::MOVE, position.x, position.y);
                _refServer.get().send_data(packetPos, foundEndpoint);
            } else
                std::cout << "NO DIRECTION" << std::endl;
        std::cout << "x " << position.x << " y " << position.y << std::endl;
    }

    void ProtocoleHandler::evalShoot()
    {
        std::cout << "evalMove" << std::endl;
        std::cout << "id client: " << _pck.getId() << std::endl;

        std::size_t idClient{ _pck.getId()};
        auto player = _ecs.get_entity(idClient);
        System sys;

        _ecs.emplace_component<component::controllable>(player, component::controllable::Shoot);
        sys.shoot_system_player(_ecs);
    }

    void ProtocoleHandler::evalQuit()
    {
        std::cout << "evalQuit" << std::endl;
    }

    void ProtocoleHandler::evalJoin()
    {
        Entity player;
        this->initPlayer();
        auto lastPlayer = _vecPlayer.back().first;
        auto lastEndpoint = _vecPlayer.back().second;

        
        Packet joinPacket(lastPlayer.get_id(), EVENT::JOIN);
        _refServer.get().send_data(joinPacket, lastEndpoint);
    }

    void ProtocoleHandler::initComponents()
    {
        _ecs.register_component<component::attribute>();
        _ecs.register_component<component::controllable>();
        _ecs.register_component<component::level>();
        _ecs.register_component<component::life>();
        _ecs.register_component<component::position>();
        _ecs.register_component<component::score>();
        _ecs.register_component<component::size>();
        _ecs.register_component<component::state>();
        _ecs.register_component<component::velocity>();
    }

    void ProtocoleHandler::initPlayer()
    {
        Entity player = _ecs.spawn_entity();
        auto lastEndpoint = _refServer.get().getLastEndpoint();

        for (size_t i = 0; i < 4; i++) {
            if (_vecPlayer.size() == 0)
                _ecs.add_component<component::attribute>(player, {component::attribute::Player1});
            if (_vecPlayer.size() == 1)
                _ecs.add_component<component::attribute>(player, {component::attribute::Player2});
            if (_vecPlayer.size() == 2)
                _ecs.add_component<component::attribute>(player, {component::attribute::Player3});
            if (_vecPlayer.size() == 3)
                _ecs.add_component<component::attribute>(player, {component::attribute::Player4});
        }
        _ecs.add_component<component::controllable>(player, {component::controllable::NoKey});
        _ecs.add_component<component::level>(player, {component::level::Level0});
        _ecs.add_component<component::life>(player, {4});
        _ecs.add_component<component::position>(player, {50, 500});
        _ecs.add_component<component::score>(player, {0});
        _ecs.add_component<component::size>(player, {32, 14});
        _ecs.add_component<component::state>(player, {component::state::Alive});
        _ecs.add_component<component::velocity>(player, {0, 0});
        _vecPlayer.push_back(std::make_pair(player, lastEndpoint));  
    }

    void ProtocoleHandler::initEnnemies()
    {
        static std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<int> dist(0, 1080);

        Entity ennemies = _ecs.spawn_entity();
        int y = dist(rng);

        _ecs.add_component<component::attribute>(ennemies, {component::attribute::Ennemies});
        _ecs.add_component<component::level>(ennemies, {component::level::Level0});
        _ecs.add_component<component::life>(ennemies, {1});
        _ecs.add_component<component::position>(ennemies, {1920, y});
        _ecs.add_component<component::size>(ennemies, {32, 14});
        _ecs.add_component<component::state>(ennemies, {component::state::Alive});
        _ecs.add_component<component::velocity>(ennemies, {20, 0});
    }

}