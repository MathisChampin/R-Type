#include "ProtocolHandler.hpp"
#include "Server.hpp"

namespace NmpServer
{
    void ProtocoleHandler::executeOpCode()
    {
        EVENT key = _pck.getOpCode();
        auto it = _mapFctOpCode.find(key);
        if (it != _mapFctOpCode.end()) {
            it->second();
        }
    }

    ProtocoleHandler::ProtocoleHandler(Server &server) : _refServer(server)
    {
        std::cout << "protocole Handler create" << std::endl;
        this->initComponents();
    }

    void ProtocoleHandler::fillPacket(Packet &packet)
    {
        std::cout << "test id: " << packet.getId() << std::endl;
        _pck = packet;
    }

    void ProtocoleHandler::evalMove()
    {
        std::cout << "evalMove" << std::endl;
        std::cout << "id client: " << _pck.getId() << std::endl;

        std::size_t idClient{ _pck.getId()};
        auto &pos = _ecs.register_component<component::position>();
        auto player = _ecs.get_entity(idClient);
        auto &position = pos[player.get_id()];
        System sys;

        auto direction = _pck.getArg();
            if (direction.has_value())
                std::cout << "Direction: ";
            if (direction == DIRECTION::DOWN) {
                std::cout << "DOWN" << std::endl;
                _ecs.emplace_component<component::controllable>(player, component::controllable::Down);
                sys.control_system(_ecs);
                sys.position_system(_ecs);
            } else if (direction == DIRECTION::UP) {
                std::cout << "UP" << std::endl;
                _ecs.emplace_component<component::controllable>(player, component::controllable::Up);
                sys.control_system(_ecs);
                sys.position_system(_ecs);
            } else if (direction == DIRECTION::LEFT) {
                std::cout << "LEFT" << std::endl;
                _ecs.emplace_component<component::controllable>(player, component::controllable::Left);
                sys.control_system(_ecs);
                sys.position_system(_ecs);
            } else if (direction == DIRECTION::RIGHT) {
                std::cout << "RIGHT" << std::endl;
                _ecs.emplace_component<component::controllable>(player, component::controllable::Right);
                sys.control_system(_ecs);
                sys.position_system(_ecs);
            } else
                std::cout << "NO DIRECTION" << std::endl;
        std::cout << "x " << position.x << " y " << position.y << std::endl;
    }

    void ProtocoleHandler::evalShoot()
    {
        std::cout << "evalShoot" << std::endl;
    }

    void ProtocoleHandler::evalQuit()
    {
        std::cout << "evalQuit" << std::endl;
    }

    void ProtocoleHandler::evalJoin()
    {
        Entity player;
        this->initPlayer();
        auto lastPlayer = _vecPlayer.back();

        Packet joinPacket(lastPlayer.get_id(), EVENT::JOIN);
        auto lastendpoint = _refServer.get()._remote_endpoint;
        _refServer.get().send_data(joinPacket, lastendpoint);
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

        _ecs.add_component<component::attribute>(player, {component::attribute::Player});
        _ecs.add_component<component::controllable>(player, {component::controllable::NoKey});
        _ecs.add_component<component::level>(player, {component::level::Level0});
        _ecs.add_component<component::life>(player, {4});
        _ecs.add_component<component::position>(player, {50, 500});
        _ecs.add_component<component::score>(player, {0});
        _ecs.add_component<component::size>(player, {32, 14});
        _ecs.add_component<component::state>(player, {component::state::Alive});
        _ecs.add_component<component::velocity>(player, {0, 0});
        _vecPlayer.push_back(player);  
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