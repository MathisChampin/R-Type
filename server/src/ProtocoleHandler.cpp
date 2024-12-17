#include "ProtocolHandler.hpp"
#include "Server.hpp"
#include "idPlayer.hpp"

namespace NmpServer
{
    void ProtocoleHandler::executeOpCode()
    {
        std::cout << "CALL PROTOCOLE" << std::endl;
        EVENT key = _pck.getOpCode();
        auto it = _mapFctOpCode.find(key);
        if (it != _mapFctOpCode.end()) {
            it->second();
        }
        //createEnnemies(); //en fraire un thread 
        //shootEnnemies();  //en fraire un thread
        //sys.position_system(_ecs);
        //std::cout << "position system" << std::endl;
        //sys.collision_system(_ecs);
        //sys.kill_system(_ecs);
    }

    registry &ProtocoleHandler::getECS() {
        return _ecs;
    }

    ProtocoleHandler::ProtocoleHandler(Server &server) : 
        _refServer(server),
        _lastEnemyCreationTime(std::chrono::steady_clock::now()),
        _lastShootCreationTime(std::chrono::steady_clock::now())
    {
        std::cout << "protocole Handler create" << std::endl;
        this->initComponents();
        this->initEnnemies();
    }

    void ProtocoleHandler::fillPacket(Packet &packet)
    {
        _pck = packet;
    }

    std::optional<asio::ip::udp::endpoint> ProtocoleHandler::foundEndpointByClient(Entity &player)
    {
        std::optional<asio::ip::udp::endpoint> optionEndpoint{std::nullopt};

        for (const auto &pair : _vecPlayer) {
            if (pair.first == player) {
                return optionEndpoint = pair.second;
            }
        }
        return optionEndpoint;
    }

    void ProtocoleHandler::updateMoveEcs(
        Entity &player, 
        component::controllable::Key &control, 
        sparse_array<component::position>::value_type &pos)
    {
        System sys;
        std::optional<asio::ip::udp::endpoint> foundEndpoint{this->foundEndpointByClient(player)}; 

        if (foundEndpoint.has_value()) {
            _ecs.emplace_component<component::controllable>(player, control);
            sys.control_system(_ecs);
            std::cout << "pos x: " << pos.x << " pos y: " << pos.y << std::endl;
            //Packet packetPos(EVENT::MOVE, pos.x, pos.y);
            //_refServer.get().send_data(packetPos, foundEndpoint.value());
        } else {
            std::cout << "no endpoint found for this client" << std::endl;
        }
    }

    void ProtocoleHandler::evalMove()
    {
        std::cout << "evalMove" << std::endl;
        std::cout << "id client: " << _pck.getId() << std::endl;
        std::size_t idClient{ _pck.getId()};
        sparse_array<component::position> &pos = _ecs.get_components<component::position>();
        Entity player = _ecs.get_entity(idClient);
        sparse_array<component::position>::value_type &position = pos[player.get_id()];
        std::optional<NmpServer::DIRECTION> direction = _pck.getArg();

        if (direction == DIRECTION::DOWN) {
            std::cout << "DOWN" << std::endl;
            auto control = component::controllable::Down;
            updateMoveEcs(player, control, position);
        } else if (direction == DIRECTION::UP) {
            std::cout << "UP" << std::endl;
            auto control = component::controllable::Up;
            updateMoveEcs(player, control, position);
        } else if (direction == DIRECTION::LEFT) {
            std::cout << "LEFT" << std::endl;
            auto control = component::controllable::Left;
            updateMoveEcs(player, control, position);
        } else if (direction == DIRECTION::RIGHT) {
            auto control = component::controllable::Right;
            updateMoveEcs(player, control, position);
        } else if ((direction == DIRECTION::SHOOT)) {
            auto control = component::controllable::Shoot;
            updateMoveEcs(player, control, position);
        } else 
            std::cout << "NO DIRECTION" << std::endl;
        std::cout << "x " << position.x << " y " << position.y << std::endl;
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
        _ecs.add_component<component::idPlayer>(player, {player.get_id()});
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
        _ecs.add_component<component::controllable>(ennemies, {component::controllable::Key::NoKey});
        _ecs.add_component<component::life>(ennemies, {1});
        _ecs.add_component<component::position>(ennemies, {1800, y});
        _ecs.add_component<component::size>(ennemies, {33, 36});
        _ecs.add_component<component::state>(ennemies, {component::state::Alive});
        _ecs.add_component<component::idPlayer>(ennemies, {ennemies.get_id()});
        _ecs.add_component<component::velocity>(ennemies, {-1, 0});
    }

}